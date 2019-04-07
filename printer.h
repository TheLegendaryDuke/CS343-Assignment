#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <string>
class State;
class Data;


_Monitor Printer {
    unsigned int numOfVoters;
    void flush();
    void check_flush(unsigned int i);
    Data * buffer;
public:
    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
};

class Data {
    Printer::Kind kind;
    char state;
    int value1;
    int value2;
    unsigned int lid;
    bool exist = false;
  public:
    Data( Printer::Kind kind, char state, int value1 = -1, int value2 = -1);
    Data( Printer::Kind kind, unsigned int lid, char state, int value1 = -1, int value2 = -1 );
};

#endif