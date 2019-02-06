//
//  LargeInt.cpp
//  csc311Project1
//
//  Created by Mehmet Sahin on 9/14/18.
//  Copyright © 2018 Mehmet Sahin. All rights reserved.
//

#include "LargeInt.hpp"
#include <string>

LargeInt:: LargeInt(const std::string& num)
{
    fillTheList(num);
}

LargeInt:: LargeInt(int num)
{
    fillTheList(num);
}

LargeInt:: LargeInt(const UDList<int> &l)
{
    list = l;
}
// could override what is inside
void LargeInt:: operator= (const LargeInt& other)
{
    UDList<int>::iterator head = list.begin();
    if (head){
        list.makeEmpty();
    }
    list = other.list;
    this->negative = other.negative;
}

void LargeInt:: operator= (const UDList<int>& otherlist)
{
    list = otherlist;
}

// could override what is inside
void LargeInt:: operator= (const std::string& num)
{
    UDList<int>::iterator head = list.begin();
    if (head){
        list.makeEmpty();
    }
    fillTheList(num);
}

void LargeInt:: operator= (int num)
{
    UDList<int>::iterator head = list.begin();
    if (head){
        list.makeEmpty();
    }
    fillTheList(num);
}

// could override what is inside
void LargeInt:: fillTheList(const std::string& num)
{
    long size = num.size();
    int i = 0;
    if (size > 0){
        if (num[0] == '-'){
            negative = true;
            i = 1;
        }else {
            negative = false;
        }
        while (i < size) {
            if (!isdigit(num[i])){
                std::cout << string("Bad data type");
                return;
            }
            list.insertBack(num[i] - '0');
            i++;
        }
    }
}

void LargeInt:: fillTheList(int num)
{
    if (num == 0){
        list.insertFront(num);
        negative = false;
    }else if (num < 0){
        negative = true;
        num = num * -1;
    }else{
        negative = false;
    }
    while (num) {
        list.insertFront(num % 10);
        num = num / 10;
    }
}

LargeInt LargeInt:: abs(const LargeInt& other) 
{
    LargeInt temp = other;
    if (temp.negative) temp.negative = false;
    return temp;
}

UDList<int> LargeInt:: add(const LargeInt& thisObject, const LargeInt& other)
{
    UDList<int> temp;
    bool carry = false;
    UDList<int>::iterator ithis = thisObject.list.end();
    UDList<int>::iterator iother = other.list.end();

    while (ithis || iother)
    {
        int total = 0;
        if (carry) total += 1;
        if (ithis && iother){
            total += (ithis->info + iother->info);
            ithis = ithis->prev;
            iother = iother->prev;
        }else if (ithis){
            total += ithis->info;
            ithis = ithis->prev;
        }else{
            total += iother->info;
            iother = iother->prev;
        }
        
        if (total > 9){
            carry = true;
            temp.insertFront(total % 10);
        }else{
            carry = false;
            temp.insertFront(total);
        }
    }
    if (carry) temp.insertFront(1);
    return temp;
}

LargeInt LargeInt:: operator+ (const LargeInt& other)
{
    LargeInt temp;
    if ( bothNegative(other) ) {
        temp = add((*this), other);
        temp.negative = true;
    } else if ( bothPositive(other) ){
        temp = add((*this), other);
        temp.negative = false;
    } else {
        LargeInt absThis = abs(*this);
        LargeInt absOther = abs(other);
        bool thisFirst = true; // assume this should be first

        if (absThis == absOther) {
            temp.list.insertFront(0);
            temp.negative = false;
        }else if (this->negative) {
            if (absThis > absOther){
                temp.negative = true;
            }else{
                thisFirst = false;
            }
        }else {
            if (absThis < absOther){
                thisFirst = false;
                temp.negative = true;
            }
        }
        temp = (thisFirst ? subs((*this), other) : subs(other, (*this)));
    }
    return temp;
}

UDList<int> LargeInt:: subs(const LargeInt& thisObject, const LargeInt& other)
{
    LargeInt copyThis(thisObject); // create a copy to make sure to NOT modify
    UDList<int> temp;
    UDList<int>::iterator p;
    UDList<int>::iterator first = copyThis.list.end();
    UDList<int>::iterator second = other.list.end();

    while (first || second)
    {
        int num = 0;
        if (first && second ) {
            if (first->info < second->info) {
                p = first->prev;
                while (p->info == 0)
                    p = p->prev;
                p->info -= 1;
                p = p->next;
                while (p != first) {
                    p->info += 10;
                    p->info -= 1;
                    p = p->next;
                }
                p->info += 10;
            }
            num = first->info - second->info;
            temp.insertFront(num);
            second = second->prev;
        }else {
            if ( (first->info == 0) && !first->prev ) {
                
            }else {
                temp.insertFront(first->info);
            }
        }
        first = first->prev;
    }

    return temp;
}

