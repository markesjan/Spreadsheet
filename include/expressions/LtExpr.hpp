#pragma once

#include "BinaryOpExpr.hpp"

// Represents a lower than expression (lhs < rhs) in the AST
class LtExpr : public BinaryOpExpr {
public:
	LtExpr(ExprPtr lhs, ExprPtr rhs);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
};
