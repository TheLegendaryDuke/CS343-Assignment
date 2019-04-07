#include <algorithm>
#include "truck.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

extern MPRNG mprng;

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) :
  printer(prt),
  nameServer(nameServer),
  plant(plant),
  numVendingMachines(numVendingMachines),
  maxStockPerFlavour(maxStockPerFlavour) {}

void Truck::main() {
  printer.print(Printer::Truck, 'S');

  VendingMachine **machines = nameServer.getMachineList();
  unsigned int lastMachineIndex = -1; // last machine the truck restocked
  unsigned int cargo[4]; // cargo for shipment

  for (;;) {
    yield(mprng(1, 10)); // coffee
    try {
      plant.getShipment(cargo);
    } catch (BottlingPlant::Shutdown) {
      break;
    }

    unsigned int total = 0;
    for (unsigned int i = 0; i < 4; ++i) {
      total += cargo[i];
    }

    printer.print(Printer::Truck, 'P', total);

    for (unsigned int i = 0; i < numVendingMachines; ++i) {
      if (total == 0) break;

      lastMachineIndex = (lastMachineIndex + 1) % numVendingMachines; // next machine

      unsigned int *inventory = machines[lastMachineIndex]->inventory(); // restock start
      printer.print(Printer::Truck, 'd', lastMachineIndex, total);

      unsigned int missing = 0; // keep track of unreplenished bottles
      for (unsigned int f = 0; f <4; ++f) {
        unsigned int numRestocked = min(maxStockPerFlavour - inventory[f], cargo[f]);
        inventory[f] += numRestocked;
        cargo[f] -= numRestocked;
        total -= numRestocked;
        missing += ( maxStockPerFlavour - inventory[f] );
      }

      machines[lastMachineIndex]->restocked(); // restock end

      if (missing > 0) { // print machines that are not fully stocked
        printer.print(Printer::Truck, 'U', lastMachineIndex, missing);
      }

      printer.print(Printer::Truck, 'D', lastMachineIndex, total);
    }
  }

  printer.print(Printer::Truck, 'F');
}