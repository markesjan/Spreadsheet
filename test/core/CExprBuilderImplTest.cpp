#include <cassert>
#include <iostream>
#include <string>

#include "CExprBuilderImpl.hpp"
#include "TestUtil.hpp"

void testNumberValue() {
	CExprBuilderImpl builder;
	parseExpression("=1", builder);
	auto stack = builder.getExprStack();
	assert(!stack.empty());

	auto root = stack.top();
	std::map<Position, CellValue> table;
	auto result = root->eval(table);
	assert(valueMatch(result, 1.0));
}

void testStringValue() {
	CExprBuilderImpl builder;
	parseExpression("=\"hello\"", builder);
	auto stack = builder.getExprStack();
	assert(!stack.empty());

	auto root = stack.top();
	std::map<Position, CellValue> table;
	auto result = root->eval(table);
	assert(valueMatch(result, "hello"));
}

void testSimpleAddition() {
	CExprBuilderImpl builder;
	parseExpression("=1+2", builder);
	auto stack = builder.getExprStack();
	assert(!stack.empty());

	auto root = stack.top();
	std::map<Position, CellValue> table;
	auto result = root->eval(table);
	assert(valueMatch(result, 3.0));
}

void testCellReference() {
	CExprBuilderImpl builder;
	parseExpression("=A1", builder);
	auto refs = builder.getCellRefs();
	assert(refs.count(Position("A1")) == 1);
	assert(refs.size() == 1);
}

void testInvalidExpression() {
	CExprBuilderImpl builder;
	try {
		parseExpression("=1+", builder);
		assert(false && "Expected exception not thrown");
	} catch (const std::invalid_argument&) {
	}
}

void exprBuilderTest() {
	testNumberValue();
	testStringValue();
	testSimpleAddition();
	testCellReference();
	testInvalidExpression();
	std::cout << "All CExprBuilderImpl tests passed!" << std::endl;
}
