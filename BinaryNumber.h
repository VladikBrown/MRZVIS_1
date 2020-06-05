//
// Created by illfate on 1.05.20.
//

#ifndef PIPELINE_NON_RESTORING_DIVISION_BINARYNUMBER_H
#define PIPELINE_NON_RESTORING_DIVISION_BINARYNUMBER_H


template<typename T>
class BinaryNumber {
    virtual T GetBinary() const = 0;

    virtual T GetDecimal() const = 0;

    virtual T LeftShift() = 0;

    virtual T RightShift() = 0;

    virtual BinaryNumber<T> operator+(BinaryNumber<T>) const = 0;
};


#endif //PIPELINE_NON_RESTORING_DIVISION_BINARYNUMBER_H
