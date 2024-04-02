/**
 * Name: Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-03-20
 * 
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef TEST_PATIENT_H
#define TEST_PATIENT_H

#include "Patient.h"

namespace seneca {
    class TestPatient : public Patient {
        static int nextTestTicket;
    public:
        TestPatient();
        virtual char type() const override;
        virtual std::ostream& write(std::ostream& ostr = cout) const override;
        virtual std::istream& read(std::istream& istr = cin) override;
    };
}

#endif
