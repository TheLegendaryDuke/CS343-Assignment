#include "cardOffice.h"
#include <assert.h>
#include <iostream>
using namespace std;

extern MPRNG mprng;

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ):printer(prt),bank(bank),numCouriers(numCouriers) {
    printer.print(Printer::Kind::WATCardOffice, 'S');
    couriers = new Courier*[numCouriers];
    for(int i = 0; i < numCouriers; i++) {
        couriers[i] = new Courier(*this, bank, printer);
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
    printer.print(Printer::Kind::WATCardOffice, 'C', sid, amount);
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
    printer.print(Printer::Kind::WATCardOffice, 'T', sid, amount);
    return *cards[sid];
}

WATCardOffice::Job* WATCardOffice::requestWork() {
    if (finished) return nullptr;
    Job* result = jobs.front();
    jobs.pop();
    printer.print(Printer::Kind::WATCardOffice, 'W');
    return result;
}

void WATCardOffice::main() {
    printer.print(Printer::WATCardOffice, 'S');
    
    for (;;) {
        _Accept(~WATCardOffice) {
            finished = true;
            for (;;) {
                if (jobs.empty()) break;
                delete jobs.front();
                jobs.pop();
            }
            
            for (unsigned int i = 0; i < numCouriers; ++i) {
                _Accept(requestWork);
            }
            for (unsigned int i = 0; i < numCouriers; ++i) {
                delete couriers[i];
            }
            delete[] couriers;
            break;
        } or _Accept(create, transfer) {
        } or _When(!jobs.empty()) _Accept(requestWork) {}
    }
    
    printer.print(Printer::WATCardOffice, 'F');
}


WATCardOffice::~WATCardOffice() {
    printer.print(Printer::Kind::WATCardOffice, 'F');
}

void WATCardOffice::Courier::main() {
    printer.print(Printer::Kind::Courier, 'S');
    while(true) {
        
        Job* job_pt = (server.requestWork());
        if (job_pt == nullptr) break;
        Job & job = *job_pt;
        
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
                printer.print(Printer::Kind::Courier, 't', job.args.id, job.args.amount);
                bank.withdraw(job.args.id, job.args.amount);
                if(mprng(6) % 6 == 0) {
                    printer.print(Printer::Kind::Courier, 'O', job.args.id);
                    job.result.exception(new WATCardOffice::Lost());
                } else job.result()->deposit(job.args.amount);
                printer.print(Printer::Kind::Courier, 'T', job.args.id, job.args.amount);
                break;
        }
        delete job_pt;
    }
}
WATCardOffice::Courier::~Courier() {
    
    printer.print(Printer::Kind::Courier, 'F');
}

