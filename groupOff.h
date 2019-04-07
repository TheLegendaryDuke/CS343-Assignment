#ifndef GROUPOFF_H
#define GROUPOFF_H
#include "printer.h"
#include "watCard.h"
_Task Groupoff {
  WATCard::FWATCard** cards;
  int counts = 0, luckies = 0;
  void main();
public:
  Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
  WATCard::FWATCard giftCard();
};
#endif
