/**
 * Name: Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-03-14
 * 
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SENECA_IOABLE_H
#define SENECA_IOABLE_H

#include <iostream>

using namespace std;

namespace seneca {
    class IOAble{
    public:
        virtual ostream& write(ostream& ostr = cout) const = 0;
        virtual istream& read(istream& istr = cin) = 0;
        virtual ~IOAble() {};

        friend ostream& operator<<(ostream& ostr, const IOAble& i);
        friend istream& operator>>(istream& istr, IOAble& i);
    };
}

#endif
