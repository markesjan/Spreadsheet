#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include "Position.hpp"
#include "Spreadsheet.hpp"
#include "TestUtil.hpp"

void testSetCellAndGetValueNumeric() {
	Spreadsheet ss;
	Position pos("A1");
	assert(ss.setCell(pos, "42"));
	auto val = ss.getValue(pos);
	assert(std::holds_alternative<double>(val));
	assert(valueMatch(val, 42.0));
}

void testSetCellAndGetValueString() {
	Spreadsheet ss;
	Position pos("B2");
	assert(ss.setCell(pos, "Hello"));
	auto val = ss.getValue(pos);
	assert(std::holds_alternative<std::string>(val));
	assert(valueMatch(val, "Hello"));
}

void testGetEmptyCell() {
	Spreadsheet ss;
	auto val = ss.getValue(Position("D5"));
	assert(std::holds_alternative<std::monostate>(val));
}

void testSetInvalidCell() {
	Spreadsheet ss;
	Position pos("A1");
	bool res = ss.setCell(pos, "=1+");
	assert(!res);
	auto val = ss.getValue(pos);
	assert(std::holds_alternative<std::monostate>(val));
}

void testSaveAndLoad() {
	Spreadsheet ss;
	ss.setCell(Position("A1"), "56");
	ss.setCell(Position("B2"), "String");

	std::stringstream ssout;
	ss.save(ssout);
	std::string saved = ssout.str();

	Spreadsheet ss2;
	std::stringstream ssin(saved);
	assert(ss2.load(ssin));

	auto v1 = ss2.getValue(Position("A1"));
	auto v2 = ss2.getValue(Position("B2"));
	assert(valueMatch(v1, 56.0));
	assert(valueMatch(v2, "String"));
}

void testCopyRectOneCell() {
	Spreadsheet ss;
	ss.setCell(Position("A1"), "123");
	ss.copyRect(Position("C3"), Position("A1"), 1, 1);
	auto v = ss.getValue(Position("C3"));
	assert(std::holds_alternative<double>(v));
	assert(std::get<double>(v) == 123.0);
}

void testCopyRectManyCells() {
	Spreadsheet ss;
	ss.setCell(Position("A1"), "1");
	ss.setCell(Position("B1"), "2");
	ss.setCell(Position("A2"), "3");
	ss.setCell(Position("B2"), "Four");
	ss.copyRect(Position("C3"), Position("A1"), 2, 2);

	auto v1 = ss.getValue(Position("C3"));
	auto v2 = ss.getValue(Position("D3"));
	auto v3 = ss.getValue(Position("C4"));
	auto v4 = ss.getValue(Position("D4"));
	assert(valueMatch(v1, 1.0));
	assert(valueMatch(v2, 2.0));
	assert(valueMatch(v3, 3.0));
	assert(valueMatch(v4, "Four"));
}

void spreadsheetTest() {
	testSetCellAndGetValueNumeric();
	testSetCellAndGetValueString();
	testGetEmptyCell();
	testSetInvalidCell();
	testSaveAndLoad();
	testCopyRectOneCell();
	testCopyRectManyCells();
	std::cout << "All Spreadsheet tests passed!" << std::endl;
}
