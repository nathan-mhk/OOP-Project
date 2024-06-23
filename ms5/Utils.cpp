/***********************************************************************
// OOP244 Project
//
// File  Utils.cpp
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "Utils.h"
#include "Time.h"
using namespace std;
namespace seneca {
   // start provided code
   bool debug = false;
   Utils U;
   int Utils::getTime() {
      int mins = -1;
      if (debug) {
         int duration[]{ 3,5,9,20,30 };
         mins = (m_testMins %= 1440);
         m_testMins += duration[m_testIndex++ % 5];
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         mins = lt.tm_hour * 60 + lt.tm_min;
      }
      return mins;
   }
   void Utils::setDebugTime(int hour, int min) {
      seneca::debug = true;
      m_testMins = hour * 60 + min;
   }

   int Utils::strcmp(const char* s1, const char* s2)const {
      int i;
      for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++);
      return s1[i] - s2[i];
   }
   // end provided code

   void Utils::clearIstrBuffer(std::istream& istr, const char delim) {
      istr.ignore(numeric_limits<streamsize>::max(), delim);
   }

   int& Utils::getInt(int& value, const int& min, const int& max) {
      while (true) {
         cin >> value;

         if (cin.fail()) {
               cout << "Bad integer value, try again: ";

               cin.clear();
               clearIstrBuffer();
               continue;
         }

         if (cin.peek() != '\n') {
               cout << "Only enter an integer, try again: ";

               clearIstrBuffer();
               continue;
         }

         if (value < min || value > max) {
               cout << "Invalid value enterd, retry[" << min << " <= value <= "<< max << "]: ";
               
               clearIstrBuffer();
               continue;
         }
         clearIstrBuffer();
         return value;
      }
   }
}