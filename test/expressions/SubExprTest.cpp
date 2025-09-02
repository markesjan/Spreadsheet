#include <cassert>
#include <map>

#include "CellValue.hpp"
#include "Position.hpp"
#include "SubExpr.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"
#include "ValStrExpr.hpp"

void testSubNumbers() {
	auto lhs = std::make_shared<ValNumExpr>(10.0);
	auto rhs = std::make_shared<ValNumExpr>(4.5);
	SubExpr sub(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = sub.eval(table);
	assert(valueMatch(result, 5.5));
}

void testSubWithZero() {
	auto lhs = std::make_shared<ValNumExpr>(0.0);
	auto rhs = std::make_shared<ValNumExpr>(6.0);
	SubExpr sub(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = sub.eval(table);
	assert(valueMatch(result, -6.0));
}

void testSubNumberAndString() {
	auto lhs = std::make_shared<ValNumExpr>(7.0);
	auto rhs = std::make_shared<ValStrExpr>("foo");
	SubExpr sub(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = sub.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testSubStringAndNumber() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValNumExpr>(11.0);
	SubExpr sub(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = sub.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testSubEmptyValues() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<EmptyExpr>();
	SubExpr sub(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = sub.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testSubExpr() {
	testSubNumbers();
	testSubWithZero();
	testSubNumberAndString();
	testSubStringAndNumber();
	testSubEmptyValues();
}
