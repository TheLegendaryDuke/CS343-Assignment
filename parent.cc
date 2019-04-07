#include "parent.h"

using namespace std;

extern MPRNG mprng;

Parent::Parent(Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay):printer(prt),bank(bank),numStudents(numStudents),parentalDelay(parentalDelay) {}

void Parent::main() {
  printer.print(Printer::Kind::Parent, 'S');
  while(true) {
    _Accept(~Parent) {
      printer.print(Printer::Kind::Parent, 'F');
      break;
    } _Else {
      int amount = mprng(1,3);
      int student = mprng(0,numStudents-1);
      yield(parentalDelay);
      printer.print(Printer::Kind::Parent, 'D', student, amount);
      bank.deposit(student, amount);
    }
  }
}