LargeInt LargeInt:: operator- (const LargeInt& other)
{
    LargeInt temp;
    bool thisFirst = true; // assume this should be first
    if ( bothNegative(other) || bothPositive(other) ){
        if ( ((*this) == other) ) {
            temp.list.insertFront(0);
            temp.negative = false;
        }else {
            if ( bothNegative(other) ) {
                if ((*this) > other){
                    thisFirst = false;
                }else{
                    temp.negative = true;
                }
            } else if ( bothPositive(other) ){
                if ((*this) < other){
                    thisFirst = false;
                    temp.negative = true;
                }
            }
            temp = (thisFirst ? subs((*this), other) : subs(other, (*this)));
        }
    }else {
        if (this->negative) {
            temp.negative = true;
        }else{
            temp.negative = false;
        }
        temp = add((*this), other);
    }
    return temp;
}

LargeInt LargeInt:: operator* (const LargeInt& other)
{
    LargeInt temp( abs(*this) );
    LargeInt temp2 = abs(other); // this will be a counter to keep track of how many times to add
    LargeInt subsObject(1);
    UDList<int>::iterator ithis = list.begin();
    UDList<int>::iterator itemp2 = temp2.list.begin();

    if (ithis && itemp2) {

        if ( (ithis->info != 0) && (itemp2->info != 0) ) {
            while ( !(temp2 == subsObject) ) {
                temp = add(temp, (*this)); // add function does not care about sign
                temp2 = (temp2 - subsObject);
            }
        }

        if ( !bothNegative(other) && !bothPositive(other) )
            temp.negative = true;
    }

    return temp;
}

LargeInt LargeInt:: operator/ (const LargeInt& other) 
{
    LargeInt temp( abs(*this) );
    LargeInt temp2 = abs(other);
    LargeInt result(0); // counter to check how many times it can be substracted
    LargeInt addObject(1);

    UDList<int>::iterator ithis = list.begin();
    UDList<int>::iterator itemp2 = temp2.list.begin();

    if (ithis && itemp2) {
        
        if ( itemp2->info == 0 ) {
            std::cout << "Cannot be divided!!" << std::endl;
            return NULL;
        }

        if ( (ithis->info != 0) ) {

            while ( !(temp < temp2) ) {
                result = (result + addObject);
                temp = (temp - temp2);
            }
            
        }

        if ( !bothNegative(other) && !bothPositive(other) )
            result.negative = true;
    }

    return result;
}

LargeInt LargeInt:: operator% (const LargeInt& other)
{        
    LargeInt temp( abs(*this) );
    LargeInt temp2 = abs(other);
    LargeInt result(0); // counter to check how many times it can be substracted
    LargeInt addObject(1);

    if (temp == temp2)
        return result;

    UDList<int>::iterator ithis = list.begin();
    UDList<int>::iterator itemp2 = temp2.list.begin();

    if (ithis && itemp2) {
        
        if ( itemp2->info == 0 ) {
            std::cout << "Cannot be divided!!" << std::endl;
            return NULL;
        }

        if ( (ithis->info != 0) ) {

            while ( !(temp < temp2) ) {
                result = (result + addObject);
                temp = (temp - temp2);
            }
            
        }

        if ( !bothNegative(other) && !bothPositive(other) )
            result.negative = true;
    }

    return temp;
}

bool LargeInt:: equality(const LargeInt& other) 
{
    UDList<int>::iterator ithis = list.begin();
    UDList<int>::iterator iother = other.list.begin();
    bool same = true;

    while (ithis && iother) {
        if (ithis->info != iother->info){
            same = false;
            break;
        }
        ithis = ithis->next;
        iother = iother->next;
    }
    return same;
}

bool LargeInt:: operator== (const LargeInt& other)
{
    bool same = false;
    
    if ( thisSameLengthAsOther(other) && ( bothPositive(other) || bothNegative(other) )) {
        same = equality(other);
    }
    
    return same;
}

