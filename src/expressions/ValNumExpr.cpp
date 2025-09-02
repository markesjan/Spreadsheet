#include "ValNumExpr.hpp"

ValNumExpr::ValNumExpr(double val) : value(CellData(val)) {}

CellData ValNumExpr::eval(std::map<Position, CellValue>& table) const {
	return value;
}

ExprPtr ValNumExpr::clone() const {
	return std::make_shared<ValNumExpr>(std::get<double>(value));
}

std::string ValNumExpr::print() const {
	return "(" + std::to_string(std::get<double>(value)) + ")";
}
