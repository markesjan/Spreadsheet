#pragma once

#include <map>
#include <memory>
#include <string>

#include "CellValue.hpp"
#include "Position.hpp"

// Interface for all expressions which are used as nodes in AST
class IExpression {
public:
	IExpression() = default;
	virtual ~IExpression() = default;

	virtual CellData eval(std::map<Position, CellValue>& table) const = 0;
	virtual std::shared_ptr<IExpression> clone() const = 0;
	virtual std::string print() const = 0;
	virtual void shiftReferences(int w, int h) = 0;
};

using ExprPtr = std::shared_ptr<IExpression>;
