#include "ValRefExpr.hpp"

#include <algorithm>

ValRefExpr::ValRefExpr(std::string val) {
	// Determine if rows or columns are absolute
	for (size_t i = 0; i < val.length(); i++) {
		if (i == 0 && val[i] == '$')
			col_abs = true;

		if (i > 0 && val[i] == '$')
			row_abs = true;
	}

	std::erase(val, '$');
	position = Position(val);
}

ValRefExpr::ValRefExpr(Position pos, bool col, bool row) : position(std::move(pos)), col_abs(col), row_abs(row) {}

CellData ValRefExpr::eval(std::map<Position, CellValue>& table) const {
	CellValue ref_value;

	try {
		ref_value = table.at(position);
	} catch (const std::out_of_range&) {
	}

	if (!ref_value.ast.empty())
		return ref_value.ast.top()->eval(table);

	return ref_value.data;
}

ExprPtr ValRefExpr::clone() const {
	return std::make_shared<ValRefExpr>(position, col_abs, row_abs);
}

std::string ValRefExpr::print() const {
	return "(" + position.print(col_abs, row_abs) + ")";
}

void ValRefExpr::shiftReferences(int w, int h) {
	if (!col_abs && !row_abs)
		this->position = this->position.shift(w, h);
	else if (!col_abs && row_abs)
		this->position = this->position.shift(w, 0);
	else if (col_abs && !row_abs)
		this->position = this->position.shift(0, h);
}
