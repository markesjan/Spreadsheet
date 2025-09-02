#include <cassert>
#include <map>

#include "CellValue.hpp"
#include "MulExpr.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"
#include "ValStrExpr.hpp"

void testMulNumbers() {
	auto lhs = std::make_shared<ValNumExpr>(3.0);
	auto rhs = std::make_shared<ValNumExpr>(4.0);
	MulExpr mul(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = mul.eval(table);
	assert(valueMatch(result, 12.0));
}

void testMulWithZero() {
	auto lhs = std::make_shared<ValNumExpr>(0.0);
	auto rhs = std::make_shared<ValNumExpr>(999.0);
	MulExpr mul(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = mul.eval(table);
	assert(valueMatch(result, 0.0));
}

void testMulNumberAndString() {
	auto lhs = std::make_shared<ValNumExpr>(7.0);
	auto rhs = std::make_shared<ValStrExpr>("foo");
	MulExpr mul(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = mul.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testMulStringAndNumber() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValNumExpr>(11.0);
	MulExpr mul(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = mul.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testMulEmptyValues() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<EmptyExpr>();
	MulExpr mul(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = mul.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testMulExpr() {
	testMulNumbers();
	testMulWithZero();
	testMulNumberAndString();
	testMulStringAndNumber();
	testMulEmptyValues();
}
