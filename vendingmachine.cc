#include "vendingmachine.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

extern MPRNG mprng;

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) :
  printer(prt),
  nameServer(nameServer),
  id(id),
  sodaCost(sodaCost),
  maxStockPerFlavour(maxStockPerFlavour),
  restocking(false) {
    for (unsigned int i = 0; i < 4; ++i) {
      stocks[i] = 0;
    }
  }

void VendingMachine::buy( Flavours flavour, WATCard & card ) {
  if (stocks[(unsigned int)flavour] == 0) {
    _Throw Stock();
  } else if (mprng(4) == 0) {
    stocks[(unsigned int)flavour]--;
    _Throw Free();
  } else if (card.getBalance() < sodaCost) {
    _Throw Funds();
  } else {
    card.withdraw(sodaCost);
    stocks[(unsigned int)flavour]--;
    printer.print(Printer::Vending, id, 'B', (unsigned int)flavour, stocks[(unsigned int)flavour]);
  }
}

unsigned int * VendingMachine::inventory() {
    restocking = true;
  printer.print(Printer::Vending, id, 'r');
  return stocks;
}

void VendingMachine::restocked() {
    restocking = false;
  printer.print(Printer::Vending, id, 'R');
}

_Nomutex unsigned int VendingMachine::cost() {
  return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
  return id;
}

void VendingMachine::main() {
  nameServer.VMregister(this);

  printer.print(Printer::Vending, id, 'S', sodaCost);

  for (;;) {
    try {
      _Accept(~VendingMachine) {
        break;
      } or _Accept(restocked) {
      } or _When (!restocking) _Accept(buy, inventory); 
    } catch (uMutexFailure::RendezvousFailure) {}
  }
  printer.print(Printer::Vending, id, 'F');
}