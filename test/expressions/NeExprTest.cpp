#include <cassert>
#include <map>

#include "CellValue.hpp"
#include "NeExpr.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"
#include "ValStrExpr.hpp"

void testNeNumbersNotEqual() {
	auto lhs = std::make_shared<ValNumExpr>(7.0);
	auto rhs = std::make_shared<ValNumExpr>(3.0);
	NeExpr ne(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ne.eval(table);
	assert(valueMatch(result, 1.0));
}

void testNeNumbersEqual() {
	auto lhs = std::make_shared<ValNumExpr>(5.0);
	auto rhs = std::make_shared<ValNumExpr>(5.0);
	NeExpr ne(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ne.eval(table);
	assert(valueMatch(result, 0.0));
}

void testNeStringsNotEqual() {
	auto lhs = std::make_shared<ValStrExpr>("zeta");
	auto rhs = std::make_shared<ValStrExpr>("alpha");
	NeExpr ne(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ne.eval(table);
	assert(valueMatch(result, 1.0));
}

void testNeStringsEqual() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValStrExpr>("foo");
	NeExpr ne(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ne.eval(table);
	assert(valueMatch(result, 0.0));
}

void testNeNumberVsString() {
	auto lhs = std::make_shared<ValNumExpr>(42.0);
	auto rhs = std::make_shared<ValStrExpr>("foo");
	NeExpr ne(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ne.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testNeStringVsNumber() {
	auto lhs = std::make_shared<ValStrExpr>("bar");
	auto rhs = std::make_shared<ValNumExpr>(10.0);
	NeExpr ne(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ne.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testNeMonostateVsMonostate() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<EmptyExpr>();
	NeExpr ne(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ne.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testNeMonostateVsNumber() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<ValNumExpr>(5.0);
	NeExpr ne(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = ne.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testNeExpr() {
	testNeNumbersNotEqual();
	testNeNumbersEqual();
	testNeStringsNotEqual();
	testNeStringsEqual();
	testNeNumberVsString();
	testNeStringVsNumber();
	testNeMonostateVsMonostate();
	testNeMonostateVsNumber();
}
