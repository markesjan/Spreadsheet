#pragma once

#include "IExpression.hpp"

// Base class for all binary operator expressions
class BinaryOpExpr : public IExpression {
public:
	BinaryOpExpr(ExprPtr lhs, ExprPtr rhs, std::string symbol);

	std::string print() const override;
	void shiftReferences(int w, int h) override;

protected:
	template <typename Compare>
	static CellData cmp(CellData lhs, CellData rhs, Compare op) {
		if (std::holds_alternative<double>(lhs) && std::holds_alternative<double>(rhs))
			return CellData(op(std::get<double>(lhs), std::get<double>(rhs)) ? 1.0 : 0.0);

		if (std::holds_alternative<std::string>(lhs) && std::holds_alternative<std::string>(rhs))
			return CellData(op(std::get<std::string>(lhs), std::get<std::string>(rhs)) ? 1.0 : 0.0);

		return {};
	}

	ExprPtr lhs, rhs;
	std::string opSymbol;
};
