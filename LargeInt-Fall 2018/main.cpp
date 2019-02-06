/**
 CSC-331 Project 1, Doubly Linked List and LargeInt
 Purpose: Create two classes to implement LargeInt idea.
 
 @author Copyright © 2018 Mehmet Sahin. All rights reserved.
 @version 1.1 Created by Mehmet Sahin on 9/8/18.
 */

// @TODO: Check + and - operator with more examples to see if they behave right

#include <iostream>
#include "LargeInt.cpp" // cannot incldue hpp because of linking issue
using namespace std;

// test LargeInt with string values function prototypes 
void storeStringTest(string num);
// test LargeInt with int values function prototypes
void storeIntTest(int num);
// test LargeInt with negative values function prototypes
void negativeValueTest(int num);
// test LargeInt with addition of two negative values function prototypes
void additionOfTwoNegativeValueTest(int num1, int num2);
// test LargeInt with bigger smaller operators function prototypes
void biggerSmallerTest(int num1, int num2);
// test LargeInt with equal operator function prototypes
void equalTest(int num1, int num2);
// test LargeInt with minus operator function prototypes
void minusTest(int num1, int num2);
// test LargeInt with minus operator function prototypes
void differentSignAddTest(int num1, int num2);
// test LargeInt with multiply operator function prototypes
void multiplyTest(int num1, int num2);
// test LargeInt with division operator function prototypes
void divisionTest(int num1, int num2);
// test LargeInt with greater-than-or-equal-to operator function
void greaterThanOrEqualToTest(int num1, int num2);
// test LargeInt with less-than-or-equal-to operator function
void lessThanOrEqualToTest(int num1, int num2);
// test LargeInt with inequal operator function
void inEqualTest(int num1, int num2);
void modTest(int num1, int num2);

int main(int argc, const char * argv[]) {
    
    // storeStringTest();
    // storeIntTest();

    // negativeValueTest();

    // additionOfTwoNegativeValueTest(100, -99);

    // biggerSmallerTest(-100, -50);

    // equalTest(-10, 10);

    // minusTest(111, 110); 
    // minusTest(-2,-100);

    // differentSignAddTest(1, -10);

    // multiplyTest(-9, 9);

    // divisionTest(-102, 2);

    // greaterThanOrEqualToTest(-2,-10);

    // lessThanOrEqualToTest(-10, -2);

    // inEqualTest(1, 1);

    // modTest(-10,10);

    return 0;
}

void modTest(int num1, int num2)
{
    LargeInt l(num1);
    LargeInt l2(num2);

    LargeInt l3;
    l3 = l % l2;

    cout << num1 << " % " << num2 << ": " << l3 << endl;
}

void inEqualTest(int num1, int num2)
{
    LargeInt l(num1);
    LargeInt l2(num2);

    cout << l << " != " << l2 << ": " << (l != l2) << endl;
}

void lessThanOrEqualToTest(int num1, int num2)
{
    LargeInt l(num1);
    LargeInt l2(num2);

    cout << l << " >= " << l2 << ": " << (l <= l2) << endl;
}

void greaterThanOrEqualToTest(int num1, int num2)
{
    LargeInt l(num1);
    LargeInt l2(num2);

    cout << l << " >= " << l2 << ": " << (l >= l2) << endl;
}

void divisionTest(int num1, int num2)
{
    LargeInt l(num1);
    LargeInt l2(num2);

    LargeInt l3;
    l3 = l / l2;

    cout << num1 << " / " << num2 << ": " << l3 << endl;
}

void multiplyTest(int num1, int num2)
{
    LargeInt l(num1);
    LargeInt l2(num2);

    LargeInt l3;
    l3 = l * l2;

    cout << "multipled nums " << num1 << " and " << num2 << ": " << l3 << endl;
}

void differentSignAddTest(int num1, int num2)
{
    LargeInt l(num1);
    LargeInt l2(num2);

    LargeInt l3;
    l3 = l + l2;

    cout << "add nums " << num1 << " and " << num2 << ": " << l3 << endl;
}

void minusTest(int num1, int num2)
{
    LargeInt l(num1);
    LargeInt l2(num2);
    cout << "l: " << l << endl;
    cout << "l2: " << l2 << endl;

    LargeInt l3;
    l3 = l - l2;

    cout << "subs nums " << num1 << " and " << num2 << ": " << l3 << endl;
    cout << "l: " << l << endl;
    cout << "l2: " << l2 << endl;
}

void equalTest(int num1, int num2)
{
    LargeInt l(num1);
    LargeInt l2(num2);

    cout << l << " is equal to " << l2 << ": " << (l == l2) << endl;

}

void biggerSmallerTest(int num1, int num2)
{
    LargeInt l(num1);
    LargeInt l2(num2);

    cout << l << " is bigger than " << l2 << ": " << (l > l2) << endl;
    cout << l << " is smaller than " << l2 << ": " << (l < l2) << endl;
}

void additionOfTwoNegativeValueTest(int num1, int num2)
{
    LargeInt l(num1);
    LargeInt l2(num2);

    cout << "l: " << l << endl;
    cout << "l2: " << l2 << endl;

    LargeInt l3;
    l3 = l + l2;

    cout << "add nums " << num1 << " and " << num2 << ": " << l3 << endl;
    cout << "l: " << l << endl;
    cout << "l2: " << l2 << endl;
}

void negativeValueTest(int num)
{
    LargeInt l(num);
    cout << "num: " << l << endl;
}

void storeIntTest(int num)
{
    LargeInt l(num);
    l = num;

    cout << "num: " << l << endl;
}

void storeStringTest(string num)
{
    LargeInt l(num);
    l = num;

    cout << "num: " << l << endl;
}
