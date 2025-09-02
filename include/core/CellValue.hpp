#pragma once

#include <memory>
#include <set>
#include <stack>
#include <string>
#include <variant>

#include "Position.hpp"

// Forward declaration to avoid cyclic include
class IExpression;
using ExprPtr = std::shared_ptr<IExpression>;

using CellData = std::variant<std::monostate, double, std::string>;

// Represents the value of a spreadsheet cell
class CellValue {
public:
	CellValue() = default;
	explicit CellValue(const std::string& contents);
	explicit CellValue(const CellData& data);

	friend std::ostream& operator<<(std::ostream& os, const CellValue& other);

	CellData data;
	std::stack<ExprPtr> ast;
	std::set<Position> refs;
};
