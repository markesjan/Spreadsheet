#include <cassert>
#include <map>
#include <string>

#include "AddExpr.hpp"
#include "CellValue.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"
#include "ValStrExpr.hpp"

void testAddNumbers() {
	auto lhs = std::make_shared<ValNumExpr>(2.5);
	auto rhs = std::make_shared<ValNumExpr>(4.5);
	AddExpr sum(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = sum.eval(table);
	assert(valueMatch(result, 7.0));
}

void testAddStrings() {
	auto lhs = std::make_shared<ValStrExpr>("Hello, ");
	auto rhs = std::make_shared<ValStrExpr>("World!");
	AddExpr sum(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = sum.eval(table);
	assert(valueMatch(result, "Hello, World!"));
}

void testAddNumberAndString() {
	auto lhs = std::make_shared<ValNumExpr>(123);
	auto rhs = std::make_shared<ValStrExpr>("foo");
	AddExpr sum(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = sum.eval(table);
	assert(valueMatch(result, "123.000000foo"));
}

void testAddStringAndNumber() {
	auto lhs = std::make_shared<ValStrExpr>("foo");
	auto rhs = std::make_shared<ValNumExpr>(42);
	AddExpr sum(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = sum.eval(table);
	assert(valueMatch(result, "foo42.000000"));
}

void testAddEmptyValues() {
	auto lhs = std::make_shared<EmptyExpr>();
	auto rhs = std::make_shared<EmptyExpr>();
	AddExpr sum(lhs, rhs);
	std::map<Position, CellValue> table;
	auto result = sum.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testAddExpr() {
	testAddNumbers();
	testAddStrings();
	testAddNumberAndString();
	testAddStringAndNumber();
	testAddEmptyValues();
}
