#include <cassert>
#include <map>

#include "CellValue.hpp"
#include "NegExpr.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"
#include "ValStrExpr.hpp"

void testNegNumberPositive() {
	auto expr = std::make_shared<ValNumExpr>(5.0);
	NegExpr neg(expr);
	std::map<Position, CellValue> table;
	auto result = neg.eval(table);
	assert(valueMatch(result, -5.0));
}

void testNegNumberNegative() {
	auto expr = std::make_shared<ValNumExpr>(-7.5);
	NegExpr neg(expr);
	std::map<Position, CellValue> table;
	auto result = neg.eval(table);
	assert(valueMatch(result, 7.5));
}

void testNegZero() {
	auto expr = std::make_shared<ValNumExpr>(0.0);
	NegExpr neg(expr);
	std::map<Position, CellValue> table;
	auto result = neg.eval(table);
	assert(valueMatch(result, -0.0));
}

void testNegString() {
	auto expr = std::make_shared<ValStrExpr>("foo");
	NegExpr neg(expr);
	std::map<Position, CellValue> table;
	auto result = neg.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testNegEmpty() {
	auto expr = std::make_shared<EmptyExpr>();
	NegExpr neg(expr);
	std::map<Position, CellValue> table;
	auto result = neg.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testNegExpr() {
	testNegNumberPositive();
	testNegNumberNegative();
	testNegZero();
	testNegString();
	testNegEmpty();
}
