#include <sstream>

#include "CellValue.hpp"

CellValue::CellValue(const std::string& contents) {
	if (contents.empty()) {
		data = std::monostate{};
		return;
	}

	std::istringstream iss(contents);
	double dbl_val;

	if (iss >> dbl_val && iss.eof())
		data = dbl_val;
	else
		data = contents;
}

CellValue::CellValue(const CellData& data) {
	this->data = data;
}

std::ostream& operator<<(std::ostream& os, const CellValue& other) {
	if (std::holds_alternative<double>(other.data))
		os << std::get<double>(other.data);
	else if (std::holds_alternative<std::string>(other.data))
		os << std::get<std::string>(other.data);

	return os;
}
