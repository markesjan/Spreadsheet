#include "NegExpr.hpp"

NegExpr::NegExpr(std::shared_ptr<IExpression> val) : value(std::move(val)) {}

CellData NegExpr::eval(std::map<Position, CellValue>& table) const {
	CellData num = value->eval(table);

	if (!std::holds_alternative<double>(num))
		return {};

	return -1 * std::get<double>(num);
}

std::shared_ptr<IExpression> NegExpr::clone() const {
	return std::make_shared<NegExpr>(value->clone());
}

std::string NegExpr::print() const {
	return "(-" + value->print() + ")";
}

void NegExpr::shiftReferences(int w, int h) {
	value->shiftReferences(w, h);
}
