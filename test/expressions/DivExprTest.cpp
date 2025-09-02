#include <cassert>
#include <iostream>
#include <string>
#include <map>

#include "CellValue.hpp"
#include "DivExpr.hpp"
#include "Position.hpp"
#include "TestUtil.hpp"
#include "ValNumExpr.hpp"
#include "ValStrExpr.hpp"

void testDivideNumbers() {
    auto lhs = std::make_shared<ValNumExpr>(10.0);
    auto rhs = std::make_shared<ValNumExpr>(2.0);
    DivExpr div(lhs, rhs);
    std::map<Position, CellValue> table;
    auto result = div.eval(table);
	assert(valueMatch(result, 5.0));
}

void testDivideByZero() {
    auto lhs = std::make_shared<ValNumExpr>(10.0);
    auto rhs = std::make_shared<ValNumExpr>(0.0);
    DivExpr div(lhs, rhs);
    std::map<Position, CellValue> table;
    auto result = div.eval(table);
    assert(std::holds_alternative<std::monostate>(result));
}

void testDivideStringOperands() {
    auto lhs = std::make_shared<ValStrExpr>("foo");
    auto rhs = std::make_shared<ValStrExpr>("bar");
    DivExpr div(lhs, rhs);
    std::map<Position, CellValue> table;
    auto result = div.eval(table);
    assert(std::holds_alternative<std::monostate>(result));
}

void testDivideEmpty() {
    auto lhs = std::make_shared<EmptyExpr>();
    auto rhs = std::make_shared<EmptyExpr>();
    DivExpr div(lhs, rhs);
    std::map<Position, CellValue> table;
    auto result = div.eval(table);
    assert(std::holds_alternative<std::monostate>(result));
}

void testDivExpr() {
    testDivideNumbers();
    testDivideByZero();
    testDivideStringOperands();
    testDivideEmpty();
}
