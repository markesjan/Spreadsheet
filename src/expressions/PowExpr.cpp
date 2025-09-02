#include <cmath>

#include "PowExpr.hpp"

PowExpr::PowExpr(ExprPtr lhs, ExprPtr rhs) : BinaryOpExpr(std::move(lhs), std::move(rhs), "^") {}

CellData PowExpr::eval(std::map<Position, CellValue>& table) const {
	CellData l_val = lhs->eval(table), r_val = rhs->eval(table);

	if (!std::holds_alternative<double>(l_val) || !std::holds_alternative<double>(r_val))
		return {};

	return pow(std::get<double>(l_val), std::get<double>(r_val));
}

ExprPtr PowExpr::clone() const {
	return std::make_shared<PowExpr>(lhs->clone(), rhs->clone());
}
