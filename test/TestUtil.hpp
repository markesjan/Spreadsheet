#pragma once

#include <cfloat>
#include <cmath>
#include <string>
#include <variant>

#include "CellValue.hpp"
#include "IExpression.hpp"

inline bool valueMatch(const CellData& lhs, const CellData& rhs) {
	if (lhs.index() != rhs.index())
		return false;
	if (lhs.index() == 0)
		return true;
	if (lhs.index() == 2)
		return std::get<std::string>(lhs) == std::get<std::string>(rhs);
	if (std::isnan(std::get<double>(lhs)) && std::isnan(std::get<double>(rhs)))
		return true;
	if (std::isinf(std::get<double>(lhs)) && std::isinf(std::get<double>(rhs)))
		return (std::get<double>(lhs) < 0 && std::get<double>(rhs) < 0) ||
			(std::get<double>(lhs) > 0 && std::get<double>(rhs) > 0);
	return fabs(std::get<double>(lhs) - std::get<double>(rhs)) <= 1e8 * DBL_EPSILON * fabs(std::get<double>(lhs));
}

class EmptyExpr : public IExpression {
	CellData eval(std::map<Position, CellValue>&) const override { return std::monostate{}; }
	ExprPtr clone() const override { return std::make_shared<EmptyExpr>(); }
	std::string print() const override { return "(empty)"; }
	void shiftReferences(int, int) override {}
};
