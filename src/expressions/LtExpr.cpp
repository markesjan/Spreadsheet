#include "LtExpr.hpp"

LtExpr::LtExpr(ExprPtr lhs, ExprPtr rhs) : BinaryOpExpr(std::move(lhs), std::move(rhs), "<") {}

CellData LtExpr::eval(std::map<Position, CellValue>& table) const {
	return cmp(lhs->eval(table), rhs->eval(table), std::less());
}

ExprPtr LtExpr::clone() const {
	return std::make_shared<LtExpr>(lhs->clone(), rhs->clone());
}
