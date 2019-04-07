#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <string>
class State;
class Data;


_Monitor Printer {
    unsigned int numStudents;
    unsigned int numVendingMachines;
    unsigned int numCouriers;
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
    ~Printer();
private:
    unsigned int getBufferIndex( Kind kind, unsigned int lid );
    unsigned int getBufferIndex( Kind kind );
};

class Data {
public:
    Printer::Kind kind;
    char state;
    int value1;
    int value2;
    unsigned int lid;
    bool exist = false;
};

#endif