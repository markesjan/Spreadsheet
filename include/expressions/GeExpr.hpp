#pragma once

#include "BinaryOpExpr.hpp"

// Represents a greater than or equal expression (lhs >= rhs) in the AST
class GeExpr : public BinaryOpExpr {
public:
	GeExpr(ExprPtr lhs, ExprPtr rhs);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
};
