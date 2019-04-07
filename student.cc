#include "student.h"

using namespace std;

MPRNG mprng;

Student::Student(Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff, unsigned int id, unsigned int maxPurchases):nameServer(nameServer),cardOffice(cardOffice),groupoff(groupoff),id(id),maxPurchases(maxPurchases),printer(prt) {}

void Student::main() {
  int numToBuy = mprng(1,maxPurchases);
  int flavour = mprng(3);
  WATCard::FWATCard watCard = cardOffice.create(id,5);
  WATCard::FWATCard giftcard = groupoff.giftCard();
  VendingMachine* vm = nameServer.getMachine(id);
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
      if(usingGiftcard) giftcard.reset();
    }catch (VendingMachine::Funds) {
      watCard = cardOffice.transfer(id, sodaCost+5, card);
      i--;
    }catch (VendingMachine::Stock) {
      vm = nameServer.getMachine(id);
      i--;
    }catch (VendingMachine::Free) {
      yield(4);
      i--;
    }
  }
}
