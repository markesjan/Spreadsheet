#pragma once

#include "IExpression.hpp"

// Represents a string value expression in the AST
class ValStrExpr : public IExpression {
public:
	explicit ValStrExpr(std::string val);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
	std::string print() const override;
	void shiftReferences(int w, int h) override {}

private:
	CellData value;
};
