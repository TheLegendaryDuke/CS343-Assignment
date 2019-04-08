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
      _Select(giftcard) {
          try {
              std::cout << 1 << endl;
              vm->buy(flavour, *giftcard());
              printer.print(Printer::Student, id, 'G', flavour, giftcard()->getBalance());
              giftcard.reset();
              break;
          } catch (VendingMachine::Stock) {
              std::cout << 2 << endl;
              vm = nameServer.getMachine(id);
              printer.print(Printer::Student, id, 'V', vm->getId());
          } catch (VendingMachine::Free) {
              std::cout << 3 << endl;
              yield(4);
              printer.print(Printer::Student, id, 'a', flavour, giftcard()->getBalance());
              break;
          }
      }
      or _Select(watcard) {
          try {
              vm->buy(flavour, *watcard());
              printer.print(Printer::Student, id, 'G', flavour, watcard()->getBalance());
              break;
          } catch (VendingMachine::Stock) {
              vm = nameServer.getMachine(id);
              printer.print(Printer::Student, id, 'V', vm->getId());
          } catch (VendingMachine::Free) {
              yield(4);
              printer.print(Printer::Student, id, 'a', flavour, watcard()->getBalance());
              break;
          } catch (WATCardOffice::Lost) {
              printer.print(Printer::Kind::Student, id, 'L');
              break;
          }
      }
  }
  printer.print(Printer::Kind::Student, id, 'F');
}
