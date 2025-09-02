#include <cassert>
#include <map>
#include <string>

#include "CellValue.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValRefExpr.hpp"

void testValRefExprNumber() {
	std::string ref_str = "B2";
	ValRefExpr expr(ref_str);
	std::map<Position, CellValue> table;
	table[Position(ref_str)] = CellValue(42.5);
	auto result = expr.eval(table);
	assert(valueMatch(result, 42.5));
}

void testValRefExprString() {
	std::string ref_str = "D4";
	ValRefExpr expr(ref_str);
	std::map<Position, CellValue> table;
	table[Position(ref_str)] = CellValue(std::string("testVal"));
	auto result = expr.eval(table);
	assert(valueMatch(result, std::string("testVal")));
}

void testValRefExprEmptyCell() {
	std::string ref_str = "J9";
	ValRefExpr expr(ref_str);
	std::map<Position, CellValue> table;
	auto result = expr.eval(table);
	assert(std::holds_alternative<std::monostate>(result));
}

void testValRefExpr() {
	testValRefExprNumber();
	testValRefExprString();
	testValRefExprEmptyCell();
}
