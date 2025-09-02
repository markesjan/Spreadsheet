#pragma once

#include "BinaryOpExpr.hpp"

// Represents a division expression (lhs / rhs) in the AST
class DivExpr : public BinaryOpExpr {
public:
	DivExpr(ExprPtr lhs, ExprPtr rhs);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
};
