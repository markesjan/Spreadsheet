#include <algorithm>
#include <stdexcept>

#include "Position.hpp"

Position::Position(std::string_view str) {
	std::string letters, digits;

	for (char c : str) {
		if (std::isalpha(c) && digits.empty())
			letters += c;
		else if (std::isdigit(c) && !letters.empty())
			digits += c;
		else
			throw std::invalid_argument("CPos constructor has invalid parameter");
	}

	if (digits.empty() || letters.empty() || str.empty())
		throw std::invalid_argument("CPos constructor has invalid parameter");

	std::ranges::transform(letters, letters.begin(), [](char c) { return static_cast<char>(std::toupper(c)); });

	this->col = colStringToInt(letters);
	this->row = std::stoi(digits);
}

std::pair<int, int> Position::distance(const Position& other) const {
	return {other.col - col, other.row - row};
}

Position Position::shift(int w, int h) const {
	Position result = *this;

	result.col += w;
	result.row += h;

	return result;
}

std::string Position::print(bool col_abs, bool row_abs) const {
	std::string result;

	result += col_abs ? "$" : "";
	result += colIntToString(col);
	result += row_abs ? "$" : "";
	result += std::to_string(row);

	return result;
}

bool Position::operator==(const Position& other) const {
	return this->col == other.col && this->row == other.row;
}

bool Position::operator<(const Position& other) const {
	if (col != other.col)
		return col < other.col;

	return row < other.row;
}

std::ostream& operator<<(std::ostream& os, const Position& other) {
	return os << Position::colIntToString(other.col) << std::to_string(other.row);
}

uint64_t Position::colStringToInt(std::string col) {
	uint64_t value = 0;
	for (char c : col)
		value = value * 26 + (c - 'A' + 1);

	return value;
}

std::string Position::colIntToString(uint64_t col) {
	std::string result;
	while (col > 0) {
		int rem = (col - 1) % 26;
		result += static_cast<char>('A' + rem);
		col = (col - 1) / 26;
	}

	std::ranges::reverse(result);
	return result;
}
