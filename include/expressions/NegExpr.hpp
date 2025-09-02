#pragma once

#include "IExpression.hpp"

// Represents a negation expression (!val) in the AST
class NegExpr : public IExpression {
public:
	explicit NegExpr(ExprPtr val);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
	std::string print() const override;
	void shiftReferences(int w, int h) override;

private:
	ExprPtr value;
};
