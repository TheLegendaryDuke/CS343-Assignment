#include "student.h"
#include <iostream>

using namespace std;

extern MPRNG mprng;

Student::Student(Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff, unsigned int id, unsigned int maxPurchases):nameServer(nameServer),cardOffice(cardOffice),groupoff(groupoff),id(id),maxPurchases(maxPurchases),printer(prt) {}

void Student::main() {
  int numToBuy = mprng(1,maxPurchases);
  VendingMachine::Flavours flavour = static_cast<VendingMachine::Flavours>(mprng(3));
  printer.print(Printer::Kind::Student, id, 'S', flavour, numToBuy);
  bool cardLost = true;
  WATCard::FWATCard watcard = cardOffice.create(id,5);
  WATCard::FWATCard giftcard = groupoff.giftCard();
  VendingMachine* vm = nameServer.getMachine(id);
  printer.print(Printer::Kind::Student, id, 'V' , vm->getId());
  for(int i = 0; i < numToBuy; i++) {
    yield(mprng(1,10));
      bool bought = false;
      while (!bought) {
          _Select(giftcard) {
              try {
                  vm->buy(flavour, *giftcard());
                  printer.print(Printer::Student, id, 'G', flavour, giftcard()->getBalance());
                  giftcard.reset();
                  bought = true;
              } catch (VendingMachine::Stock) {
                  vm = nameServer.getMachine(id);
                  printer.print(Printer::Student, id, 'V', vm->getId());
              } catch (VendingMachine::Free) {
                  yield(4);
                  printer.print(Printer::Student, id, 'a', flavour, giftcard()->getBalance());
                  bought = true;
              }
          }
          or _Select(watcard) {
              try {
                  vm->buy(flavour, *watcard());
                  printer.print(Printer::Student, id, 'G', flavour, watcard()->getBalance());
                  bought = true;
              } catch (VendingMachine::Stock) {
                  vm = nameServer.getMachine(id);
                  printer.print(Printer::Student, id, 'V', vm->getId());
              } catch (VendingMachine::Free) {
                  yield(4);
                  printer.print(Printer::Student, id, 'a', flavour, watcard()->getBalance());
                  bought = true;
              } catch (WATCardOffice::Lost) {
                  printer.print(Printer::Kind::Student, id, 'L');
                  watcard = cardOffice.create(id,5);
              }
          }
          
      }

  }
  printer.print(Printer::Kind::Student, id, 'F');
}
