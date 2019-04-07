#include "student.h"

using namespace std;

extern MPRNG mprng;

Student::Student(Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff, unsigned int id, unsigned int maxPurchases):nameServer(nameServer),cardOffice(cardOffice),groupoff(groupoff),id(id),maxPurchases(maxPurchases),printer(prt) {}

void Student::main() {
  int numToBuy = mprng(1,maxPurchases);
  VendingMachine::Flavours flavour = static_cast<VendingMachine::Flavours>(mprng(3));
  printer.print(Printer::Kind::Student, 'S', flavour, numToBuy);
  bool cardLost = true;
  while(cardLost) {
    try {
      WATCard::FWATCard watCard = cardOffice.create(id,5);
      cardLost = false;
    }catch (WATCardOffice::Lost) {
      printer.print(Printer::Kind::Student, 'L');
      cardLost = true;
    }
  }
  WATCard::FWATCard giftcard = groupoff.giftCard();
  VendingMachine* vm = nameServer.getMachine(id);
  printer.print(Printer::Kind::Student, 'V', vm->getId());
  for(int i = 0; i < numToBuy; i++) {
    yield(mprng(1,10));
    _Select(giftcard || watCard);
    WATCard* card;
    bool usingGiftcard = false;
    if(giftcard.available()) {
    	card = giftcard();
    	usingGiftcard = true;
    } else card = watCard();
    
    int oldBalance = card->getBalance();
    
    try{
      vm->buy(flavour, *card);
      if(usingGiftcard) {
        printer.print(Printer::Kind::Student, 'G', flavour, 0);
        giftcard.reset();
      }else printer.print(Printer::Kind::Student, 'B', flavour, card->getBalance());
    }catch (VendingMachine::Funds) {
      cardLost = true;
      while(cardLost) {
        try {
          watCard = cardOffice.transfer(id, vm->cost()+5, card);
          cardLost = false;
          i--;
        }catch (WATCardOffice::Lost) {
          printer.print(Printer::Kind::Student, 'L');
          cardLost = true;
        }
      }
    }catch (VendingMachine::Stock) {
      vm = nameServer.getMachine(id);
      i--;
    }catch (VendingMachine::Free) {
      yield(4);
      if(usingGiftcard) printer.print(Printer::Kind::Student, 'a', flavour, card->getBalance());
      else printer.print(Printer::Kind::Student, 'A', flavour, card->getBalance());
      i--;
    }
  }
  printer.print(Printer::Kind::Student, 'F');
}
