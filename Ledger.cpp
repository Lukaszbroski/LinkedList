//
// Created by Lukasz Bakun on 2/27/2019.
// Includes all implementations of methods in Ledger
#include "Ledger.h"
#include <string>
#include <iostream>
#include <map>

//Constructor
Ledger::Ledger() {
long long ID = 0;
}
//Deconstructor
//This is the only thing I was able to find on the internet for how to setup deconstructors, so I hope this is correct
Ledger::~Ledger() {
    header.~Node();
}
//Add External Money
//Inputs (string ToName, int amount): ToName = reciever of money, amount = amount of money recieved
long long Ledger::AddExternalMoney (string ToName, int amount) {
    ID++; //Increments ID for uniqueness
    Node* currentNode = &header;
    //Find the last node
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    //Create a new node with correct input
    Node* newNode = new Node();
    newNode->amount = amount;
    newNode->id = ID;
    newNode->reciever = ToName;
    newNode->sender = "External"; //from external source
    //set the new last node to the new node
    currentNode->next = newNode;
    //we dont want the 2nd to last node to connect to the header
        currentNode->next->last = currentNode;
    return ID;

}
//Adds a payment between two users
//Inputs (string FromName, string toName, int amount) FromName = sender, ToName = reciever, amount = amount
long long Ledger::AddPayment(string FromName, string ToName, int amount) {
    ID++; // Increments Unique ID
    Node* currentNode = &header;
    //Find the last Node in the ledger
    while (currentNode->next !=nullptr) {
        currentNode = currentNode->next;
    }
    //Create a new Node with the correct fields
    Node* newNode = new Node();
    newNode->amount = amount;
    newNode->id = ID;
    newNode->reciever = ToName;
    newNode->sender = FromName;
    //set new end node as current Node
    currentNode->next = newNode;
    //dont let the node connect to the header
        currentNode->next->last = currentNode;
    return ID;
}
//Removes a node with the ID = to the input ID
//this method was created before I implemented node.last* so Im keeping it as legacy as im running out of time to fix it
int Ledger::RefundPayment(long long id) {
    bool foundNode = false; //keeps track of whether or not the ID was found in the ledger
    Node* currentNode = &header;    //current Node
    Node* lastNode = &header;   //Last Node starts as header but will eventually be the last one in order to link properly
    //While not at the end of the ledger
    while(currentNode->next != nullptr) {
        //if the node is not what we are looking for: increment
        if (currentNode->id != id) {
            lastNode = currentNode; // sets the last node to the current node before incrementing
            currentNode = currentNode->next;
        }
        //if it is, break and set to true;
        else {
            foundNode = true;
            break;
        }
    }
    //backup check to ensure not deleting something not meant to be deleted.
    if (currentNode->id == id) {
        lastNode->next = currentNode->next;
        currentNode->~Node();
    }
    //return 1 if found, or -1 if not found
    if (foundNode) {
        return 1;
    }
    else return -1;
}
//Refund payment by Info inputted instead of by ID
//this method was created before I implemented node.last* so Im keeping it as legacy as im running out of time to fix it
int Ledger::RefundPayment(string FromName, string ToName, int amount) {
    bool  foundNode = false; //keeps track of whether or not the ID was found in the ledger
    Node* currentNode = &header; // current node used for tracking
    Node* lastNode = &header;   //Last node used for tracking, starts as header, but turns into the last node later on
    //while not at the end
    while(currentNode->next != nullptr) {
        //see if the data matches on the currentNode
        if (currentNode->sender == FromName && currentNode->reciever == ToName && currentNode->amount == amount) {
            foundNode = true;
            break;
        }
        //if not increment
        else {
            lastNode = currentNode;
            currentNode = currentNode->next;
        }
    }
    //redundant backup check to ensure that delete is deleting currect node
    if (currentNode->sender == FromName && currentNode->reciever == ToName && currentNode->amount == amount) {
        lastNode->next = currentNode->next;
        currentNode->~Node();

    }
    //return 1 if removed, otherwise dont remove and return -1
    if (foundNode) {
        return 1;
    }
    else return -1;
}
//Method that clears the whole ledger, other than the header.
void Ledger::Clear() {
    Node* currentNode = header.next;
    Node* tempLastNode = nullptr; // temp last node to backtrack, since the current node will be deconstructed
    //get to the end of the ledger
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    //until we get back to the beginning
    while (currentNode->last != nullptr) {
        tempLastNode = currentNode->last;
        //disconnect nodes and deconstruct them
        currentNode->last->next = nullptr;
        currentNode->~Node();
        currentNode = tempLastNode;
    }
}
//prints out all transactions and nodes in the ledger
void Ledger::Print() {
    cout << "setting header" << endl;
    if (header.next != nullptr) {
        Node *currentNode = &header;
        cout << "header set, attempting to loop" << endl;
        //until we reach the end, print out the node info
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
            cout << "ID: " << currentNode->id << " Payment from: " << currentNode->sender << ", to: "
                 << currentNode->reciever << ", In the amount of: " << currentNode->amount << endl;
        }
    }
}
//prints out all transactions with the username as the sender or reciever
void Ledger::Print(string UserName) {
    if (header.next != nullptr) {
        Node *currentNode = &header;
        //until we reach the end, print out node info pertaining to the username provided
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
            if (currentNode->reciever == UserName || currentNode->sender == UserName) {
                cout << "ID: " << currentNode->id << " Payment from: " << currentNode->sender << ", to: "
                     << currentNode->reciever << ", In the amount of: " << currentNode->amount << endl;
            }
        }
    }
}
//prints out all end balances for all users
void Ledger::Settle() {
    Node* currentNode = &header;
    std::map<std::string, int> balances;    //creates a map for all users and their balance
    //while not at the end
    while(currentNode->next != nullptr) {
        currentNode = currentNode->next;
        //if not an external source, subtract balance from senders, and add balance to recievers
        if(currentNode->sender != "External") {
            balances[currentNode->sender] -= currentNode->amount;
        }
        balances[currentNode->reciever] += currentNode->amount;
    }
    //iterate through all balances printing out names and balances
    std::map<std::string, int>::iterator iterator1 = balances.begin();
    cout << "Settling all balances" << endl;
    while (iterator1 != balances.end()) {
        std::string username = iterator1->first;
        int balance = iterator1->second;
        cout << username << ": current balance: " << balance << endl;
        iterator1++;
    }
    cout << endl;
}
//prints out all positive balances for users.
//pretty close to a direct copy of settle with a slight change
void Ledger::InTheBlack() {
    Node* currentNode = &header;
    std::map<std::string, int> balances;
    while(currentNode->next != nullptr) {
        currentNode = currentNode->next;
        if(currentNode->sender != "External") {
            balances[currentNode->sender] -= currentNode->amount;
        }
        balances[currentNode->reciever] += currentNode->amount;
    }
    std::map<std::string, int>::iterator iterator1 = balances.begin();
    cout << "Settling Positive balances" << endl; //changed to positive
    while (iterator1 != balances.end()) {
        std::string username = iterator1->first;
        int balance = iterator1->second;
        if (balance >= 0) { //requires balance to be positive or 0
            cout << username << ": current balance: " << balance << endl;
        }
        iterator1++;
    }
    cout << endl;
}
//prints out all negative balances for users.
//also pretty close to a direct copy of settle with a slight change.
void Ledger::InTheRed() {
    Node* currentNode = &header;
    std::map<std::string, int> balances;
    while(currentNode->next != nullptr) {
        currentNode = currentNode->next;
        if(currentNode->sender != "External") {
            balances[currentNode->sender] -= currentNode->amount;
        }
        balances[currentNode->reciever] += currentNode->amount;
    }
    std::map<std::string, int>::iterator iterator1 = balances.begin();
    cout << "Settling Negative balances" << endl;  //changed to be negative
    while (iterator1 != balances.end()) {
        std::string username = iterator1->first;
        int balance = iterator1->second;
        if (balance < 0) { //requires balance to be below 0
            cout << username << ": current balance: " << balance << endl;
        }
        iterator1++;
    }
    cout << endl;
}