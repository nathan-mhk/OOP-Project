#!/bin/bash

if [[ $# == 0 ]];
then
    main=main.cpp
else
    main="ms5$1_test.cpp"
fi

g++ -Wall -std=c++11 Menu.cpp IOAble.cpp Ticket.cpp Time.cpp Patient.cpp TestPatient.cpp TriagePatient.cpp PreTriage.cpp Utils.cpp $main

exit 0
