/**
 * Name: Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-03-20
 * 
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "TriagePatient.h"
#include "Utils.h"
#include <cstring>

namespace seneca {
    int TriagePatient::nextTriageTicket = 1;

    const int SYMPTOMS_LEN = 512;

    void TriagePatient::copySymptoms(const char* symptoms) {
        delete[] m_symptoms;
        m_symptoms = new char[strlen(symptoms) + 1];
        strcpy(m_symptoms, symptoms);
    }

    TriagePatient::TriagePatient() : Patient(nextTriageTicket++) {}

    TriagePatient::~TriagePatient() { delete[] m_symptoms; }

    TriagePatient::TriagePatient(const TriagePatient& triagePatient) : Patient(triagePatient) {
        copySymptoms(triagePatient.m_symptoms);
    }
    
    TriagePatient& TriagePatient::operator=(const TriagePatient& triagePatient) {
        if (this != &triagePatient) {
            Patient::operator=(triagePatient);
            copySymptoms(triagePatient.m_symptoms);
        }
        return *this;
    }

    char TriagePatient::type() const { return 'T'; }

    std::ostream& TriagePatient::write(std::ostream& ostr) const {
        if (&ostr == &std::cout) ostr << "TRIAGE" << std::endl;

        Patient::write(ostr);

        if (&ostr == &std::cout) ostr << "Symptoms: " << m_symptoms << std::endl;

        else if (&ostr != &std::clog) ostr << "," << m_symptoms;

        return ostr;
    }

    std::istream& TriagePatient::read(std::istream& istr) {
        delete[] m_symptoms;
        Patient::read(istr);

        if (istr.fail()) {
            m_symptoms = nullptr;
            return istr;
        }

        if (&istr != &std::cin) {
            // fstream
            U.clearIstrBuffer(istr, ',');
        } else {
            // cin
            std::cout << "Symptoms: ";
        }

        char tmpSymptoms[SYMPTOMS_LEN + 1] = { 0 };
        istr.get(tmpSymptoms, SYMPTOMS_LEN + 1, '\n');
        
        m_symptoms = new char[strlen(tmpSymptoms) + 1];
        strcpy(m_symptoms, tmpSymptoms);

        if (&istr != &std::cin)
            nextTriageTicket = number() + 1;    // fstream

        return istr;
    }
}
