#include "bottlingplant.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

extern MPRNG mprng;

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
  unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
  unsigned int timeBetweenShipments ) :
  printer(prt),
  nameServer(nameServer),
  numVendingMachines(numVendingMachines),
  maxShippedPerFlavour(maxShippedPerFlavour),
  maxStockPerFlavour(maxStockPerFlavour),
  timeBetweenShipments(timeBetweenShipments),
  closed(false) {}

BottlingPlant::~BottlingPlant() {
  if (truck != nullptr) {
    delete truck;
  }
}

void BottlingPlant::getShipment( unsigned int cargo[] ) {
  if (closed) {
    uRendezvousAcceptor();
    _Throw Shutdown();
  }

  for (unsigned int f = 0; f < 4; ++f) {
    cargo[f] = stock[f];
  }

  printer.print(Printer::BottlingPlant, 'P');
}

void BottlingPlant::main() {
  printer.print(Printer::BottlingPlant, 'S');
  truck = new Truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);

  for (;;) {
    _Accept(~BottlingPlant) {
      closed = true;
      try {
        _Accept(getShipment);
      } catch (uMutexFailure::RendezvousFailure) {}
      break;
    } _Else {
      yield(timeBetweenShipments);

      unsigned int count = 0;
      for (unsigned int f = 0; f < 4; ++f) {
        stock[f] = mprng(maxStockPerFlavour);
        count += stock[f];
      }
      printer.print(Printer::BottlingPlant, 'G', count);

      _Accept(getShipment);
    }
  }

  printer.print(Printer::BottlingPlant, 'F');
}
