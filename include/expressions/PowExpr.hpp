#pragma once

#include "BinaryOpExpr.hpp"

// Represents a power expression (^) in the AST
class PowExpr : public BinaryOpExpr {
public:
	PowExpr(ExprPtr lhs, ExprPtr rhs);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
};
