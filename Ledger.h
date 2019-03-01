//
// Created by Lukasz Bakun on 2/27/2019.
//

#ifndef LINKEDLISTS_LEDGER_H
#define LINKEDLISTS_LEDGER_H

#include <string>

using namespace std;

struct Node {
    string reciever;
    string sender;
    int amount;
    long long id;
    Node* next;
};

class Ledger {

public:
    Ledger();
    ~Ledger();
    void AddExternalMoney(string ToName,int Amount);
    void AddPayment(string FromName, string ToName, int Amount);
    void RefundPayment(long long id);
    void RefundPayment(string FromName, string ToName, int amount);
    void Clear();
    void Print();
    void Print(string UserName);
    void Settle();
    void InTheBlack();
    void InTheRed();

private:
    Node header = *new Node;

};


#endif //LINKEDLISTS_LEDGER_H
