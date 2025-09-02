#pragma once

#include <map>
#include <string>

#include "CellValue.hpp"
#include "Position.hpp"

// Delimiter for save and load methods
constexpr char DELIM = '~';

// Represents a table of cells and its operations
class Spreadsheet {
public:
	Spreadsheet() = default;

	bool load(std::istream& is);
	bool save(std::ostream& os) const;
	bool setCell(Position pos, const std::string& contents);
	CellData getValue(Position pos);
	void copyRect(Position dst, Position src, int w = 1, int h = 1);

private:
	bool dfsCycleCheck(const Position& pos, std::set<Position>& visiting, std::set<Position>& visited);
	bool hasCycle(const Position& pos, const std::set<Position>& refs);

	std::map<Position, CellValue> table;
};
