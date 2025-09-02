#pragma once

#include "BinaryOpExpr.hpp"

// Represents a lower than or equal expression (lhs <= rhs) in the AST
class LeExpr : public BinaryOpExpr {
public:
	LeExpr(ExprPtr lhs, ExprPtr rhs);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
};
