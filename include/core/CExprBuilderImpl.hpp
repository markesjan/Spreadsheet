#pragma once

#include <string>

#include "CExprBuilder.hpp"
#include "CellValue.hpp"
#include "IExpression.hpp"
#include "Position.hpp"

// Concrete implementation of CExprBuilder that constructs an AST (Abstract Syntax Tree)
class CExprBuilderImpl : public CExprBuilder {
public:
	void opAdd() override;
	void opSub() override;
	void opMul() override;
	void opDiv() override;
	void opPow() override;
	void opNeg() override;
	void opEq() override;
	void opNe() override;
	void opLt() override;
	void opLe() override;
	void opGt() override;
	void opGe() override;
	void valNumber(double val) override;
	void valString(std::string val) override;
	void valReference(std::string val) override;
	void valRange(std::string val) override;
	void funcCall(std::string fnName, int paramCount) override;

	std::stack<ExprPtr> getExprStack();
	std::set<Position> getCellRefs();

private:
	std::pair<ExprPtr, ExprPtr> popTwo();

	std::stack<ExprPtr> exprStack;
	std::set<Position> cellRefs;
};
