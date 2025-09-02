#pragma once

#include "BinaryOpExpr.hpp"

// Represents a multiplication expression (lhs * rhs) in the AST
class MulExpr : public BinaryOpExpr {
public:
	MulExpr(ExprPtr lhs, ExprPtr rhs);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
};
