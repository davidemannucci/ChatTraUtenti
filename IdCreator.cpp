#include "IdCreator.h"
#include <unordered_set>

std::unordered_set<int> IdCreator::idUsed;

int IdCreator::createId() {
    srand(time(nullptr));
    int newId;
    do {
        newId = rand()%9000+1000;
    } while (idUsed.find(newId) != idUsed.end());
    idUsed.insert(newId);
    return newId;
}

void IdCreator::reset() {
    idUsed.clear();
}