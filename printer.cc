#include "printer.h"
#include <iostream>
using namespace std;

std::ostream& operator<<(std::ostream& out, Data &data) {
    out << (char)data.state;
    if (data.value1 != -1) out << data.value1;
    if (data.value2 != -1) out << "," << data.value2;
    return out;
}


Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
  numStudents(numStudents),
  numVendingMachines(numVendingMachines),
  numCouriers(numCouriers) {
    buffer = new Data[numStudents + numVendingMachines + numCouriers + 6];

    cout << "Parent" << '\t';
    cout << "Gropoff" << '\t';
    cout << "WATOff" << '\t';
    cout << "Names" << '\t';
    cout << "Truck" << '\t';
    cout << "Plant" << '\t';

    for (unsigned int i = 0; i < numStudents; ++i) {
        cout << "Stud" << i << '\t';
    }

    for (unsigned int i = 0; i < numVendingMachines; ++i) {
        cout << "Mach" << i << '\t';
    }

    for (unsigned int i = 0; i < numCouriers; ++i) {
        cout << "Cour" << i;

        if (i != numCouriers - 1) {
        cout << '\t';
        }
    }

    cout << endl;

    cout << "*******";
    for (unsigned int i = 1; i < numStudents + numVendingMachines + numCouriers + 6; ++i) {
        cout << "\t*******";
    }
    cout << endl;
}

Printer::~Printer() {
    flush();
    delete[] buffer;
    std::cout << "***********************" << std::endl;
}

void Printer::flush() {
    unsigned int last_index = numStudents + numVendingMachines + numCouriers + 6-1;
    for (unsigned int i = 0; i < numStudents + numVendingMachines + numCouriers + 6; i++) {
        if (buffer[numStudents + numVendingMachines + numCouriers + 6 - i - 1].exist) {
            last_index = numStudents + numVendingMachines + numCouriers + 6 - i - 1;
            break;
        }
    }
    for (unsigned int i = 0; i <= last_index; i++) {
        if (i != 0) std::cout << '\t';
        if (buffer[i].exist) {
            std::cout << buffer[i];
            buffer[i].exist = false;
        }
    }
    std::cout << std::endl;
}

void Printer::check_flush(unsigned int i) {
    if (buffer[i].exist) flush();
}

unsigned int Printer::getBufferIndex( Kind kind) {
  if (kind != Student && kind != Vending && kind != Courier) {
    return (int) kind;
  }
  return 0;
}

unsigned int Printer::getBufferIndex( Kind kind, unsigned int lid ) {
  if (kind != Student && kind != Vending && kind != Courier) {
    return (int) kind;
  }

  switch (kind) {
    case Student:
      return 6 + lid;
    case Vending:
      return 6 + numStudents + lid;
    case Courier:
      return 6 + numStudents + numVendingMachines + lid;
  }
}

void Printer::print( Kind kind, char state ) {
    unsigned int id = getBufferIndex(kind);
    check_flush(id);
    buffer[id].kind = kind;
    buffer[id].state = state;
    buffer[id].exist = true;
}

void Printer::print( Kind kind, char state, int value1 ) {
    unsigned int id = getBufferIndex(kind);
    check_flush(id);
    buffer[id].kind = kind;
    buffer[id].state = state;
    buffer[id].exist = true;
    buffer[id].value1 = value1;
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
    unsigned int id = getBufferIndex(kind);
    check_flush(id);
    buffer[id].kind = kind;
    buffer[id].state = state;
    buffer[id].exist = true;
    buffer[id].value1 = value1;
    buffer[id].value2  = value2;
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
    unsigned int id = getBufferIndex(kind, lid);
    check_flush(id);
    buffer[id].kind = kind;
    buffer[id].state = state;
    buffer[id].exist = true;
    buffer[id].lid = lid;
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
    unsigned int id = getBufferIndex(kind, lid);
    check_flush(id);
    buffer[id].kind = kind;
    buffer[id].state = state;
    buffer[id].exist = true;
    buffer[id].value1 = value1;
    buffer[id].lid = lid;
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
    unsigned int id = getBufferIndex(kind, lid);
    check_flush(id);
    buffer[id].kind = kind;
    buffer[id].state = state;
    buffer[id].exist = true;
    buffer[id].value1 = value1;
    buffer[id].value2  = value2;
    buffer[id].lid = lid;
}