#include "LeExpr.hpp"

LeExpr::LeExpr(ExprPtr lhs, ExprPtr rhs) : BinaryOpExpr(std::move(lhs), std::move(rhs), "<=") {}

CellData LeExpr::eval(std::map<Position, CellValue>& table) const {
	return cmp(lhs->eval(table), rhs->eval(table), std::less_equal());
}

ExprPtr LeExpr::clone() const {
	return std::make_shared<LeExpr>(lhs->clone(), rhs->clone());
}
