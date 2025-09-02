#pragma once

#include "BinaryOpExpr.hpp"

// Represents an addition expression (lhs + rhs) in the AST
class AddExpr : public BinaryOpExpr {
public:
	AddExpr(ExprPtr lhs, ExprPtr rhs);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
};
