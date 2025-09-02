#include <algorithm>
#include <iostream>
#include <vector>

#include "CExprBuilderImpl.hpp"
#include "Spreadsheet.hpp"

bool Spreadsheet::load(std::istream& is) {
	bool any_loaded = false;
	while (true) {
		std::string pos_str, val_str;
		if (!std::getline(is, pos_str, DELIM))
			break;
		if (!std::getline(is, val_str, DELIM))
			break;

		try {
			Position pos(pos_str);
			setCell(pos, val_str);
			any_loaded = true;
		} catch (const std::invalid_argument&) {
			// Skip invalid cell instead of aborting everything
		}
	}

	return any_loaded;
}

bool Spreadsheet::save(std::ostream& os) const {
	for (const auto& [pos, val] : table)
		os << pos << DELIM << val << DELIM;

	return true;
}

bool Spreadsheet::setCell(Position pos, const std::string& contents) {
	CellValue cell_val(contents);

	try {
		CExprBuilderImpl builder;
		parseExpression(contents, builder);
		cell_val.ast = builder.getExprStack();
		cell_val.refs = builder.getCellRefs();
	} catch (const std::invalid_argument&) {
		return false;
	}

	table[pos] = std::move(cell_val);
	return true;
}

CellData Spreadsheet::getValue(Position pos) {
	CellValue cell_content;

	try {
		cell_content = table.at(pos);
	} catch (const std::out_of_range&) {
		return {};
	}

	if (this->hasCycle(pos, cell_content.refs))
		return {};

	if (!cell_content.ast.empty())
		return cell_content.ast.top()->eval(table);

	return cell_content.data;
}

void Spreadsheet::copyRect(Position dst, Position src, int w, int h) {
	std::vector<std::pair<Position, CellValue>> copied_cells;
	std::pair<int, int> dist = src.distance(dst);

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			Position src_shift = src.shift(i, j);
			Position dst_shift = dst.shift(i, j);

			CellValue old_val;
			try {
				old_val = this->table.at(src_shift);
			} catch (const std::out_of_range&) {
			}

			if (!old_val.ast.empty()) {
				std::stack<ExprPtr> ast_cloned;
				ast_cloned.push(old_val.ast.top()->clone());

				old_val.ast = ast_cloned;
				old_val.ast.top()->shiftReferences(dist.first, dist.second);
				old_val.data = "=" + old_val.ast.top()->print();
			}

			copied_cells.emplace_back(dst_shift, old_val);
		}
	}

	for (const auto& [pos, val] : copied_cells)
		this->table[pos] = val;
}

bool Spreadsheet::dfsCycleCheck(const Position& pos, std::set<Position>& visiting, std::set<Position>& visited) {
	if (visited.contains(pos))
		return false;

	if (visiting.contains(pos))
		return true;

	visiting.insert(pos);
	std::set<Position> descendants;

	try {
		descendants = this->table.at(pos).refs;
	} catch (const std::out_of_range&) {
	}

	for (const auto& desc : descendants)
		if (this->dfsCycleCheck(desc, visiting, visited))
			return true;

	visiting.erase(pos);
	visited.insert(pos);
	return false;
}

bool Spreadsheet::hasCycle(const Position& pos, const std::set<Position>& refs) {
	std::set<Position> visiting = {pos}, visited;

	for (const auto& ref : refs)
		if (this->dfsCycleCheck(ref, visiting, visited))
			return true;

	return false;
}
