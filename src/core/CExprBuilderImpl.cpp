#include <iostream>
#include <string>

#include "AddExpr.hpp"
#include "CExprBuilderImpl.hpp"
#include "CellValue.hpp"
#include "DivExpr.hpp"
#include "EqExpr.hpp"
#include "GeExpr.hpp"
#include "GtExpr.hpp"
#include "LeExpr.hpp"
#include "LtExpr.hpp"
#include "MulExpr.hpp"
#include "NeExpr.hpp"
#include "NegExpr.hpp"
#include "Position.hpp"
#include "PowExpr.hpp"
#include "SubExpr.hpp"
#include "ValNumExpr.hpp"
#include "ValRefExpr.hpp"
#include "ValStrExpr.hpp"

void CExprBuilderImpl::opAdd() {
	auto [lhs, rhs] = popTwo();
	exprStack.push(std::make_shared<AddExpr>(AddExpr(lhs, rhs)));
}

void CExprBuilderImpl::opSub() {
	auto [lhs, rhs] = popTwo();
	exprStack.push(std::make_shared<SubExpr>(SubExpr(lhs, rhs)));
}

void CExprBuilderImpl::opMul() {
	auto [lhs, rhs] = popTwo();
	exprStack.push(std::make_shared<MulExpr>(MulExpr(lhs, rhs)));
}

void CExprBuilderImpl::opDiv() {
	auto [lhs, rhs] = popTwo();
	exprStack.push(std::make_shared<DivExpr>(DivExpr(lhs, rhs)));
}

void CExprBuilderImpl::opPow() {
	auto [base, exp] = popTwo();
	exprStack.push(std::make_shared<PowExpr>(PowExpr(base, exp)));
}

void CExprBuilderImpl::opNeg() {
	if (exprStack.empty())
		throw std::runtime_error("Invalid expression: not enough operands");

	auto num = exprStack.top();
	exprStack.pop();
	exprStack.push(std::make_shared<NegExpr>(NegExpr(num)));
}

void CExprBuilderImpl::opEq() {
	auto [lhs, rhs] = popTwo();
	exprStack.push(std::make_shared<EqExpr>(EqExpr(lhs, rhs)));
}

void CExprBuilderImpl::opNe() {
	auto [lhs, rhs] = popTwo();
	exprStack.push(std::make_shared<NeExpr>(NeExpr(lhs, rhs)));
}

void CExprBuilderImpl::opLt() {
	auto [lhs, rhs] = popTwo();
	exprStack.push(std::make_shared<LtExpr>(LtExpr(lhs, rhs)));
}

void CExprBuilderImpl::opLe() {
	auto [lhs, rhs] = popTwo();
	exprStack.push(std::make_shared<LeExpr>(LeExpr(lhs, rhs)));
}

void CExprBuilderImpl::opGt() {
	auto [lhs, rhs] = popTwo();
	exprStack.push(std::make_shared<GtExpr>(GtExpr(lhs, rhs)));
}

void CExprBuilderImpl::opGe() {
	auto [lhs, rhs] = popTwo();
	exprStack.push(std::make_shared<GeExpr>(GeExpr(lhs, rhs)));
}

void CExprBuilderImpl::valNumber(double val) {
	exprStack.push(std::make_shared<ValNumExpr>(ValNumExpr(val)));
}

void CExprBuilderImpl::valString(std::string val) {
	exprStack.push(std::make_shared<ValStrExpr>(ValStrExpr(val)));
}

void CExprBuilderImpl::valReference(std::string val) {
	exprStack.push(std::make_shared<ValRefExpr>(ValRefExpr(val)));
	std::erase(val, '$');
	cellRefs.insert(Position(val));
}

void CExprBuilderImpl::valRange(std::string val) {
	std::cout << val;
}

void CExprBuilderImpl::funcCall(std::string fnName, int paramCount) {
	std::cout << fnName;
}

std::stack<ExprPtr> CExprBuilderImpl::getExprStack() {
	return exprStack;
}

std::set<Position> CExprBuilderImpl::getCellRefs() {
	return cellRefs;
}

std::pair<ExprPtr, ExprPtr> CExprBuilderImpl::popTwo() {
	if (exprStack.size() < 2)
		throw std::runtime_error("Invalid expression: not enough operands");

	auto rhs = exprStack.top();
	exprStack.pop();
	auto lhs = exprStack.top();
	exprStack.pop();

	return {lhs, rhs};
}
