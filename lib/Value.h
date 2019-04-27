//
// Created by Andrey on 18.04.2019.
//

#ifndef HYDROLIB2_VALUE_H
#define HYDROLIB2_VALUE_H

class Value {
public:
    virtual int getInt() = 0;
    virtual float getFloat() = 0;
    virtual bool  getBool() = 0;
    virtual ~Value() = default;
};
template <class T>
class ValueImpl: public Value {
    const T mValue;
public:
    explicit ValueImpl(T aVal): mValue(aVal) {}
    int getInt() override { return (int)mValue; };
    float getFloat() override { return (float)mValue;};
    bool  getBool() override { return (bool) mValue; }
};



#endif //HYDROLIB2_VALUE_H
