//
// Created by Andrey on 18.04.2019.
//

#ifndef HYDROLIB2_VALUE_H
#define HYDROLIB2_VALUE_H

#include "HydroObject.h"

class Value {
public:
    virtual int getInt() = 0;

    virtual float getFloat() = 0;

    virtual bool getBool() = 0;

    virtual HydroObject *getObj() = 0;

    virtual ~Value() = default;
};

template<class T>
class ValueImpl : public Value {
    const T mValue;
public:
    explicit ValueImpl(T aVal) : mValue(aVal) {}

    int getInt() override { return static_cast<int>(mValue); }

    float getFloat() override { return static_cast<float>(mValue); }

    bool getBool() override { return static_cast<bool>(mValue); }

    HydroObject *getObj() override { return nullptr; }
};

class ValueObj : public Value {
    HydroObject *mValue;
public:
    explicit ValueObj(HydroObject *aVal);

    int getInt() override;

    float getFloat() override;

    bool getBool() override;

    HydroObject *getObj() override;

    ~ValueObj() override;
};


#endif //HYDROLIB2_VALUE_H
