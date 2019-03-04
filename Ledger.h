//
// Created by Lukasz Bakun on 2/27/2019.
//

#ifndef LINKEDLISTS_LEDGER_H
#define LINKEDLISTS_LEDGER_H

#include <string>

using namespace std;

struct Node {
    string reciever = "";
    string sender = "";
    int amount = 0;
    long long id = 0;
    Node* next = nullptr;
    Node* last = nullptr;
};

class Ledger {

public:
    Ledger();
    ~Ledger();
    void AddExternalMoney(string ToName,int Amount);
    long long AddPayment(string FromName, string ToName, int Amount);
    int RefundPayment(long long id);
    int RefundPayment(string FromName, string ToName, int amount);
    void Clear();
    void Print();
    void Print(string UserName);
    void Settle();
    void InTheBlack();
    void InTheRed();

private:
    Node header = *new Node;
    long long ID = 0;

};


#endif //LINKEDLISTS_LEDGER_H
