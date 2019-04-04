#ifndef STUDENT_H
#define STUDENT_H
#include "nameServer.h"
#include "cardOffice.h"
#include "groupOff.h"
#include "printer.h"
#include "MPRNG.h"

_Task Student {
  void main();
  NameServer &nameServer;
  WATCardOffice &cardOffice;
  Groupoff &groupoff;
  Printer &printer;
  unsigned int id, maxPurchases;
public:
  Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff, unsigned int id, unsigned int maxPurchases );
};
#endif
