/***********************************************************************
// OOP244 Project 
//
// File  Utils.h
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
/**
 * Name: Nathan Kong
 * Email: nkong@myseneca.ca
 * ID: 150950236
 * Date: 2024-03-18
 * 
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#ifndef SENECA_UTILS_H_
#define SENECA_UTILS_H_
#include <iostream>
namespace seneca {
   class Utils {
      /// <summary>
      /// Start point for the simulated time
      /// Set to 8 AM
      /// </summary>
      unsigned int m_testMins = 480;
      /// <summary>
      /// index for the time addition intervals ({ 3,5,9,20,30 });
      /// </summary>
      unsigned int m_testIndex = 0 ;
   public:
      /// <summary>
      /// Set the debug global variable to true and sets the m_testMins attribute to 
      ///  hour x 60 + min. This value will be the intial starting time for debugging
      ///  and testing. 
      /// </summary>
      /// <param name="hour">hours</param>
      /// <param name="min">minutes</param>
      void setDebugTime(int hour, int min);
      /// <summary>
      /// If not in debugging mode, returns the current minute value of the system hour
      ///  and minute. If debugging is active it will first return the value of m_testMins 
      ///  then adds the following values in these intervals (3,5,9,20,30) to simulate passage
      ///  of time. 
      /// </summary>
      /// <returns>the current time in minutes</returns>
      int getTime(); // returns the time of day in minutes

      /// @brief Clear the istream buffer
      /// @param istr - the istream buffer to be cleared. Default `cin`
      /// @param delim - the delimiter of the buffer to be cleared up to. Default `\\n`.
      void clearIstrBuffer(std::istream& istr = std::cin, const char delim = '\n');

      /// @brief Get an integer [min, max] from user through `cin`
      /// @param value - the integer value to be stored in
      /// @param min - the min. acceptable value, inclusive
      /// @param max - the max. acceptable value, inclusive
      /// @return the reference variable of `value`
      int& getInt(int& value, const int& min, const int& max);
   };

   /// <summary>
   /// making seneca::debug variable global to all the files
   /// which include "Utils.h"
   /// </summary>
   extern bool debug; 
   /// <summary>
   /// making seneca::U "Utils" object global to all the files which include "Utils.h"
   /// </summary>
   extern Utils U;    

}
#endif // !SENECA_UTILS_H_

