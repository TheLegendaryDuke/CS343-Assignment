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
  printer.print(Printer::Kind::Groupoff, 'S');
  while(true) {
    _Accept(~Groupoff) {
      printer.print(Printer::Kind::Groupoff, 'F');
      break;
    }_Else {
      if(luckies == count) _Accept(giftCard);
      yield(groupoffDelay);
      int luckyOne = mprng(luckies, count-1);
      WATCard* card = new WATCard();
      card->deposit(sodaCost);
      WATCard::FWATCard* temp = cards[luckyOne];
      printer.print(Printer::Kind::Groupoff, 'D', sodaCost);
      temp->delivery(card);
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
