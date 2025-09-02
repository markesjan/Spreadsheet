#include "ValStrExpr.hpp"

ValStrExpr::ValStrExpr(std::string val) : value(CellData(val)) {}

CellData ValStrExpr::eval(std::map<Position, CellValue>& table) const {
	return value;
}

ExprPtr ValStrExpr::clone() const {
	return std::make_shared<ValStrExpr>(std::get<std::string>(value));
}

std::string ValStrExpr::print() const {
	return "(" + std::get<std::string>(value) + ")";
}
