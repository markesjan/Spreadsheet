#include "AddExpr.hpp"

AddExpr::AddExpr(ExprPtr lhs, ExprPtr rhs) : BinaryOpExpr(std::move(lhs), std::move(rhs), "+") {}

CellData AddExpr::eval(std::map<Position, CellValue>& table) const {
	CellData l_val = lhs->eval(table), r_val = rhs->eval(table);

	bool l_is_dbl = std::holds_alternative<double>(l_val), r_is_dbl = std::holds_alternative<double>(r_val),
		 l_is_str = std::holds_alternative<std::string>(l_val), r_is_str = std::holds_alternative<std::string>(r_val);

	if (l_is_dbl && r_is_dbl)
		return std::get<double>(l_val) + std::get<double>(r_val);
	if (l_is_str && r_is_str)
		return std::get<std::string>(l_val) + std::get<std::string>(r_val);
	if (l_is_dbl && r_is_str)
		return std::to_string(std::get<double>(l_val)) + std::get<std::string>(r_val);
	if (l_is_str && r_is_dbl)
		return std::get<std::string>(l_val) + std::to_string(std::get<double>(r_val));

	return {};
}

ExprPtr AddExpr::clone() const {
	return std::make_shared<AddExpr>(lhs->clone(), rhs->clone());
}
