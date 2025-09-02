#include "GtExpr.hpp"

GtExpr::GtExpr(ExprPtr lhs, ExprPtr rhs) : BinaryOpExpr(std::move(lhs), std::move(rhs), ">") {}

CellData GtExpr::eval(std::map<Position, CellValue>& table) const {
	return cmp(lhs->eval(table), rhs->eval(table), std::greater());
}

ExprPtr GtExpr::clone() const {
	return std::make_shared<GtExpr>(lhs->clone(), rhs->clone());
}
