//
// Created by Lukasz Bakun on 2/27/2019.
//
#include "Ledger.h"
#include <string>
#include <iostream>
#include <map>


Ledger::Ledger() {
long long ID = 0;
}
Ledger::~Ledger() {
    delete this;
}

void Ledger::AddExternalMoney (string ToName, int amount) {
    ID++;
    Node* currentNode = &header;
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    Node* newNode = new Node();
    newNode->amount = amount;
    newNode->id = ID;
    newNode->reciever = ToName;
    newNode->sender = "External";
    currentNode->next = newNode;
    if (currentNode != &header) {
        currentNode->next->last = currentNode;
    }

}

long long Ledger::AddPayment(string FromName, string ToName, int amount) {
    ID++;
    Node* currentNode = &header;
    while (currentNode->next !=nullptr) {
        currentNode = currentNode->next;
    }
    Node* newNode = new Node();
    newNode->amount = amount;
    newNode->id = ID;
    newNode->reciever = ToName;
    newNode->sender = FromName;
    currentNode->next = newNode;
    if (currentNode != &header) {
        currentNode->next->last = currentNode;
    }
    return ID;
}

int Ledger::RefundPayment(long long id) {
    bool foundNode = false;
    Node* currentNode = &header;
    Node* lastNode = &header;
    while(currentNode->next != nullptr) {
        if (currentNode->id != id) {
            lastNode = currentNode;
            currentNode = currentNode->next;
        }
        if (currentNode->id == id) {
            foundNode = true;
            break;
        }
    }
    //backup check to ensure not deleting something not meant to be deleted.
    if (currentNode->id == id) {
        lastNode->next = currentNode->next;
        currentNode->~Node();
    }
    if (foundNode) {
        return 1;
    }
    else return -1;
}

int Ledger::RefundPayment(string FromName, string ToName, int amount) {
    bool  foundNode = false;
    Node* currentNode = &header;
    Node* lastNode = &header;
    while(currentNode->next != nullptr) {
        if (currentNode->sender == FromName && currentNode->reciever == ToName && currentNode->amount == amount) {
            foundNode = true;
            break;
        }
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
    if (foundNode) {
        return 1;
    }
    else return -1;
}

void Ledger::Clear() {
    Node* currentNode = header.next;
    Node* tempLastNode;
    while (currentNode->next != nullptr) {
        currentNode = currentNode->next;
    }
    while (currentNode->last != nullptr) {
        tempLastNode = currentNode->last;
        currentNode->last->next = nullptr;
        currentNode->~Node();
        currentNode = tempLastNode;
    }
}

void Ledger::Print() {
    Node* currentNode = &header;
    while(currentNode->next != nullptr) {
        currentNode = currentNode->next;
        cout << "ID: " << currentNode->id << " Payment from: " << currentNode->sender << ", to: " << currentNode->reciever << ", In the amount of: " << currentNode->amount << endl;
    }
}

void Ledger::Print(string UserName) {
    Node* currentNode = &header;
    while(currentNode->next != nullptr) {
        currentNode = currentNode->next;
        if(currentNode->reciever == UserName || currentNode->sender == UserName) {
            cout << "ID: " << currentNode->id << " Payment from: " << currentNode->sender << ", to: " << currentNode->reciever << ", In the amount of: " << currentNode->amount << endl;
        }
    }
}

void Ledger::Settle() {
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
    cout << "Settling all balances" << endl;
    while (iterator1 != balances.end()) {
        std::string username = iterator1->first;
        int balance = iterator1->second;
        cout << username << ": current balance: " << balance << endl;
        iterator1++;
    }
    cout << endl;
}

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
    cout << "Settling Positive balances" << endl;
    while (iterator1 != balances.end()) {
        std::string username = iterator1->first;
        int balance = iterator1->second;
        if (balance >= 0) {
            cout << username << ": current balance: " << balance << endl;
        }
        iterator1++;
    }
    cout << endl;
}

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
    cout << "Settling Negative balances" << endl;
    while (iterator1 != balances.end()) {
        std::string username = iterator1->first;
        int balance = iterator1->second;
        if (balance < 0) {
            cout << username << ": current balance: " << balance << endl;
        }
        iterator1++;
    }
    cout << endl;
}