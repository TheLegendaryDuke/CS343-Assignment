#ifndef GROUPOFF_H
#define GROUPOFF_H
#include "printer.h"
#include "watCard.h"
#include "MPRNG.h"
_Task Groupoff {
  WATCard::FWATCard** cards;
  int count = 0, luckies = 0;
  void main();
  Printer& printer;
  unsigned int sodaCost,groupoffDelay,numStudents;
public:
  Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
  WATCard::FWATCard giftCard();
};
#endif
