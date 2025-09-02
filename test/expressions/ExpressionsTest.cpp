#include <iostream>

void testAddExpr();
void testDivExpr();
void testMulExpr();
void testNegExpr();
void testPowExpr();
void testSubExpr();
void testEqExpr();
void testGeExpr();
void testGtExpr();
void testLeExpr();
void testLtExpr();
void testNeExpr();
void testValNumExpr();
void testValRefExpr();
void testValStrExpr();

void expressionsTest() {
	testAddExpr();
	testDivExpr();
	testMulExpr();
	testNegExpr();
	testPowExpr();
	testSubExpr();
	testEqExpr();
	testGeExpr();
	testGtExpr();
	testLeExpr();
	testLtExpr();
	testNeExpr();
	testValNumExpr();
	testValRefExpr();
	testValStrExpr();
	std::cout << "All Expressions tests passed!" << std::endl;
}
