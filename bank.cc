#include "bank.h"

using namespace std;

Bank::Bank(unsigned int numStudents):numStudents(numStudents) {
  accounts = new int[numStudents];
  for(int i = 0; i < numStudents; i++) {
    accounts[i] = 0;
  }
}

void Bank::deposit(unsigned int id, unsigned int amount) {
  accounts[id] += amount;
}

void Bank::withdraw(unsigned int id, unsigned int amount) {
  while(accounts[id] < amount) _Accept(deposit);
  accounts[id] -= amount;
}
