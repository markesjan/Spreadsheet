#include <cassert>
#include <iostream>
#include <sstream>

#include "Position.hpp"
#include "Spreadsheet.hpp"
#include "TestUtil.hpp"

void testCircularReference() {
	Spreadsheet ss;
	assert(ss.setCell(Position("A1"), "=B1"));
	assert(ss.setCell(Position("B1"), "=C1"));
	assert(ss.setCell(Position("C1"), "=A1"));
	assert(valueMatch(ss.getValue(Position("A1")), CellData()));
	assert(valueMatch(ss.getValue(Position("B1")), CellData()));
	assert(valueMatch(ss.getValue(Position("C1")), CellData()));
}

void testBulkDependentUpdate() {
	Spreadsheet ss;
	assert(ss.setCell(Position("A1"), "5"));
	assert(ss.setCell(Position("A2"), "4"));
	assert(ss.setCell(Position("A3"), "3"));
	assert(ss.setCell(Position("B1"), "=A1+A2+A3"));
	assert(ss.setCell(Position("C1"), "=B1*2"));
	assert(valueMatch(ss.getValue(Position("B1")), CellData(12.0)));
	assert(valueMatch(ss.getValue(Position("C1")), CellData(24.0)));
	assert(ss.setCell(Position("A2"), "40"));
	assert(valueMatch(ss.getValue(Position("B1")), CellData(48.0)));
	assert(valueMatch(ss.getValue(Position("C1")), CellData(96.0)));
}

void testSaveLoadWithStringsAndFormulas() {
	Spreadsheet out, in;
	std::ostringstream oss;
	std::istringstream iss;
	assert(out.setCell(Position("A1"), "Text1"));
	assert(out.setCell(Position("A2"), "42"));
	assert(out.setCell(Position("A3"), "=A2*2"));
	assert(out.setCell(Position("B1"), "=A1+A2"));
	assert(out.setCell(Position("C1"), "\"Hello, \"\"world\"\"!\""));
	assert(valueMatch(out.getValue(Position("A1")), CellData("Text1")));
	assert(valueMatch(out.getValue(Position("A3")), CellData(84.0)));
	assert(out.save(oss));
	iss.str(oss.str());
	iss.clear();
	assert(in.load(iss));
	assert(valueMatch(in.getValue(Position("A1")), CellData("Text1")));
	assert(valueMatch(in.getValue(Position("A2")), CellData(42.0)));
	assert(valueMatch(in.getValue(Position("A3")), CellData(84.0)));
	assert(valueMatch(in.getValue(Position("B1")), CellData("Text142.000000")));
	assert(valueMatch(in.getValue(Position("C1")), CellData("\"Hello, \"\"world\"\"!\"")));
}