bool LargeInt:: operator!= (const LargeInt& other)
{
    return !( (*this) == other ); // if it is not equal, it must be inequal!
}

// -1 < 2 or 1 < -2 or 10 < 5 or -5 < -10
bool LargeInt:: operator< (const LargeInt& other)
{
    UDList<int>::iterator ithis = list.begin();
    UDList<int>::iterator iother = other.list.begin();
    bool smaller = thisSameLengthAsOther(other);
    bool same = false;

    if ( this->negative && !other.negative ) {
        smaller = true;
    }else if ( !this->negative && other.negative ) {
        smaller = false;
    }else if ( thisSameLengthAsOther(other) && bothPositive(other) ) {
        while (ithis && iother) {
            if (ithis->info < iother->info) {
                smaller = true;
                same = false;
                break;
            }else if (ithis->info > iother->info) {
                smaller = false;
                break;
            }else {
                same = true;
            }
            ithis = ithis->next;
            iother = iother->next;
        }
    }else if ( this->negative && other.negative ){
        if ( thisSameLengthAsOther(other) ){
            while (ithis && iother) {
                if (ithis->info > iother->info) {
                    smaller = true;
                    same = false;
                    break;
                }else if (ithis->info < iother->info) {
                    smaller = false;
                    break;
                }else {
                    same = true;
                }
                ithis = ithis->next;
                iother = iother->next;
            }
        }else{
            smaller = (this->list.getLength() > other.list.getLength());
        }
    }
    if (same) smaller = false;
    return smaller;
}

bool LargeInt:: operator<= (const LargeInt& other)
{
    return !( (*this) > other ); // if it is not bigger, it must be less or equal!
}

bool LargeInt:: operator> (const LargeInt& other) 
{
    UDList<int>::iterator ithis = list.begin();
    UDList<int>::iterator iother = other.list.begin();
    bool bigger = thisBiggerLengthThanOther(other);
    bool same = false;

    if ( this->negative && !other.negative ) {
        bigger = false;
    }else if ( !this->negative && other.negative ){
        bigger = true;
    }else if ( thisSameLengthAsOther(other) && bothPositive(other) ) {
        while (ithis && iother) {
            if (ithis->info > iother->info) {
                bigger = true;
                same = false;
                break;
            }else if (ithis->info < iother->info) {
                bigger = false;
                break;
            }else {
                same = true;
            }
            ithis = ithis->next;
            iother = iother->next;
        }
    }else if ( bothNegative(other) ){
        if ( thisSameLengthAsOther(other) ){
            while (ithis && iother) {
                if (ithis->info < iother->info) {
                    bigger = true;
                    same = false;
                    break;
                }else if (ithis->info > iother->info) {
                    bigger = false;
                    break;
                }else {
                    same = true;
                }
                ithis = ithis->next;
                iother = iother->next;
            }
        }else{
            bigger = (this->list.getLength() < other.list.getLength());
        }
    }
    if (same) bigger = false;
    return bigger;
}

bool LargeInt:: operator>= (const LargeInt& other)
{
    return !( (*this) < other );
}


std::ostream& operator<< (std::ostream& out, const LargeInt& largeInt)
{
    UDList<int>::iterator it = largeInt.list.begin();
    if (largeInt.negative) {
        out << '-';
    }
    while (it) {
        out << it->info;
        it = it->next;
    }
    return out;
}

// could override what is inside ???? check with professor
std::istream& operator>> (std::istream& in,LargeInt& largeInt)
{
    std::string num;
    in >> num;
    if (largeInt.list.getLength() == 0)
        largeInt = num;
    return in;
}



void LargeInt:: print() const
{
    if (this->negative) {
        std::cout << '-';
    }
    list.printFromFront();
}

// Helper functions
bool LargeInt:: thisSameLengthAsOther(const LargeInt& other)
{
    return (this->list.getLength() == other.list.getLength());
}

bool LargeInt:: thisSmallerLengthThanOther(const LargeInt& other)
{
    return (this->list.getLength() < other.list.getLength());
}

bool LargeInt:: thisBiggerLengthThanOther(const LargeInt& other)
{
    return (this->list.getLength() > other.list.getLength());
}

bool LargeInt:: bothNegative(const LargeInt& other)
{
    return (this->negative && other.negative);
}

bool LargeInt:: bothPositive(const LargeInt& other)
{
    return (!this->negative && !other.negative);
}