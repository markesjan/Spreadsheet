#pragma once

#include "BinaryOpExpr.hpp"

// Represents a greater than expression (lhs > rhs) in the AST
class GtExpr : public BinaryOpExpr {
public:
	GtExpr(ExprPtr lhs, ExprPtr rhs);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
};
