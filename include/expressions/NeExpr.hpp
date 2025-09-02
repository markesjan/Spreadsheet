#pragma once

#include "BinaryOpExpr.hpp"

// Represents a not equal expression (lhs != rhs) in the AST
class NeExpr : public BinaryOpExpr {
public:
	NeExpr(ExprPtr lhs, ExprPtr rhs);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
};
