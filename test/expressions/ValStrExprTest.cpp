#include <cassert>
#include <map>
#include <string>

#include "CellValue.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValStrExpr.hpp"

void testValStrExprNormal() {
	ValStrExpr expr("hello world");
	std::map<Position, CellValue> table;
	auto result = expr.eval(table);
	assert(valueMatch(result, std::string("hello world")));
}

void testValStrExprEmpty() {
	ValStrExpr expr("");
	std::map<Position, CellValue> table;
	auto result = expr.eval(table);
	assert(valueMatch(result, std::string("")));
}

void testValStrExpr() {
	testValStrExprNormal();
	testValStrExprEmpty();
}
