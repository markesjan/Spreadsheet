#include <cassert>
#include <map>

#include "CellValue.hpp"
#include "GeExpr.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"
#include "ValStrExpr.hpp"

void testGeNumbersGreater() {
	auto lhs = std::make_shared<ValNumExpr>(7.0);
	auto rhs = std::make_shared<ValNumExpr>(3.0);
	GeExpr ge(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ge.eval(table);
	assert(valueMatch(result, 1.0));
}

void testGeNumbersEqual() {
	auto lhs = std::make_shared<ValNumExpr>(5.0);
	auto rhs = std::make_shared<ValNumExpr>(5.0);
	GeExpr ge(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ge.eval(table);
	assert(valueMatch(result, 1.0));
}

void testGeNumbersLess() {
	auto lhs = std::make_shared<ValNumExpr>(2.0);
	auto rhs = std::make_shared<ValNumExpr>(8.0);
	GeExpr ge(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ge.eval(table);
	assert(valueMatch(result, 0.0));
}

void testGeStringsGreater() {
	auto lhs = std::make_shared<ValStrExpr>("zeta");
	auto rhs = std::make_shared<ValStrExpr>("alpha");
	GeExpr ge(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ge.eval(table);
	assert(valueMatch(result, 1.0));
}

void testGeStringsEqual() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValStrExpr>("foo");
	GeExpr ge(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ge.eval(table);
	assert(valueMatch(result, 1.0));
}

void testGeStringsLess() {
	auto lhs = std::make_shared<ValStrExpr>("bar");
	auto rhs = std::make_shared<ValStrExpr>("foo");
	GeExpr ge(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ge.eval(table);
	assert(valueMatch(result, 0.0));
}

void testGeNumberVsString() {
	auto lhs = std::make_shared<ValNumExpr>(42.0);
	auto rhs = std::make_shared<ValStrExpr>("foo");
	GeExpr ge(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ge.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testGeStringVsNumber() {
	auto lhs = std::make_shared<ValStrExpr>("bar");
	auto rhs = std::make_shared<ValNumExpr>(10.0);
	GeExpr ge(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ge.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testGeMonostateVsMonostate() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<EmptyExpr>();
	GeExpr ge(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ge.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testGeMonostateVsNumber() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<ValNumExpr>(5.0);
	GeExpr ge(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ge.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testGeExpr() {
	testGeNumbersGreater();
	testGeNumbersEqual();
	testGeNumbersLess();
	testGeStringsGreater();
	testGeStringsEqual();
	testGeStringsLess();
	testGeNumberVsString();
	testGeStringVsNumber();
	testGeMonostateVsMonostate();
	testGeMonostateVsNumber();
}
