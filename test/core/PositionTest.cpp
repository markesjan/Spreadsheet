#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include "Position.hpp"

void testPositionValid() {
	Position p("A1");
	assert(p == Position("A1"));

	Position q("Z99");
	assert(q == Position("Z99"));

	Position r("AA10");
	assert(r == Position("AA10"));
}

void testPositionInvalid() {
	try {
		Position p("123");
		assert(false && "Expected exception not thrown");
	} catch (const std::invalid_argument&) {
	}

	try {
		Position p("A");
		assert(false && "Expected exception not thrown");
	} catch (const std::invalid_argument&) {
	}

	try {
		Position p("1A");
		assert(false && "Expected exception not thrown");
	} catch (const std::invalid_argument&) {
	}
}

void testPositionDistance() {
	Position p("A1");
	Position q("C5");

	auto [dx, dy] = p.distance(q);
	assert(dx == 'C' - 'A');
	assert(dy == 5 - 1);
}

void testPositionShift() {
	Position p("B2");
	Position shifted = p.shift(2, 3);

	assert(shifted == Position("D5"));
}

void testPositionPrint() {
	Position p("C7");
	std::string s1 = p.print(false, false);
	std::string s2 = p.print(true, false);
	std::string s3 = p.print(false, true);
	std::string s4 = p.print(true, true);

	assert(s1 == "C7");
	assert(s2 == "$C7");
	assert(s3 == "C$7");
	assert(s4 == "$C$7");
}

void testLargePositionPrint() {
	Position p("ZZZ999");
	std::string s1 = p.print(false, false);
	std::string s2 = p.print(true, false);
	std::string s3 = p.print(false, true);
	std::string s4 = p.print(true, true);

	assert(s1 == "ZZZ999");
	assert(s2 == "$ZZZ999");
	assert(s3 == "ZZZ$999");
	assert(s4 == "$ZZZ$999");
}

void testPositionOperators() {
	Position p("A1");
	Position q("A2");
	Position r("B1");

	assert(p < q);
	assert(p < r);
	assert(!(q < p));
	assert(p == Position("A1"));
}

void testPositionOutputOperator() {
	Position p("AB12");
	std::ostringstream oss;
	oss << p;
	assert(oss.str() == "AB12");
}

void positionTest() {
	testPositionValid();
	testPositionInvalid();
	testPositionDistance();
	testPositionShift();
	testPositionPrint();
	testLargePositionPrint();
	testPositionOperators();
	testPositionOutputOperator();
	std::cout << "All Position tests passed!" << std::endl;
}
