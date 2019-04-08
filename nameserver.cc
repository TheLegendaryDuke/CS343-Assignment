#include "vendingmachine.h"
#include <iostream>

NameServer::NameServer( Printer &printer, unsigned int numVendingMachines, unsigned int numStudents ) :
  printer(printer), numStudents(numStudents), numVendingMachines(numVendingMachines) {
  MachineMap = new unsigned int[numStudents];
  Machines = new VendingMachine*[numVendingMachines];

  for (unsigned int i = 0; i < numStudents; i++) {
    MachineMap[i] = i%numVendingMachines;
  }
}

NameServer::~NameServer() {
  delete [] MachineMap;
  delete [] Machines;
}

void NameServer::main() {
  printer.print(Printer::NameServer, 'S');

  while (true) {
    _Accept(~NameServer) break;
    or _When(registed == numVendingMachines) _Accept(getMachine, getMachineList);
    or _When(registed < numVendingMachines) _Accept(VMregister);
  }

  printer.print(Printer::NameServer, 'F');
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
  int id = vendingmachine->getId();
  printer.print(Printer::NameServer, 'R', id);
  Machines[registed++] = vendingmachine;
}

VendingMachine *NameServer::getMachine( unsigned int id ) {
    std::cout << "get machine" << std::endl;
  VendingMachine *ret = Machines[MachineMap[id]];
  printer.print(Printer::NameServer, 'N', id, ret->getId());
  MachineMap[id] = (MachineMap[id] + 1) % numVendingMachines;

  return ret;
}

VendingMachine **NameServer::getMachineList() {
  return Machines;
}
