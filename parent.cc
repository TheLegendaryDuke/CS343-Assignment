#include "parent.h"

using namespace std;

Parent::Parent(Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay):printer(prt),bank(bank),numStudents(numStudents),parentalDelay(parentalDelay) {}

void Parent::main() {
  while(true) {
    _Accpet(~Parent) {
      break;
    } _Else {
      int amount = mprng(1,3);
      int student = mprng(0,numStudents-1);
      yield(parentalDelay);
      bank.deposit(student, amount);
    }
  }
}
