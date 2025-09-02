#pragma once

#include "BinaryOpExpr.hpp"

// Represents an subtraction expression (lhs - rhs) in the AST
class SubExpr : public BinaryOpExpr {
public:
	SubExpr(ExprPtr lhs, ExprPtr rhs);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
};
