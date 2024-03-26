/**
 * Name: Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-03-20
 * 
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef TRIAGE_PATIENT_H
#define TRIAGE_PATIENT_H

#include "Patient.h"

namespace seneca {
    class TriagePatient : public Patient {
        static int nextTriageTicket;
        char* m_symptoms {};
        void copySymptoms(const char* symptoms);
    public:
        TriagePatient();
        ~TriagePatient();
        TriagePatient(const TriagePatient& triagePatient);
        TriagePatient& operator=(const TriagePatient& triagePatient);
        virtual char type() const;
        virtual std::ostream& write(std::ostream& ostr = cout) const;
        virtual std::istream& read(std::istream& istr = cin);
    };
}

#endif
