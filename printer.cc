#include "printer.h"
using namespace std;

std::ostream& operator<<(std::ostream& out, Data &data) {
    out << (char)data.state;
    if (value1 != -1) out << value1;
    if (value2 != -1) out << "," << value2;
    return out;
}


Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) {
    numOfVoters = voters;
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
    unsigned int last_index = numOfVoters-1;
    for (unsigned int i = 0; i < numOfVoters; i++) {
        if (buffer[numOfVoters - i - 1].exist) {
            last_index = numOfVoters - i - 1;
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
    unsigned int idx = getBufferIndex(kind);
    check_flush();
    buffer[id].kind = kind;
    buffer[id].state = state;
    buffer[id].exist = true;
}

void Printer::print( Kind kind, char state, int value1 ) {
    unsigned int idx = getBufferIndex(kind);
    check_flush();
    buffer[id].kind = kind;
    buffer[id].state = state;
    buffer[id].exist = true;
    buffer[id].value1 = value1;
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
    unsigned int idx = getBufferIndex(kind);
    check_flush();
    buffer[id].kind = kind;
    buffer[id].state = state;
    buffer[id].exist = true;
    buffer[id].value1 = value1;
    buffer[id].value2  = value2;
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
    unsigned int idx = getBufferIndex(kind);
    check_flush();
    buffer[id].kind = kind;
    buffer[id].state = state;
    buffer[id].exist = true;
    buffer[id].lib = lib;
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
    unsigned int idx = getBufferIndex(kind);
    check_flush();
    buffer[id].kind = kind;
    buffer[id].state = state;
    buffer[id].exist = true;
    buffer[id].value1 = value1;
    buffer[id].lib = lib;
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
    unsigned int idx = getBufferIndex(kind);
    check_flush();
    buffer[id].kind = kind;
    buffer[id].state = state;
    buffer[id].exist = true;
    buffer[id].value1 = value1;
    buffer[id].value2  = value2;
    buffer[id].lib = lib;
}