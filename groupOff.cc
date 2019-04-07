#include "groupOff.h"

using namespace std;

extern MPRNG mprng;

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ):printer(prt),numStudents(numStudents),sodaCost(sodaCost),groupoffDelay(groupoffDelay){
  cards = new WATCard::FWATCard*[numStudents];
  for(int i = 0; i < numStudents; i++) {
    cards[i] = new WATCard::FWATCard();
  }
}

void Groupoff::main() {
  while(true) {
    _Accept(~Groupoff) {
      break;
    }_Else {
      if(luckies == count) _Accept(giftcard);
      yield(groupoffDelay);
      int luckyOne = mprng(luckies, count-1);
      WATCard::FWATCard* temp = cards[luckyOne];
      cards[luckyOne] = cards[luckies];
      cards[luckies] = temp;
      luckies++;
      if(luckies == numStudents) break;
    }
  }
}

WATCard::FWATCard Groupoff::giftCard() {
  int temp = count;
  count++;
  return *cards[temp];
}
