    
#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include "printer.h"
#include "nameserver.h"
#include "watCard.h"

_Task NameServer;

_Task VendingMachine {
    Printer &printer;
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    unsigned int stocks[4]; 
    bool restocking;
    void main();
  public:
    enum Flavours { luesBlack_Cherry=0, Classic_Cream_Soda=1, Rock_Root_Beer=2, Jazz_Lime=3 };
    _Event Free {};
    _Event Funds {};
    _Event Stock {}; 
    VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
    void buy( Flavours flavour, WATCard & card );
    unsigned int * inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif
