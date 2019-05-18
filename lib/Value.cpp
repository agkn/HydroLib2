//
// Created by Andrey on 18.04.2019.
//

#include "Value.h"

ValueObj::~ValueObj() {
    delete(mValue);
}

HydroObject *ValueObj::getObj() { return mValue; }

bool ValueObj::getBool() { return false; }

float ValueObj::getFloat() { return 0; }

int ValueObj::getInt() { return 0; }

ValueObj::ValueObj(HydroObject *aVal) : mValue(aVal) {}
