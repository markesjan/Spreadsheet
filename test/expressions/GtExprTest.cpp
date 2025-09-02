#include <cassert>
#include <map>

#include "CellValue.hpp"
#include "GtExpr.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"
#include "ValStrExpr.hpp"

void testGtNumbersGreater() {
	auto lhs = std::make_shared<ValNumExpr>(7.0);
	auto rhs = std::make_shared<ValNumExpr>(3.0);
	GtExpr gt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = gt.eval(table);
	assert(valueMatch(result, 1.0));
}

void testGtNumbersEqual() {
	auto lhs = std::make_shared<ValNumExpr>(5.0);
	auto rhs = std::make_shared<ValNumExpr>(5.0);
	GtExpr gt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = gt.eval(table);
	assert(valueMatch(result, 0.0));
}

void testGtNumbersLess() {
	auto lhs = std::make_shared<ValNumExpr>(2.0);
	auto rhs = std::make_shared<ValNumExpr>(8.0);
	GtExpr gt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = gt.eval(table);
	assert(valueMatch(result, 0.0));
}

void testGtStringsGreater() {
	auto lhs = std::make_shared<ValStrExpr>("zeta");
	auto rhs = std::make_shared<ValStrExpr>("alpha");
	GtExpr gt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = gt.eval(table);
	assert(valueMatch(result, 1.0));
}

void testGtStringsEqual() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValStrExpr>("foo");
	GtExpr gt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = gt.eval(table);
	assert(valueMatch(result, 0.0));
}

void testGtStringsLess() {
	auto lhs = std::make_shared<ValStrExpr>("bar");
	auto rhs = std::make_shared<ValStrExpr>("foo");
	GtExpr gt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = gt.eval(table);
	assert(valueMatch(result, 0.0));
}

void testGtNumberVsString() {
	auto lhs = std::make_shared<ValNumExpr>(42.0);
	auto rhs = std::make_shared<ValStrExpr>("foo");
	GtExpr gt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = gt.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testGtStringVsNumber() {
	auto lhs = std::make_shared<ValStrExpr>("bar");
	auto rhs = std::make_shared<ValNumExpr>(10.0);
	GtExpr gt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = gt.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testGtMonostateVsMonostate() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<EmptyExpr>();
	GtExpr gt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = gt.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testGtMonostateVsNumber() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<ValNumExpr>(5.0);
	GtExpr gt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = gt.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testGtExpr() {
	testGtNumbersGreater();
	testGtNumbersEqual();
	testGtNumbersLess();
	testGtStringsGreater();
	testGtStringsEqual();
	testGtStringsLess();
	testGtNumberVsString();
	testGtStringVsNumber();
	testGtMonostateVsMonostate();
	testGtMonostateVsNumber();
}
