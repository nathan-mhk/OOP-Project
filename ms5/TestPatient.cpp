/**
 * Name: Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-03-20
 * 
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "TestPatient.h"

namespace seneca {
    int TestPatient::nextTestTicket = 1;

    TestPatient::TestPatient() : Patient(nextTestTicket++) {}

    char TestPatient::type() const { return 'C'; }

    std::ostream& TestPatient::write(std::ostream& ostr) const {
        if (&ostr == &std::cout) ostr << "Contagion TEST" << endl;
        return Patient::write(ostr);
    }

    std::istream& TestPatient::read(std::istream& istr) {
        Patient::read(istr);

        if (&istr != &std::cin)
            nextTestTicket = number() + 1;  // fstream

        return istr;
    }
}
