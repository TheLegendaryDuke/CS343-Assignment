    
#ifndef NAMESERVER_H
#define NAMESERVER_H

#include "printer.h"
#include "vendingmachine.h"

_Task VendingMachine;

_Task NameServer {
    Printer &printer;
    unsigned int numVendingMachines;
    unsigned int numStudents;
    VendingMachine ** Machines;
    unsigned int * MachineMap;
    unsigned int registed = 0;
    void main();
  public:
    NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine * vendingmachine );
    VendingMachine * getMachine( unsigned int id );
    VendingMachine ** getMachineList();
};

#endif