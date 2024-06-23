/**
 * Name: Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-03-14
 * 
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "IOAble.h"

using namespace std;

namespace seneca {
    ostream& operator<<(ostream& ostr, const IOAble& i) {
        return i.write(ostr);
    }

    istream& operator>>(istream& istr, IOAble& i) {
        return i.read(istr);
    }
}
