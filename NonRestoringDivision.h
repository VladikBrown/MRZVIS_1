#ifndef PIPELINE_NON_RESTORING_DIVISION_NONRESTORINGDIVISION_H
#define PIPELINE_NON_RESTORING_DIVISION_NONRESTORINGDIVISION_H


#include "BiNumber.h"
#include <iostream>

struct DivisionResult {
    BiNumber quotient;
    BiNumber remainder;
};

class NonRestoringDivision {
public:
    NonRestoringDivision(BiNumber divisor, BiNumber divided) : divisor(divisor), dividend(divided) {

    }

    DivisionResult Process() {
        int numBits = dividend.GetNumberOfActualBits();
        BiNumber temp(0);
        for (int i = 0; i < numBits; ++i) {
            processFirstStep(temp);
            processSecondStep(temp);
        }
        if (temp.GetLastBit()) {
            temp.Add(divisor);
        }
        return {dividend, temp};
    }



private:
    BiNumber divisor;
    BiNumber dividend;

    void processFirstStep(BiNumber &temp) {
        if (!temp.GetLastBit()) {
            temp.ShiftToLeft(dividend);
            temp.Subtract(divisor);
        } else {
            temp.ShiftToLeft(dividend);
            temp.Add(divisor);
        }
    }

    void processSecondStep(BiNumber &temp) {
        if (!temp.GetLastBit()) {
            dividend.SetFirstBit(1);
        } else {
            dividend.SetFirstBit(0);
        }
    }
};


#endif //PIPELINE_NON_RESTORING_DIVISION_NONRESTORINGDIVISION_H
