#ifndef GROUPOFF_H
#define GROUPOFF_H
#include "printer.h"
#include "watCard.h"
_Task Groupoff {
  void main();
public:
  Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
  WATCard::FWATCard giftCard();
};
#endif