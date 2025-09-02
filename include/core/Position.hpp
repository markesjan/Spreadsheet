#pragma once

#include <cstdint>
#include <string>

// Represents a spreadsheet cell position
class Position {
public:
	Position() = default;
	explicit Position(std::string_view str);

	std::pair<int, int> distance(const Position& other) const;
	Position shift(int w, int h) const;
	std::string print(bool col_abs, bool row_abs) const;

	bool operator==(const Position& other) const;
	bool operator<(const Position& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Position& other);

private:
	static uint64_t colStringToInt(std::string col);
	static std::string colIntToString(uint64_t col);

	uint64_t col, row;
};
