#include "cardOffice.h"
#include <assert.h>

using namespace std;

extern MPRNG mprng;

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ):printer(prt),bank(bank),numCouriers(numCouriers) {
  sem.P();
  couriers = new Courier*[numCouriers];
  for(int i = 0; i < numCouriers; i++) {
    couriers[i] = new Courier(*this, bank);
  }
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
  cards[sid] = new WATCard::FWATCard();
  Job::Args args;
  args.op = Job::Args::Operation::create;
  args.amount = amount;
  args.id = sid;
  Job* job = new Job(args);
  job->result = *cards[sid];
  jobs.push(job);
  sem.V();
  return *cards[sid];
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
  assert(card==(*cards[sid])());
  Job::Args args;
  args.op = Job::Args::Operation::transfer;
  args.amount = amount;
  args.id = sid;
  Job* job= new Job(args);
  job->result = *cards[sid];
  jobs.push(job);
  sem.V();
  return *cards[sid];
}

WATCardOffice::Job* WATCardOffice::requestWork() {
  sem.P();
  Job* result = jobs.front();
  jobs.pop();
  return result;
}

void WATCardOffice::main() {
  
}



void WATCardOffice::Courier::main() {
  while(true) {
    Job& job = *(server.requestWork());
    switch(job.args.op) {
      case Job::Args::Operation::create:
      {
        bank.withdraw(job.args.id, job.args.amount);
        WATCard* card = new WATCard();
        card->deposit(job.args.amount);
        if(mprng(6) % 6 == 0) job.result.exception(new WATCardOffice::Lost()); 
        else job.result.delivery(card);
        break;
      }
      case Job::Args::Operation::transfer:
        bank.withdraw(job.args.id, job.args.amount);
        if(mprng(6) % 6 == 0) job.result.exception(new WATCardOffice::Lost());
        else job.result()->deposit(job.args.amount);
        break;
    }
  }
}
