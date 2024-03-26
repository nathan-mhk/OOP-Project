/**
 * Name: Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-03-25
 * 
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef PRETRIAGE_H
#define PRETRIAGE_H

#include "Time.h"
#include "Patient.h"

namespace seneca {
    class PreTriage {
        static const int MAX_LINEUP = 100;
        Time m_avgWaitContagion {};
        Time m_avgWaitTriage {};
        Patient* m_patients[MAX_LINEUP] {};
        char* m_fileName {};
        int m_numPatients {};   // <= MAX_LINEUP

        /**
         * - Find the number of Patients in the lineup that match the type of the
         *   received Patient References.
         * - Returns the product of estimated wait time (for that type of patient)
         *   to the number of patients found.
        */
        Time getWaitTime(const Patient& patient) const;

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
        void setAverageWaitTime(const Patient& patient);

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
        int indexOfFirstInLine(const char patientType);

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
        void load();

        /**
         * 1. Opens the data file for output
         * 2. Inserts `"Saving lineup..."` into cout and goes to newline
         * 3. Inserts the average Contagion Test and Triage wait time, comma-separated
         *    into the data file and goes to newline
         * 4. Iterates through the lineup array of Patient pointers
         *    - Inserts them into the data file and goes to newline
         * 5. Inserts the number of records saved for each type of patient into `cout`
         *    and goes to newline
        */
        void save();

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
        void registerPatient();

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
        void admit();

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
        void lineup();

    public:
        /**
         * `fileName` will be stored in `m_fileName`.
         * `avgWaitContagion` will be init. to 15. `avgWaitTriage` will be init to 5.
         * Time values may be overwritten by values in the data file
        */
        PreTriage(char* fileName);
        ~PreTriage();

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
        void run();
    };
}

#endif
