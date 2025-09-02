#include <functional>

#include "EqExpr.hpp"

EqExpr::EqExpr(ExprPtr lhs, ExprPtr rhs) : BinaryOpExpr(std::move(lhs), std::move(rhs), "==") {}

CellData EqExpr::eval(std::map<Position, CellValue>& table) const {
	return cmp(lhs->eval(table), rhs->eval(table), std::equal_to());
}

ExprPtr EqExpr::clone() const {
	return std::make_shared<EqExpr>(lhs->clone(), rhs->clone());
}
