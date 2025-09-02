#include <cassert>
#include <map>

#include "CellValue.hpp"
#include "LtExpr.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"
#include "ValStrExpr.hpp"

void testLtNumbersLess() {
	auto lhs = std::make_shared<ValNumExpr>(3.0);
	auto rhs = std::make_shared<ValNumExpr>(7.0);
	LtExpr lt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = lt.eval(table);
	assert(valueMatch(result, 1.0));
}

void testLtNumbersEqual() {
	auto lhs = std::make_shared<ValNumExpr>(5.0);
	auto rhs = std::make_shared<ValNumExpr>(5.0);
	LtExpr lt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = lt.eval(table);
	assert(valueMatch(result, 0.0));
}

void testLtNumbersGreater() {
	auto lhs = std::make_shared<ValNumExpr>(8.0);
	auto rhs = std::make_shared<ValNumExpr>(2.0);
	LtExpr lt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = lt.eval(table);
	assert(valueMatch(result, 0.0));
}

void testLtStringsLess() {
	auto lhs = std::make_shared<ValStrExpr>("alpha");
	auto rhs = std::make_shared<ValStrExpr>("zeta");
	LtExpr lt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = lt.eval(table);
	assert(valueMatch(result, 1.0));
}

void testLtStringsEqual() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValStrExpr>("foo");
	LtExpr lt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = lt.eval(table);
	assert(valueMatch(result, 0.0));
}

void testLtStringsGreater() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValStrExpr>("bar");
	LtExpr lt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = lt.eval(table);
	assert(valueMatch(result, 0.0));
}

void testLtNumberVsString() {
	auto lhs = std::make_shared<ValNumExpr>(42.0);
	auto rhs = std::make_shared<ValStrExpr>("foo");
	LtExpr lt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = lt.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testLtStringVsNumber() {
	auto lhs = std::make_shared<ValStrExpr>("bar");
	auto rhs = std::make_shared<ValNumExpr>(10.0);
	LtExpr lt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = lt.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testLtMonostateVsMonostate() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<EmptyExpr>();
	LtExpr lt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = lt.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testLtMonostateVsNumber() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<ValNumExpr>(5.0);
	LtExpr lt(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = lt.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testLtExpr() {
	testLtNumbersLess();
	testLtNumbersEqual();
	testLtNumbersGreater();
	testLtStringsLess();
	testLtStringsEqual();
	testLtStringsGreater();
	testLtNumberVsString();
	testLtStringVsNumber();
	testLtMonostateVsMonostate();
	testLtMonostateVsNumber();
}
