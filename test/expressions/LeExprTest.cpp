#include <cassert>
#include <map>

#include "CellValue.hpp"
#include "LeExpr.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"
#include "ValStrExpr.hpp"

void testLeNumbersLess() {
	auto lhs = std::make_shared<ValNumExpr>(3.0);
	auto rhs = std::make_shared<ValNumExpr>(7.0);
	LeExpr le(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = le.eval(table);
	assert(valueMatch(result, 1.0));
}

void testLeNumbersEqual() {
	auto lhs = std::make_shared<ValNumExpr>(5.0);
	auto rhs = std::make_shared<ValNumExpr>(5.0);
	LeExpr le(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = le.eval(table);
	assert(valueMatch(result, 1.0));
}

void testLeNumbersGreater() {
	auto lhs = std::make_shared<ValNumExpr>(8.0);
	auto rhs = std::make_shared<ValNumExpr>(2.0);
	LeExpr le(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = le.eval(table);
	assert(valueMatch(result, 0.0));
}

void testLeStringsLess() {
	auto lhs = std::make_shared<ValStrExpr>("alpha");
	auto rhs = std::make_shared<ValStrExpr>("zeta");
	LeExpr le(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = le.eval(table);
	assert(valueMatch(result, 1.0));
}

void testLeStringsEqual() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValStrExpr>("foo");
	LeExpr le(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = le.eval(table);
	assert(valueMatch(result, 1.0));
}

void testLeStringsGreater() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValStrExpr>("bar");
	LeExpr le(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = le.eval(table);
	assert(valueMatch(result, 0.0));
}

void testLeNumberVsString() {
	auto lhs = std::make_shared<ValNumExpr>(42.0);
	auto rhs = std::make_shared<ValStrExpr>("foo");
	LeExpr le(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = le.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testLeStringVsNumber() {
	auto lhs = std::make_shared<ValStrExpr>("bar");
	auto rhs = std::make_shared<ValNumExpr>(10.0);
	LeExpr le(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = le.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testLeMonostateVsMonostate() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<EmptyExpr>();
	LeExpr le(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = le.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testLeMonostateVsNumber() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<ValNumExpr>(5.0);
	LeExpr le(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = le.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testLeExpr() {
	testLeNumbersLess();
	testLeNumbersEqual();
	testLeNumbersGreater();
	testLeStringsLess();
	testLeStringsEqual();
	testLeStringsGreater();
	testLeNumberVsString();
	testLeStringVsNumber();
	testLeMonostateVsMonostate();
	testLeMonostateVsNumber();
}
