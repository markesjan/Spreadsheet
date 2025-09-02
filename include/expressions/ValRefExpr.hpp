#pragma once

#include "IExpression.hpp"

// Represents a reference value expression in the AST
class ValRefExpr : public IExpression {
public:
	explicit ValRefExpr(std::string val);
	ValRefExpr(Position pos, bool col, bool row);

	CellData eval(std::map<Position, CellValue>& table) const override;
	ExprPtr clone() const override;
	std::string print() const override;
	void shiftReferences(int w, int h) override;

private:
	Position position;
	bool col_abs = false, row_abs = false;
};
