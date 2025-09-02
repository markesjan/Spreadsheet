#include "DivExpr.hpp"

DivExpr::DivExpr(ExprPtr lhs, ExprPtr rhs) : BinaryOpExpr(std::move(lhs), std::move(rhs), "/") {}

CellData DivExpr::eval(std::map<Position, CellValue>& table) const {
	CellData l_val = lhs->eval(table), r_val = rhs->eval(table);

	if (!std::holds_alternative<double>(l_val) || !std::holds_alternative<double>(r_val) ||
		std::get<double>(r_val) == 0) {
		return {};
	}

	return std::get<double>(l_val) / std::get<double>(r_val);
}

ExprPtr DivExpr::clone() const {
	return std::make_shared<DivExpr>(lhs->clone(), rhs->clone());
}
