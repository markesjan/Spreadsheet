#include <cassert>
#include <cmath>
#include <map>

#include "CellValue.hpp"
#include "Position.hpp"
#include "PowExpr.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"
#include "ValStrExpr.hpp"

void testPowNumbers() {
	auto lhs = std::make_shared<ValNumExpr>(2.0);
	auto rhs = std::make_shared<ValNumExpr>(3.0);
	PowExpr pow(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = pow.eval(table);
	assert(valueMatch(result, 8.0));
}

void testPowZeroExponent() {
	auto lhs = std::make_shared<ValNumExpr>(5.0);
	auto rhs = std::make_shared<ValNumExpr>(0.0);
	PowExpr pow(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = pow.eval(table);
	assert(valueMatch(result, 1.0));
}

void testPowNumberAndString() {
	auto lhs = std::make_shared<ValNumExpr>(2.0);
	auto rhs = std::make_shared<ValStrExpr>("foo");
	PowExpr pow(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = pow.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testPowStringAndNumber() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValNumExpr>(3.0);
	PowExpr pow(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = pow.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testPowEmptyValues() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<EmptyExpr>();
	PowExpr pow(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = pow.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testPowExpr() {
	testPowNumbers();
	testPowZeroExponent();
	testPowNumberAndString();
	testPowStringAndNumber();
	testPowEmptyValues();
}
