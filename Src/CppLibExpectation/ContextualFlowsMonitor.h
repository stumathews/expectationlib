#pragma once
#include <string>

#include "Observer.h"

namespace ExpectationLib
{
	class ContextualFlowsMonitor {
public:
    static std::vector<Observer*> overseers;
    static Observer* GetOverseer(std::string transactionId) {
        for (int i = 0; i < overseers.size(); i++) {
            if (overseers[i]->TransactionId == transactionId) {
                return overseers[i];
            }
        }
        Observer* overseer = new Observer();
        overseer->TransactionId = transactionId;
        overseers.push_back(overseer);
        return overseer;
    }
    static void RemoveOverseer(std::string transactionId) {
        for (int i = 0; i < overseers.size(); i++) {
            if (overseers[i]->TransactionId == transactionId) {
                overseers.erase(overseers.begin() + i);
                break;
            }
        }
    }
};

}
