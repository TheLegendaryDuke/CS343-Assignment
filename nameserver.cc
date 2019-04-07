#include "vendingmachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) :
  prt(prt), numStudents(numStudents), numMachines(numVendingMachines), numRegisteredMachines(0) {
  assignments = new int[numStudents];
  machines = new VendingMachine*[numMachines];

  for (unsigned int i = 0; i < numStudents; i++) {
    assignments[i] = i%numMachines;
  }
}

NameServer::~NameServer() {
  delete [] assignments;
  delete [] machines;
}

void NameServer::main() {
  prt.print(Printer::NameServer, "S");

  while (true) {
    _Accept(~NameServer) break;
    or _When(numRegisteredMachines == numMachines) _Accept(getMachine, getMachineList);
    or _When(numRegisteredMachines < numMachines) _Accept(VMregister);
  }

  prt.print(Printer::NameServer, "F");
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
  int id = vendingmachine->getId();
  prt.print(Printer::NameServer, "R", id);
  machines[numRegisteredMachines++] = vendingmachine;
}

VendingMachine *NameServer::getMachine( unsigned int id ) {
  VendingMachine *ret = machines[assignments[id]];
  prt.print(Printer::NameServer, "N", id, ret->getId());
  assignments[id] = (assignments[id] + 1) % numMachines;

  return ret;
}

VendingMachine **NameServer::getMachineList() {
  return machines;
}