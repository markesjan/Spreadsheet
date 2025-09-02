#include "SubExpr.hpp"

SubExpr::SubExpr(ExprPtr lhs, ExprPtr rhs) : BinaryOpExpr(std::move(lhs), std::move(rhs), "-") {}

CellData SubExpr::eval(std::map<Position, CellValue>& table) const {
	CellData l_val = lhs->eval(table), r_val = rhs->eval(table);

	if (!std::holds_alternative<double>(l_val) || !std::holds_alternative<double>(r_val))
		return {};

	return std::get<double>(l_val) - std::get<double>(r_val);
}

ExprPtr SubExpr::clone() const {
	return std::make_shared<SubExpr>(lhs->clone(), rhs->clone());
}
