#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include "CellValue.hpp"
#include "TestUtil.hpp"

void testCellValueNumeric() {
	CellValue cv(std::string("42"));
	assert(std::holds_alternative<double>(cv.data));
	assert(valueMatch(cv.data, 42.0));
}

void testCellValueDoubleScientific() {
	CellValue cv(std::string("3e2"));
	assert(std::holds_alternative<double>(cv.data));
	assert(valueMatch(cv.data, 3e2));
}

void testCellValueString() {
	CellValue cv(std::string("hello world"));
	assert(std::holds_alternative<std::string>(cv.data));
	assert(valueMatch(cv.data, std::string("hello world")));
}

void testCellValueEmpty() {
	CellValue cv(std::string(""));
	assert(std::holds_alternative<std::monostate>(cv.data));
}

void testCellValueFromCellDataNumeric() {
	CellValue cv(CellData(123.45));
	assert(std::holds_alternative<double>(cv.data));
	assert(valueMatch(cv.data, 123.45));
}

void testCellValueFromCellDataString() {
	CellValue cv(CellData(std::string("abc")));
	assert(std::holds_alternative<std::string>(cv.data));
	assert(valueMatch(cv.data, std::string("abc")));
}

void testCellValueFromCellDataEmpty() {
	CellValue cv(CellData({}));
	assert(std::holds_alternative<std::monostate>(cv.data));
}

void testCellValueOutputOperatorNumeric() {
	std::ostringstream oss;
	CellValue cv(std::string("100"));
	oss.str("");
	oss.clear();
	oss << cv;
	assert(oss.str() == "100");
}

void testCellValueOutputOperatorString() {
	std::ostringstream oss;
	CellValue cv(std::string("hello"));
	oss.str("");
	oss.clear();
	oss << cv;
	assert(oss.str() == "hello");
}

void testCellValueOutputOperatorEmpty() {
	std::ostringstream oss;
	CellValue cv(std::string(""));
	oss.str("");
	oss.clear();
	oss << cv;
	assert(oss.str() == "");
}

void cellValueTest() {
	testCellValueNumeric();
	testCellValueDoubleScientific();
	testCellValueString();
	testCellValueEmpty();
	testCellValueFromCellDataNumeric();
	testCellValueFromCellDataString();
	testCellValueFromCellDataEmpty();
	testCellValueOutputOperatorNumeric();
	testCellValueOutputOperatorString();
	testCellValueOutputOperatorEmpty();
	std::cout << "All CellValue tests passed!" << std::endl;
}
