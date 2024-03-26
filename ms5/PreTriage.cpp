/**
 * Name: Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-03-25
 * 
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <iostream>
#include <fstream>
#include <cstring>

#include "PreTriage.h"
#include "Utils.h"
#include "Menu.h"
#include "TestPatient.h"
#include "TriagePatient.h"

using namespace std;

namespace seneca {
    /**
     * - Find the number of Patients in the lineup that match the type of the
     *   received Patient References.
     * - Returns the product of estimated wait time (for that type of patient)
     *   to the number of patients found.
    */
    Time PreTriage::getWaitTime(const Patient& patient) const {
        int num = 0;
        for (int i = indexOfFirstInLine(patient.type()); i >= 0 && i < m_numPatients; ++i) {
            if (*m_patients[i] == patient) ++num;
        }
        if (patient == CONTAGION) return Time(m_avgWaitContagion * num);
        if (patient == TRIAGE) return Time(m_avgWaitTriage * num);
        return Time(-1);    // This shouldn't happen?
    }

    /**
     * Adjusts the average wait time of that type of patient based on the
     * admittance time of the patient.
     * 
     * Modify and set the value of the average wait time of the corresponding
     * patient using the following formula:
     * ```
     * CT: Current Time
     * PTT: Patient's Ticket Time
     * AWT: Average Wait Time (Contagion or Triage)
     * PTN: Patient's Ticket Number
     * AWT = ((CT - PTT) + (AWT * (PTN - 1))) / PTN
     * ```
    */
    void PreTriage::setAverageWaitTime(const Patient& patient) {
        const Time CT(U.getTime());
        const Time PTT = patient.time();
        Time* AWT = &m_avgWaitContagion;
        const int PTN = patient.number();

        if (patient == TRIAGE) {
            AWT = &m_avgWaitTriage;
        }

        *AWT = ((CT - PTT) + (*AWT * (PTN - 1))) / PTN;
    }

    /**
     * Finds and returns the index of the first patient in line that matches a
     * specified type.
     * 
     * Iterates over the lineup array of pointers from the beginning. For each
     * patient, it compares the patient's type with the specified type (using the
     * overloaded `operator==`). If a match is found, the function returns the
     * found index. If the function iterates over the entire lineup without
     * finding a match, it returns -1.
    */
    int PreTriage::indexOfFirstInLine(const char patientType) const {
        for (int i = 0; i < m_numPatients; ++i) {
            if (*(m_patients[i]) == patientType) return i;
        }
        return -1;
    }

    /**
     * Loads the average wait times and the patient records from the data file
     * and stores them in the lineup array of pointers.
     * 
     * - print `"Loading data..."`, goto newline
     * - read the contagion test average wait time from the data file
     * - ignore the comma
     * - read the triage average wait time from the data file
     * - ignore the newline
     * 
     * Pseudo-code:
     * ```
     * Create a local patient-pointer
     * In a loop from 0 to the max. number of patients (or up to when reading fails)
     *      Read the first character and ignore the comma
     *      If the character is 'C'
     *          In the current patient-pointer element instantiate a Contagion Test Patient
     *      Otherwise, if the character is 'T'
     *          In the current patient-pointer element instantiate a Triage Patient
     *      Endif
     *      If instantiation successful
     *          Read the patient information from the file
     *          Add the local pointer value to the patient lineup array
     *          Increase the lineup size
     *      Endif
     * End loop
     * ```
     * - At the end print these messages and go to new line:
     * - If there are still records left in the file, print the following warning:
     *   `"Warning: number of records exceeded"` and the print the max. number of records, 
     *   for example:
     *   ```
     *   Warning: number of records exceeded 100
     *   ```
     * - If no records were read print `"No data or bad data file~"` otherwise, print
     *   `"### Records imported"` (`###` is replaced with the number of records read)
     *   Example:
     *   ```
     *   Loading data...
     *   Warning: number of records exceeded 100
     *   100 Records imported...
     *   ```
     *   ```
     *   Loading data...
     *   16 Records imported...
     *   ```
     *   ```
     *   Loading data...
     *   No data or bad data file!
     *   ```
    */
    void PreTriage::load() {
        ifstream ifstr;
        ifstr.open(m_fileName);

        cout << "Loading data..." << endl;

        ifstr >> m_avgWaitContagion;
        U.clearIstrBuffer(ifstr, ',');

        ifstr >> m_avgWaitTriage;
        U.clearIstrBuffer(ifstr);

        for (int i = 0; i < MAX_LINEUP && ifstr.good(); ++i) {
            char patientType = ifstr.get();
            U.clearIstrBuffer(ifstr, ',');

            Patient* patient = nullptr;

            if (patientType == CONTAGION) {
                patient = new TestPatient();
            } else if (patientType == TRIAGE) {
                patient = new TriagePatient();
            }

            if (patient) {
                ifstr >> *patient;
                U.clearIstrBuffer(ifstr);   // Ignore the \n at the and of the line

                m_patients[i] = patient;
                ++m_numPatients;
            }
        }

        if (ifstr.good()) cout << "Warning: number of records exceeded " << MAX_LINEUP << endl;

        if (m_numPatients)
            cout << m_numPatients << " Records imported..." << endl;
        else
            cout << "No data or bad data file!" << endl << endl;

        ifstr.close();
    }

    /**
     * 1. Opens the data file for output
     * 2. Inserts `"Saving lineup..."` into `cout` and goes to newline
     * 3. Inserts the average Contagion Test and Triage wait time, comma-separated
     *    into the data file and goes to newline
     * 4. Iterates through the lineup array of Patient pointers
     *    - Inserts them into the data file and goes to newline
     * 5. Inserts the number of records saved for each type of patient into `cout`
     *    and goes to newline
    */
    void PreTriage::save() const {
        ofstream ofstr;
        ofstr.open(m_fileName);

        cout << "Saving lineup..." << endl;

        ofstr << m_avgWaitContagion << "," << m_avgWaitTriage << endl;

        int cCnt = 0, tCnt = 0;
        for (int i = 0; i < m_numPatients; ++i) {
            const Patient& patient = *m_patients[i];

            if (patient == CONTAGION)
                ++cCnt;
            else if (patient == TRIAGE)
                ++tCnt;

            ofstr << patient << endl;
        }

        ofstr.close();

        cout << cCnt << " Contagion Tests and ";
        cout << tCnt << " Triage records were saved!" << endl;
    }

    inline int getMenuOpt(const Menu& menu) {
        int opt = 0;
        return menu >> opt;
    }

    /**
     * Register a new patient:
     * 
     * Create a Menu object for a sub-menu for patient type selection with one
     * indentation (1 \t) as follows to be displayed later:
     * ```
     *    Select Type of Registration:
     *    1- Contagion Test
     *    2- Triage
     *    0- Exit
     *    >
     * ```
     * 
     * - If the lineup size has reached the max. number of patients, print
     *   `"Line up full!"`, go to a new line and terminate the function.
     * - Display the sub-menu and receive the selection
     * - If the selection is `1`, in the next available lineup pointer instantiate
     *   a Contagion Test Patient.
     * - If the selection is `2`, in the next available lineup pointer instantiate a
     *   Triage Patient.
     * - If the selection is `0`, terminate the function
     * - Set the patient's arrival time
     * - Print `"Please enter patient information: "`
     * - Extract the patient from `cin`
     * - Go to newline
     * - Print the ticket
     *      - Print `"******************************************"`
     *      - Go to newline
     *      - Insert the patient into `cout`
     *      - Print `"Estimated Wait Time: "`
     *      - Print the return value of `getWaitTime` for the patient
     *      - Go to newline
     *      - Print `"******************************************"`
     *      - Go to newline twice
     * - Increase the lineup size 
    */
    void PreTriage::registerPatient() {
        if (m_numPatients == MAX_LINEUP) {
            cout << "Line up full!" << endl;
            return;
        }

        Patient* patient = m_patients[m_numPatients];

        switch (
            getMenuOpt(
                Menu(
                    "Select Type of Registration\n1- Contagion Test\n2- Triage", 1))) {
            case 0:
                return;
            case 1:
                patient = new TestPatient();
                break;
            case 2:
                patient = new TriagePatient();
                break;
            default:
                cerr << "This shouldn't happen!" << endl;
                return;
        }

        patient->setArrivalTime();

        cout << "Please enter patient information: ";
        cin >> *patient;
        cout << endl;

        cout << "******************************************" << endl;
        cout << *patient;
        cout << "Estimated Wait Time: " << getWaitTime(*patient) << endl;
        cout << "******************************************" << endl
             << endl;

        ++m_numPatients;
    }

    inline char getPatientType(const Menu& menu) {
        switch (getMenuOpt(menu)) {
            case 0:
                return 0;
            case 1:
                return PreTriage::CONTAGION;
            case 2:
                return PreTriage::TRIAGE;
            default:
                cerr << "This shouldn't happen!" << endl;
                return 0;
        }
    }

    /**
     * Calls the next patient in line to be admitted to the contagion test centre or
     * Triage centre
     * 
     * Create a Menu object for a sub-menu for patient type selection with one
     * indentation (1 \t) as follows to be displayed later.
     * ```
     *    Select Type of Admittance:
     *    1- Contagion Test
     *    2- Triage
     *    0- Exit
     *    > 0
     * ```
     * - Display the sub-menu and receive the selection to determine the type of
     *   patient to admit.
     * - If the selection is 1, the type is 'C'
     * - If the selection is 2, the type is 'T'
     * - If the selection is 0, terminate the function
     * - Find the index of the next patient in the line for the type (use
     *   `indexOfFirstInLine` method)
     * - If no patient is found, print `"Lineup is empty!\n"` and terminate the
     *   function
     * - Go to newline
     * - Print: `"******************************************"`
     * - Go to newline
     * - Print: `"Call time [H:M]"`
     * - Go to newline
     * - Print: `"Calling for "`
     * - Insert the patient into cout
     * - Print: `"******************************************"`
     * - Go to newline twice
     * - Set the average wait time for the patient (using `setAverageWaitTime` method)
     * - Remove the patient from the lineup using the `removeDynamicElement`
     *   function template.
    */
    void PreTriage::admit() {
        char patientType = getPatientType(
            Menu("Select Type of Admittance:\n1- Contagion Test\n2- Triage", 1));
        if (!patientType) return;

        int index = indexOfFirstInLine(patientType);
        if (index == -1) {
            cout << "Lineup is empty!" << endl;
            return;
        }

        const Patient& patient = *m_patients[index];

        cout << endl;
        cout << "******************************************" << endl;
        cout << "Call time [" << Time(U.getTime()) << "]" << endl;
        cout << "Calling for " << patient;
        cout << "******************************************" << endl
             << endl;

        setAverageWaitTime(patient);

        U.removeDynamicElement(m_patients, index, m_numPatients);
    }

    /**
     * Prints a report on patients currently in the lineup.
     * 
     * - Display a sub-menu with one indentation as follows and get the user's
     *   selection.
     *      ```
     *         Select The Lineup:
     *         1- Contagion Test
     *         2- Triage
     *         0- Exit
     *         >
     *      ```
     * - Print the following header:
     *      ```
     *      Row - Patient name                                          OHIP     Tk #  Time
     *      -------------------------------------------------------------------------------
     *      ```
     * - Iterate through the lineup array of patient pointers and insert only the
     *   type of patents selected by the user into clog.
     * - If there are no patients in the lineup print "Line up is empty!\n" instead.
     * - Close the list by printing:
     *      ```
     *      -------------------------------------------------------------------------------
     *      ```
    */
    void PreTriage::lineup() const {
        char patientType = getPatientType(
            Menu(
                "Select The Lineup:\n1- Contagion Test\n2- Triage", 1
            )
        );

        cout << "Row - Patient name                                          OHIP     Tk #  Time" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;

        int i = indexOfFirstInLine(patientType);
        if (i < 0) {
            clog << "Line up is empty!" << endl;
        } else {
            clog << *m_patients[i++];

            for (; i < m_numPatients; ++i) {
                const Patient& patient = *m_patients[i];
                if (patient == patientType) {
                    clog << patient;
                }
            }
        }

        cout << "-------------------------------------------------------------------------------" << endl;
    }

    /**
     * `fileName` will be stored in `m_fileName`.
     * `avgWaitContagion` will be init. to 15. `avgWaitTriage` will be init to 5.
     * Time values may be overwritten by values in the data file
    */
    PreTriage::PreTriage(const char* fileName)
        : m_avgWaitContagion(15), m_avgWaitTriage(5) {
        m_fileName = new char[strlen(fileName) + 1];
        strcpy(m_fileName, fileName);
        load();
    }
    
    PreTriage::~PreTriage() {
        save();

        for (int i = 0; i < m_numPatients; ++i) delete m_patients[i];

        delete[] m_fileName;
    }

    /**
     * Runs the PreTriage main application.
     * Create the Main system menu as follows
     * ```
     * General Healthcare Facility Pre-Triage Application
     * 1- Register
     * 2- Admit
     * 3- View Lineup
     * 0- Exit
     * >
     * ```
     * And get the user's selection.
     * 
     * 1. Display the menu and get the selection
     * 2. If the selection is 0, quit the method
     * 3. If the selection is 1 call the register method
     * 4. If the selection is 2 call the admit method
     * 5. If the selection is 3 call the lineup method
     * 6. Go back to 1
    */
    void PreTriage::run() {
        while (true) {
            switch (
                getMenuOpt(
                    Menu(
                        "General Healthcare Facility Pre-Triage Application\n1- Register\n2- Admit\n3- View Lineup", 0))) {
                case 0:
                    return;
                case 1:
                    registerPatient();
                    break;
                case 2:
                    admit();
                    break;
                case 3:
                    lineup();
                    break;
                default:
                    cerr << "This shouldn't happen!" << endl;
                    break;
            }
        }
    }
}
