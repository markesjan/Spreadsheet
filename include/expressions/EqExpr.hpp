#pragma once

#include "BinaryOpExpr.hpp"

// Represents an equality comparison expression (lhs == rhs) in the AST
class EqExpr : public BinaryOpExpr {
public:
	EqExpr(ExprPtr lhs, ExprPtr rhs);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
};
