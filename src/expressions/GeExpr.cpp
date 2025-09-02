#include "GeExpr.hpp"

GeExpr::GeExpr(ExprPtr lhs, ExprPtr rhs) : BinaryOpExpr(std::move(lhs), std::move(rhs), ">=") {}

CellData GeExpr::eval(std::map<Position, CellValue>& table) const {
	return cmp(lhs->eval(table), rhs->eval(table), std::greater_equal());
}

ExprPtr GeExpr::clone() const {
	return std::make_shared<GeExpr>(lhs->clone(), rhs->clone());
}
