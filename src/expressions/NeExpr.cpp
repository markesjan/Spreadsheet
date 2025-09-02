#include "NeExpr.hpp"

NeExpr::NeExpr(ExprPtr lhs, ExprPtr rhs) : BinaryOpExpr(std::move(lhs), std::move(rhs), "!=") {}

CellData NeExpr::eval(std::map<Position, CellValue>& table) const {
	return cmp(lhs->eval(table), rhs->eval(table), std::not_equal_to());
}

ExprPtr NeExpr::clone() const {
	return std::make_shared<NeExpr>(lhs->clone(), rhs->clone());
}
