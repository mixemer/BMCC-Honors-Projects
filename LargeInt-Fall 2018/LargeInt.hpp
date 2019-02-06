//
//  LargeInt.hpp
//  csc311Project1
//
//  Created by Mehmet Sahin on 9/14/18.
//  Copyright © 2018 Mehmet Sahin. All rights reserved.
//

#ifndef LargeInt_hpp
#define LargeInt_hpp

#include <iostream>
#include "UDList.cpp"
using namespace std;

// TODO: ask prof if it is okey to use (=) to insert or should it stop if overrides

class LargeInt{
private:
    UDList<int> list; // an empty doubly linked list

    bool negative;
    
    /**
     * fills the list with given string num by parting num into individual digits.
     * will be used for constructor and assignment oporator
     * @param num is an string
     */
    void fillTheList(const std::string& num);

    /**
     * fills the list with given int num by parting num into individual digits.
     * will be used for constructor and assignment oporator
     * @param num is an int
     */
    void fillTheList(int num);

    /**
     * Adds all the number digits of the both this and otehr LargeInt objects.
     * @param other is a reference to LargeInt object
     * @return UDList<x> object that was added by this and other LargeInt
     */
    UDList<int> add(const LargeInt& thisObject, const LargeInt& other);

    /**
     * Substracts number digits of other LargeInt objects from this.
     * @param other is a reference to LargeInt object
     * @return LargeInt that was a result of substraction
     */
    UDList<int> subs(const LargeInt& thisObject, const LargeInt& other); // UDList<int>::iterator first, UDList<int>::iterator second
    
    /**
     * Absolute value of given LargeInt object, other
     * @param other is a reference to LargeInt object
     * @return LargeInt that was a result of absolute value of other
     */
    LargeInt abs(const LargeInt& other);

    /**
     * equality function to check if this and other LargeInt objects contain the same data
     * @param other is a reference to LargeInt object
     * @return bool that was a result of checking if this and other objects are the same
     */
    bool equality(const LargeInt& other);

    // helper functions
    bool thisSameLengthAsOther(const LargeInt& other);
    bool thisSmallerLengthThanOther(const LargeInt& other);
    bool thisBiggerLengthThanOther(const LargeInt& other);
    bool bothNegative(const LargeInt& other);
    bool bothPositive(const LargeInt& other);
public:
    LargeInt() { negative = false; };
    
    /**
     * Overloaded constructor so it can get an string num so it can fill the nodes of the list with digits of the num
     * @param num is an string
     */
    LargeInt(const std::string& num);

    /**
     * Overloaded constructor so it can get an int num so it can fill the nodes of the list with digits of the num
     * @param num is an int
     */
    LargeInt(int num);
    
    /**
     * copy constructor to copy other object's data into this object.
     * @param other is a reference to UDList<x> object
     */
    LargeInt(const UDList<int>& other);
    
    /**
     * Overloaded assignment operator to copy other object's data into this object.
     * @param other is a reference to LargeInt object
     */
    void operator= (const LargeInt& other);

    /**
     * Overloaded assignment operator to copy other object's list into this object.
     * @param other is a reference to UDList<x> object
     */
    void operator= (const UDList<int>& otherlist);
    
    /**
     * Overloaded assignment operator fills the nodes of the list with digits of the num
     * @param num is an string
     */
    void operator= (const std::string& num);

    /**
     * Overloaded assignment operator fills the nodes of the list with digits of the num
     * @param num is an int
     */
    void operator= (int num);
    
    /**
     * Adds all the number digits of the both this and otehr LargeInt objects.
     * @param other is a reference to LargeInt object
     * @return LargeInt that was added by this and other LargeInt
     */
    LargeInt operator+ (const LargeInt& other);

    /**
     * Substracts number digits of other LargeInt objects from this.
     * @param other is a reference to LargeInt object
     * @return LargeInt that was a result of substraction
     */
    LargeInt operator- (const LargeInt& other);

    /**
     * Multiplication number digits of other LargeInt objects from this.
     * @param other is a reference to LargeInt object
     * @return LargeInt that was a result of Multiplication
     */
    LargeInt operator* (const LargeInt& other);

    /**
     * Division number digits of other LargeInt objects from this.
     * @param other is a reference to LargeInt object
     * @return LargeInt that was a result of Division
     */
    LargeInt operator/ (const LargeInt& other);

    /**
     * Division number digits of other LargeInt objects from this.
     * @param other is a reference to LargeInt object
     * @return LargeInt that was a result of Division
     */
    LargeInt operator% (const LargeInt& other);
    
    /**
     * Overloaded bool operator to check if this and other LargeInt objects contain the same data
     * @param other is a reference to LargeInt object
     */
    bool operator== (const LargeInt& other);

    /**
     * Overloaded inequality operator to check if this object is inequal to other LargeInt object
     * @param other is a reference to LargeInt object
     */
    bool operator!= (const LargeInt& other);

    /**
     * Overloaded bool operator to check if this object is smaller than other object
     * @param other is a reference to LargeInt object
     */
    bool operator< (const LargeInt& other);

    /**
     * Overloaded less-than-or-equal-to operator to check if this object is less or equal to other LargeInt object
     * @param other is a reference to LargeInt object
     */
    bool operator<= (const LargeInt& other);

    /**
     * Overloaded bool operator to check if this object is bigger than other object
     * @param other is a reference to LargeInt object
     */
    bool operator> (const LargeInt& other);

    /**
     * Overloaded greater-than-or-equal-to operator to check if this object is bigger or equal to other LargeInt object
     * @param other is a reference to LargeInt object
     */
    bool operator>= (const LargeInt& other);
    
    /**
     * Overloaded output operator to output data of this object to files
     * @param out is a reference to istream object
     * @largeInt is areference to LargeInt object
     */
    friend std::ostream& operator<< (std::ostream& out, const LargeInt& largeInt);
    
    /**
     * Overloaded input operator to get data from and file and store it in this LargeInt object.
     * @param in is a reference to istream object
     * @largeInt is areference to LargeInt object
     */
    friend std::istream& operator>> (std::istream& in, LargeInt& largeInt);
    
    /**
     * Prints the information of nodes of this list
     */
    void print() const;
};

#endif /* LargeInt_hpp */











