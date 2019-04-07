#ifndef CARDOFFICE_H
#define CARDOFFICE_H
#include <uFuture.h>
#include "watCard.h"
#include "bank.h"
#include "printer.h"
#include <unordered_map>
#include <queue>
#include <uSemaphore.h>
#include "MPRNG.h"

_Task WATCardOffice {
  struct Job { // marshalled arguments and return future

    struct Args {
      enum Operation { create, transfer };
      Operation op;
      int amount;
      int id;
    };

    Args args; // call arguments (YOU DEFINE “Args”)
    WATCard::FWATCard result; // return future
    Job( Args args ) : args( args ) {}
  };
  _Task Courier {
    WATCardOffice& server;
    Bank& bank;
    void main();
  public:
    Courier(WATCardOffice& server, Bank& bank):server(server),bank(bank) {}
  }; // communicates with bank
  Printer& printer;
  void main();
  std::unordered_map<int, WATCard::FWATCard*> cards;
  std::queue<Job*> jobs;
  Courier** couriers;
  uSemaphore sem;
  Bank& bank;
  unsigned int numCouriers;
public:
  _Event Lost {}; // lost WATCard
  WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
  WATCard::FWATCard create( unsigned int sid, unsigned int amount );
  WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *
card );
  Job *requestWork();
};
#endif
