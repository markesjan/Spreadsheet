#include <cassert>
#include <map>

#include "CellValue.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"

void testValNumExprPositive() {
	ValNumExpr expr(42.0);
	std::map<Position, CellValue> table;
	auto result = expr.eval(table);
	assert(valueMatch(result, 42.0));
}

void testValNumExprNegative() {
	ValNumExpr expr(-13.5);
	std::map<Position, CellValue> table;
	auto result = expr.eval(table);
	assert(valueMatch(result, -13.5));
}

void testValNumExprZero() {
	ValNumExpr expr(0.0);
	std::map<Position, CellValue> table;
	auto result = expr.eval(table);
	assert(valueMatch(result, 0.0));
}

void testValNumExpr() {
	testValNumExprPositive();
	testValNumExprNegative();
	testValNumExprZero();
}
