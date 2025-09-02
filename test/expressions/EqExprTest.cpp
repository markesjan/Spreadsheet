#include <cassert>
#include <map>

#include "CellValue.hpp"
#include "EqExpr.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"
#include "ValStrExpr.hpp"

void testEqNumbersEqual() {
	auto lhs = std::make_shared<ValNumExpr>(5.0);
	auto rhs = std::make_shared<ValNumExpr>(5.0);
	EqExpr eq(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = eq.eval(table);
	assert(valueMatch(result, 1.0));
}

void testEqNumbersNotEqual() {
	auto lhs = std::make_shared<ValNumExpr>(3.0);
	auto rhs = std::make_shared<ValNumExpr>(7.0);
	EqExpr eq(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = eq.eval(table);
	assert(valueMatch(result, 0.0));
}

void testEqStringsEqual() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValStrExpr>("foo");
	EqExpr eq(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = eq.eval(table);
	assert(valueMatch(result, 1.0));
}

void testEqStringsNotEqual() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValStrExpr>("bar");
	EqExpr eq(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = eq.eval(table);
	assert(valueMatch(result, 0.0));
}

void testEqNumberVsString() {
	auto lhs = std::make_shared<ValNumExpr>(42.0);
	auto rhs = std::make_shared<ValStrExpr>("42");
	EqExpr eq(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = eq.eval(table);
	assert(!valueMatch(result, 0.0));
}

void testEqMonostateVsMonostate() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<EmptyExpr>();
	EqExpr eq(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = eq.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testEqMonostateVsNumber() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<ValNumExpr>(5.0);
	EqExpr eq(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = eq.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testEqMonostateVsString() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<ValStrExpr>("abc");
	EqExpr eq(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = eq.eval(table);
	assert(valueMatch(result, std::monostate{}));
}

void testEqExpr() {
	testEqNumbersEqual();
	testEqNumbersNotEqual();
	testEqStringsEqual();
	testEqStringsNotEqual();
	testEqNumberVsString();
	testEqMonostateVsMonostate();
	testEqMonostateVsNumber();
	testEqMonostateVsString();
}
