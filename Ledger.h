//
// Created by Lukasz on 2/27/2019.
//
// Class Ledger definition with all methods of Ledger along with a Struct Node

#ifndef LINKEDLISTS_LEDGER_H
#define LINKEDLISTS_LEDGER_H
#include <string>

using namespace std;

//each node in our LinkedList Ledger that is setup properly with all info necessary
//default values are set so that it is good for the header along with avoiding issues possible
struct Node {
    string reciever = "";
    string sender = "";
    int amount = 0;
    long long id = 0;
    Node* next = nullptr;
    Node* last = nullptr;
};

//Class Ledger definitions with all methods
class Ledger {

public:
    Ledger();   //Constructor
    ~Ledger();  //Deconstructor
    long long AddExternalMoney(string ToName,int Amount);    //Add money to an account from external source aka Cash
    long long AddPayment(string FromName, string ToName, int Amount);   //transfer money between 2 users
    int RefundPayment(long long id);    //Remove a node with the ID
    int RefundPayment(string FromName, string ToName, int amount);  //Remove a Node with the specified info
    void Clear();   //Clear the linked List
    void Print();   //Print all Nodes in the ledger
    void Print(string UserName);    //Print all nodes involving UserName in the ledger
    void Settle();  //Print all balances for all users
    void InTheBlack();  //Prints all Positive Balances
    void InTheRed();    //Prints all Negative Balances

private:
    Node header = *new Node;    //Creates a New Node as the Header with Default Values, next is to be added later
    long long ID = 0;   //ID that will (hopefully) never repeat

};


#endif //LINKEDLISTS_LEDGER_H
