#include <iostream>
#include "config.h"
#include "MPRNG.h"
#include "printer.h"
#include "parent.h"
#include "bank.h"
#include "cardOffice.h"
#include "nameserver.h"
#include "vendingmachine.h"
#include "groupOff.h"
#include "student.h"
#include "bottlingplant.h"

using namespace std;

MPRNG mprng;

void usage(char *arg) {
  cerr << "Usage: " << arg
    << " [ config-file [ random-seed (> 0) ] ]" << endl;
  exit(EXIT_FAILURE);
}

int tryParseStringToNumber(char* arg) {
  char* endptr;

  long val = strtol(arg, &endptr, 10);

  if (*endptr == 0) {
    return int(val);
  } else {
    return -1;
  }
}

int main( int argc, char *argv[] ) {
  string configFile = "soda.config";
  int seed = getpid();

  switch (argc) {
    case 3:
      seed = tryParseStringToNumber(argv[2]);
      if (seed < 0) {
        usage(argv[0]);
      }
    case 2:
      configFile = argv[1];
    case 1:
      break;
    default:
      usage(argv[0]);
  }

  mprng.set_seed(seed);

  ConfigParms config;
  processConfigFile(configFile.c_str(), config);

  Printer printer(config.numStudents, config.numVendingMachines, config.numCouriers);
      Bank * bank_pt = new Bank(config.numStudents);
    {


  Parent* parent_pt = new Parent(printer, *bank_pt, config.numStudents, config.parentalDelay);

  WATCardOffice* office_pt = new WATCardOffice(printer, *bank_pt, config.numCouriers);

  NameServer nameServer(printer, config.numVendingMachines, config.numStudents);

  Groupoff groupoff(printer, config.numStudents, config.sodaCost, config.groupoffDelay);

  BottlingPlant *plant = new BottlingPlant(printer, nameServer, config.numVendingMachines,
    config.maxShippedPerFlavour, config.maxStockPerFlavour, config.timeBetweenShipments);

  VendingMachine *vendingMachines[config.numVendingMachines];
  for (unsigned int i = 0; i < config.numVendingMachines; ++i) {
    vendingMachines[i] = new VendingMachine(printer, nameServer, i, config.sodaCost, config.maxStockPerFlavour);
  }

  Student* students[config.numStudents];
  for (unsigned int i = 0; i < config.numStudents; ++i) {
    students[i] = new Student(printer, nameServer, *office_pt, groupoff, i, config.maxPurchases);
  }

  for (unsigned int i = 0; i < config.numStudents; ++i) {
    delete students[i];
  }

  delete plant;

  for (unsigned int i = 0; i < config.numVendingMachines; ++i) {
    delete vendingMachines[i];
  }
        delete office_pt;
        delete parent_pt;
        
 }
    delete bank_pt;
  std::cout << "finish" << std::endl;
}