void testSpreadsheetScenario() {
	Spreadsheet x0, x1;
	std::ostringstream oss;
	std::istringstream iss;
	std::string data;
	assert(x0.setCell(Position("A1"), "10"));
	assert(x0.setCell(Position("A2"), "20.5"));
	assert(x0.setCell(Position("A3"), "3e1"));
	assert(x0.setCell(Position("A4"), "=40"));
	assert(x0.setCell(Position("A5"), "=5e+1"));
	assert(x0.setCell(Position("A6"), "raw text with any characters, including a quote \" or a newline\n"));
	assert(x0.setCell(Position("A7"),
					  "=\"quoted string, quotes must be doubled: \"\". Moreover, backslashes are needed for C++.\""));
	assert(valueMatch(x0.getValue(Position("A1")), CellData(10.0)));
	assert(valueMatch(x0.getValue(Position("A2")), CellData(20.5)));
	assert(valueMatch(x0.getValue(Position("A3")), CellData(30.0)));
	assert(valueMatch(x0.getValue(Position("A4")), CellData(40.0)));
	assert(valueMatch(x0.getValue(Position("A5")), CellData(50.0)));
	assert(valueMatch(x0.getValue(Position("A6")),
					  CellData("raw text with any characters, including a quote \" or a newline\n")));
	assert(
		valueMatch(x0.getValue(Position("A7")),
				   CellData("quoted string, quotes must be doubled: \". Moreover, backslashes are needed for C++.")));
	assert(valueMatch(x0.getValue(Position("A8")), CellData()));
	assert(valueMatch(x0.getValue(Position("AAAA9999")), CellData()));
	assert(x0.setCell(Position("B1"), "=A1+A2*A3"));
	assert(x0.setCell(Position("B2"), "= -A1 ^ 2 - A2 / 2   "));
	assert(x0.setCell(Position("B3"), "= 2 ^ $A$1"));
	assert(x0.setCell(Position("B4"), "=($A1+A$2)^2"));
	assert(x0.setCell(Position("B5"), "=B1+B2+B3+B4"));
	assert(x0.setCell(Position("B6"), "=B1+B2+B3+B4+B5"));
	assert(valueMatch(x0.getValue(Position("B1")), CellData(625.0)));
	assert(valueMatch(x0.getValue(Position("B2")), CellData(-110.25)));
	assert(valueMatch(x0.getValue(Position("B3")), CellData(1024.0)));
	assert(valueMatch(x0.getValue(Position("B4")), CellData(930.25)));
	assert(valueMatch(x0.getValue(Position("B5")), CellData(2469.0)));
	assert(valueMatch(x0.getValue(Position("B6")), CellData(4938.0)));
	assert(x0.setCell(Position("A1"), "12"));
	assert(valueMatch(x0.getValue(Position("B1")), CellData(627.0)));
	assert(valueMatch(x0.getValue(Position("B2")), CellData(-154.25)));
	assert(valueMatch(x0.getValue(Position("B3")), CellData(4096.0)));
	assert(valueMatch(x0.getValue(Position("B4")), CellData(1056.25)));
	assert(valueMatch(x0.getValue(Position("B5")), CellData(5625.0)));
	assert(valueMatch(x0.getValue(Position("B6")), CellData(11250.0)));
	x1 = x0;
	assert(x0.setCell(Position("A2"), "100"));
	assert(x1.setCell(Position("A2"), "=A3+A5+A4"));
	assert(valueMatch(x0.getValue(Position("B1")), CellData(3012.0)));
	assert(valueMatch(x0.getValue(Position("B2")), CellData(-194.0)));
	assert(valueMatch(x0.getValue(Position("B3")), CellData(4096.0)));
	assert(valueMatch(x0.getValue(Position("B4")), CellData(12544.0)));
	assert(valueMatch(x0.getValue(Position("B5")), CellData(19458.0)));
	assert(valueMatch(x0.getValue(Position("B6")), CellData(38916.0)));
	assert(valueMatch(x1.getValue(Position("B1")), CellData(3612.0)));
	assert(valueMatch(x1.getValue(Position("B2")), CellData(-204.0)));
	assert(valueMatch(x1.getValue(Position("B3")), CellData(4096.0)));
	assert(valueMatch(x1.getValue(Position("B4")), CellData(17424.0)));
	assert(valueMatch(x1.getValue(Position("B5")), CellData(24928.0)));
	assert(valueMatch(x1.getValue(Position("B6")), CellData(49856.0)));
	oss.clear();
	oss.str("");
	assert(x0.save(oss));
	data = oss.str();
	iss.clear();
	iss.str(data);
	assert(x1.load(iss));
	assert(valueMatch(x1.getValue(Position("B1")), CellData(3012.0)));
	assert(valueMatch(x1.getValue(Position("B2")), CellData(-194.0)));
	assert(valueMatch(x1.getValue(Position("B3")), CellData(4096.0)));
	assert(valueMatch(x1.getValue(Position("B4")), CellData(12544.0)));
	assert(valueMatch(x1.getValue(Position("B5")), CellData(19458.0)));
	assert(valueMatch(x1.getValue(Position("B6")), CellData(38916.0)));
	assert(x0.setCell(Position("A3"), "4e1"));
	assert(valueMatch(x1.getValue(Position("B1")), CellData(3012.0)));
	assert(valueMatch(x1.getValue(Position("B2")), CellData(-194.0)));
	assert(valueMatch(x1.getValue(Position("B3")), CellData(4096.0)));
	assert(valueMatch(x1.getValue(Position("B4")), CellData(12544.0)));
	assert(valueMatch(x1.getValue(Position("B5")), CellData(19458.0)));
	assert(valueMatch(x1.getValue(Position("B6")), CellData(38916.0)));
	oss.clear();
	oss.str("");
	assert(x0.save(oss));
	data = oss.str();
	for (size_t i = 0; i < std::min<size_t>(data.length(), 10); i++)
		data[i] ^= 0x5a;
	iss.clear();
	iss.str(data);
	assert(!x1.load(iss));
	assert(x0.setCell(Position("D0"), "10"));
	assert(x0.setCell(Position("D1"), "20"));
	assert(x0.setCell(Position("D2"), "30"));
	assert(x0.setCell(Position("D3"), "40"));
	assert(x0.setCell(Position("D4"), "50"));
	assert(x0.setCell(Position("E0"), "60"));
	assert(x0.setCell(Position("E1"), "70"));
	assert(x0.setCell(Position("E2"), "80"));
	assert(x0.setCell(Position("E3"), "90"));
	assert(x0.setCell(Position("E4"), "100"));
	assert(x0.setCell(Position("F10"), "=D0+5"));
	assert(x0.setCell(Position("F11"), "=$D0+5"));
	assert(x0.setCell(Position("F12"), "=D$0+5"));
	assert(x0.setCell(Position("F13"), "=$D$0+5"));
	x0.copyRect(Position("G11"), Position("F10"), 1, 4);
	assert(valueMatch(x0.getValue(Position("F10")), CellData(15.0)));
	assert(valueMatch(x0.getValue(Position("F11")), CellData(15.0)));
	assert(valueMatch(x0.getValue(Position("F12")), CellData(15.0)));
	assert(valueMatch(x0.getValue(Position("F13")), CellData(15.0)));
	assert(valueMatch(x0.getValue(Position("F14")), CellData()));
	assert(valueMatch(x0.getValue(Position("G10")), CellData()));
	assert(valueMatch(x0.getValue(Position("G11")), CellData(75.0)));
	assert(valueMatch(x0.getValue(Position("G12")), CellData(25.0)));
	assert(valueMatch(x0.getValue(Position("G13")), CellData(65.0)));
	assert(valueMatch(x0.getValue(Position("G14")), CellData(15.0)));
	x0.copyRect(Position("G11"), Position("F10"), 2, 4);
	assert(valueMatch(x0.getValue(Position("F10")), CellData(15.0)));
	assert(valueMatch(x0.getValue(Position("F11")), CellData(15.0)));
	assert(valueMatch(x0.getValue(Position("F12")), CellData(15.0)));
	assert(valueMatch(x0.getValue(Position("F13")), CellData(15.0)));
	assert(valueMatch(x0.getValue(Position("F14")), CellData()));
	assert(valueMatch(x0.getValue(Position("G10")), CellData()));
	assert(valueMatch(x0.getValue(Position("G11")), CellData(75.0)));
	assert(valueMatch(x0.getValue(Position("G12")), CellData(25.0)));
	assert(valueMatch(x0.getValue(Position("G13")), CellData(65.0)));
	assert(valueMatch(x0.getValue(Position("G14")), CellData(15.0)));
	assert(valueMatch(x0.getValue(Position("H10")), CellData()));
	assert(valueMatch(x0.getValue(Position("H11")), CellData()));
	assert(valueMatch(x0.getValue(Position("H12")), CellData()));
	assert(valueMatch(x0.getValue(Position("H13")), CellData(35.0)));
	assert(valueMatch(x0.getValue(Position("H14")), CellData()));
	assert(x0.setCell(Position("F0"), "-27"));
	assert(valueMatch(x0.getValue(Position("H14")), CellData(-22.0)));
	x0.copyRect(Position("H12"), Position("H13"), 1, 2);
	assert(valueMatch(x0.getValue(Position("H12")), CellData(25.0)));
	assert(valueMatch(x0.getValue(Position("H13")), CellData(-22.0)));
	assert(valueMatch(x0.getValue(Position("H14")), CellData(-22.0)));
}

void integrationTest() {
	testCircularReference();
	testBulkDependentUpdate();
	testSaveLoadWithStringsAndFormulas();
	testSpreadsheetScenario();
	std::cout << "All integration tests passed!" << std::endl;
}
