#include "cardOffice.h"

using namespace std;

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ):printer(prt),bank(bank),numCouriers(numCouriers) {
  couriers = new Courier*[numCouriers];
  for(int i = 0; i < numCouriers; i++) {
    couriers[i] = new Courier();
  }
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
  cards[sid] = new WATCard::FWATCard();
  Job* job = new Job({create,amount,sid});
  job->result = *cards[sid];
  jobs.push(job);
  sem.V();
  return *cards[sid];
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount) {
  Job* job= new Job({transfer, amount, sid});
  job->result = *cards[sid];
  jobs.push(job);
  sem.V();
  return *cards[sid];
}

Job* WATCardOffice::requestWork() {
  sem.P();
  return jobs.pop();
}

void WATCardOffice::main() {
  
}



void WATCardOffice::Courier::main() {
  while(true) {
    Job& job = *requestWork();
    switch(job.args.op) {
      case create:
        bank.withdraw(job.args.id, job.args.amount);
        WATCard* card = new WATCard();
        card->deposit(job.args.amount);
        if(mprng(6) % 6 == 0) job.result.exception(WATCardOffice::Lost{}); 
        else job.result.delivery(card);
        break;
      case transfer:
        bank.withdraw(job.args.id, job.args.amount);
        if(mprng(6) % 6 == 0) job.result.exception(WATCardOffice::Lost{});
        else job.result()->deposit(job.args.amount);
        break;
    }
}
