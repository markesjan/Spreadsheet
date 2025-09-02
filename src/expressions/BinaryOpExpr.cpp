#include "BinaryOpExpr.hpp"

BinaryOpExpr::BinaryOpExpr(ExprPtr lhs, ExprPtr rhs, std::string symbol) :
	lhs(std::move(lhs)), rhs(std::move(rhs)), opSymbol(std::move(symbol)) {}

std::string BinaryOpExpr::print() const {
	return "(" + lhs->print() + " " + opSymbol + " " + rhs->print() + ")";
}

void BinaryOpExpr::shiftReferences(int w, int h) {
	lhs->shiftReferences(w, h);
	rhs->shiftReferences(w, h);
}
