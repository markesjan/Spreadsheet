#pragma once

#include "IExpression.hpp"

// Represents a numeric value expression in the AST
class ValNumExpr : public IExpression {
public:
	explicit ValNumExpr(double val);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
	std::string print() const override;
	void shiftReferences(int w, int h) override {}

private:
	CellData value;
};
