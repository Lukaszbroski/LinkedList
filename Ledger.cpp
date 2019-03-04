//
// Created by Lukasz Bakun on 2/27/2019.
//
#include "Ledger.h"
#include <string>
#include <stdout>


Ledger::Ledger() {
long long ID = 0;
}

void Ledger::AddExternalMoney (string ToName, int amount) {
    ID++;
    Node currentNode = header;
    while (header.next != nullptr) {
        currentNode = currentNode.next;
    }
    Node newNode = new Node();
    newNode.amount = amount;
    newNode.id = ID;
    newNode.reciever = ToName;
    newNode.sender = "External";
    currentNode.next = newNode;
    currentNode.next.last = currentNode;

}

void Ledger::AddPayment(string FromName, string ToName, int amount) {
    ID++;
    Node currentNode = header;
    while (header.next !=nullptr) {
        currentNode = currentNode.next;
    }
    Node newNode = new Node();
    newNode.amount = amount;
    newNode.id = ID;
    newNode.reciever = ToName;
    newNode.sender = FromName;
    currentNode.next = newNode;
    currentNode.next.last = currentNode;
}

int Ledger::AddPayment(string FromName, string ToName, int amount) {
    ID++;
    Node currentNode = header;
    while (header.next !=nullptr) {
        currentNode = currentNode.next;
    }
    Node newNode = new Node();
    newNode.amount = amount;
    newNode.id = ID;
    newNode.reciever = ToName;
    newNode.sender = FromName;
    currentNode.next = newNode;
    currentNode.next.last = currentNode;
    return ID;
}

void Ledger::RefundPayment(long long id) {
    bool foundNode = false;
    Node currentNode = header;
    Node lastNode = header;
    while(currentNode.next != nullptr) {
        if (currentNode.id != id) {
            lastNode = currentNode;
            currentNode = currentNode.next;
        }
        if (currentNode.id == id) {
            foundNode = true;
            break;
        }
    }
    //backup check to ensure not deleting something not meant to be deleted.
    if (currentNode.id == id) {
        lastNode.next = currentNode.next;
        ~currentNode();
    }
}

void Ledger::RefundPayment(string FromName, string ToName, int amount) {
    bool  foundNode = false;
    Node currentNode = header;
    Node lastNode = header;
    while(currentNode.next != nullptr) {
        if (currentNode.sender == FromName && currentNode.reciever == ToName && currentNode.amount = amount) {
            foundNode = true;
            break;
        }
        else {
            lastNode = currentNode;
            currentNode = currentNode.next;
        }

    }
    //redundant backup check to ensure that delete is deleting currect node
    if (currentNode.sender == FromName && currentNode.reciever == ToName && currentNode.amount = amount) {
        lastNode.next = currentNode.next;
        ~currentNode();
    }
}

void Ledger::clear() {
    Node currentNode = header.next;
    while (currentNode.next != nullptr) {
        currentNode = currentNode.next;
    }
    while (currentNode.last != nullptr) {
        tempLastNode = currentNode.last;
        currentNode.last.next = nullptr;
        ~currentNode();
        tempLastNode = currentNode;
    }
}

void Ledger::print() {
    Node currentNode = header;
    while(currentNode.next != nullptr) {
        currentNode = currentNode.next;
        cout << "ID: " << currentNode.id << " Payment from: " << currentNode.sender << " to: " << currentNode.reciever << " In the amount of: " << currentNode.amount << endl;
    }
}

void Ledger::print(string UserName) {
    Node currentNode = header;
    while(currentNode.next != nullptr) {
        currentNode = currentNode.next;
        if(currentNode.reciever == UserName || currentNode.sender == UserName) {
            cout << "ID: " << currentNode.id << " Payment from: " << currentNode.sender << " to: " << currentNode.reciever << " In the amount of: " << currentNode.amount << endl;
        }
    }
}

void Ledger::settle() {

}

void Ledger::InTheBlack() {
    Node currentNode = header;


}