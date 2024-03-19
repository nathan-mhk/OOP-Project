/**
 * Name: Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-03-18
 * 
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include "Patient.h"

namespace seneca {
    /**
     * Instantiate a Patient object by providing a ticket number (an
     * integer). This ticket number will be utilized to initialize the
     * Ticket member attribute.
    */
    Patient::Patient(int ticketNum) {
        m_ticket = new Ticket(ticketNum);
    }

    Patient::Patient(Patient&) {}

    Patient& Patient::operator=(Patient& patient) {
        return patient;
    }

    Patient::~Patient() {
        delete m_ticket;
    }

    /**
     * Return true if the values returned by the `type` function of this
     * patient and the provided single character are identical.
    */
    bool Patient::operator==(const char) const {
        return false;
    }

    /**
     * Return true if the type of the current patient is the same as the
     * type of the other patient; otherwise, return false.
    */
    bool Patient::operator==(const Patient&) const {
        return false;
    }

    /**
     * Sets the time of the patient's ticket to the current time
    */
    void Patient::setArrivalTime() {}

    Time Patient::time() const {
        return m_ticket->time();
    }

    int Patient::number() const {
        return 0;
    }

    /**
     * Return true if the Patient is in a valid state; otherwise, return
     * false.
    */
    Patient::operator bool() const {
        return false;
    }

    /**
     * Return the address of the patient's name.
    */
    Patient::operator const char*() const {
        return m_name;
    }

    /**
     * Inserts information into the ostream reference in three different
     * formats based on the instance of the ostream. For `cout`, it
     * inserts detailed information suitable for printing like a ticket
     * in multiline format. For `clog`, it presumes a list is being
     * printed, and therefore the information is inserted in a linear
     * format suitable for a list. For any other object, it will insert
     * the values in a comma-separated format suitable for saving in a
     * file.
     * 
     * 1. If the patient is being inserted into the `clog` object, the
     *    information is displayed in a linear format as follows:
     *      - If the patient is in an invalid empty state
     *          - Insert "Invalid Patient Record".
     *      - Otherwise
     *          - Insert the name of the patient in 53 spaces,
     *            left-justified, padded with '.' characters.
     *          - Insert the OHIP number.
     *          - Insert the ticket number in 5 spaces, right-justified.
     *          - Insert a space.
     *          - Insert the ticket time.
     * 
     * 2. If the patient is being inserted into the `cout` object,
     *    the information is inserted as follows:
     *      - If the patient is in an invalid empty state
     *          - Insert "Invalid Patient Record" and go to a newline.
     *      - Otherwise
     *          - Insert the member ticket object.
     *          - Insert a newline character.
     *          - Insert the patient's name.
     *          - Insert ", OHIP: ".
     *          - Insert the OHIP number.
     *          - Insert a newline character.
     *          - Return the ostream.
     * 
     * 3. If the patient is not being inserted into the `cout` or `clog`
     *    object, the information is presented in a comma-separated
     *    value format:
     *      - Insert the following values into the ostream in a comma-
     *        separated format. After the values are inserted, add a
     *        single "comma", and then call the write function of the
     *        member ticket object. Finally, return the ostream.
     *      - The sequence of values inserted into the ostream is as
     *        follows:
     *        ```
     *        returned value of the type() function
     *        ','
     *        name of the patient
     *        ','
     *        OHIP number
     *        ','
     *        ```
     *        and then insert the ticket.
    */
    std::ostream& Patient::write(std::ostream& ostr) const {
        return ostr;
    }

    /**
     * Extract patient information from the istream.
     * If the information is being extracted from `cin` (user input
     * over the console), the following actions are taken:
     * - Display the prompt: "Name: ".
     * - Extract the name of the patient from the istream up to 50
     *   characters or the newline character into a local Cstring of 51
     *   characters using `istream`'s `get`.
     * - Copy the extracted name into dynamically allocated memory
     *   pointed by the name member variable, ensuring the name pointer
     *   is deleted before the allocation to prevent memory leaks.
     * - Extract and ignore all characters up to and including the
     *   newline character.
     * - Display the prompt: "OHIP: ".
     * - Extract a 9-digit OHIP number from the istream. Validate it,
     *   ensuring it is between 100000000 and 999999999. Use the same
     *   error message format as the Menu item selection.
     * - Return the istream reference at the end.
     * 
     * Execution example:
     * ```
     * Name: John Doe
     * OHIP: abc
     * Bad integer value, try again: 100
     * Invalid value entered, retry [100000000 <= value <= 999999999]: 123123123
     * ```
     * 
     * If the information is not being extracted from `cin`, presuming
     * it is being read from a file, the information should be read in
     * comma-separated format as follows:
     * - Extract the name of the patient from the `istream` up to 50
     *   characters or a comma character into a local Cstring of 51
     *   characters.
     * - Copy the extracted name into dynamically allocated memory
     *   pointed by the name member variable, ensuring the name pointer
     *   is deleted before the allocation to prevent memory leaks.
     * - Extract and ignore all characters up to and including a comma
     *   character using istream's ignore.
     * - Extract an integer from the istream into the OHIP member
     *   variable.
     * - End the extraction by calling the read method of the patient's
     *   ticket.
     * - Return the istream reference at the end.
     * 
     * If, in any case, the istream fails to read the information,
     * ensure that any dynamically allocated memory held by the name
     * attribute is deleted, and the pointer is set to nullptr.
    */
    std::istream& Patient::read(std::istream& istr) {
        return istr;
    }
}
