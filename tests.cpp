#include <iostream>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do
// this in one cpp file
#include "catch.hpp"
#include "BiNumber.h"
#include "NonRestoringDivision.h"


// Задание
// алгоритм вычисления целочисленного частного пары 4-разрядных чисел делением без восстановления частичного остатка.

template<typename T>
bool operator==(const std::vector<T> &lhs, const std::vector<T> &rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}



TEST_CASE("Check division") {
    BiNumber dividend(11);
    BiNumber divisor(3);

    NonRestoringDivision div(divisor, dividend);
    auto[quotient, remainder]=div.Process();
    REQUIRE(quotient.GetDecimal() == 3);
    REQUIRE(remainder.GetDecimal() == 2);
}

TEST_CASE("Check division2") {
    BiNumber dividend2(11);
    BiNumber divisor2(2);

    NonRestoringDivision div2(divisor2, dividend2);
    auto[quotient2, remainder2]=div2.Process();
    REQUIRE(quotient2.GetDecimal() == 5);
    REQUIRE(remainder2.GetDecimal() == 1);
}

TEST_CASE("Check division4") {
    BiNumber dividend2(12);
    BiNumber divisor2(2);

    NonRestoringDivision div2(divisor2, dividend2);
    auto[quotient2, remainder2]=div2.Process();
    REQUIRE(quotient2.GetDecimal() == 6);
    REQUIRE(remainder2.GetDecimal() == 0);
}

TEST_CASE("Check division3") {
    BiNumber dividend(0);
    BiNumber divisor(3);

    NonRestoringDivision div(divisor, dividend);
    auto[quotient, remainder]=div.Process();
    REQUIRE(quotient.GetDecimal() == 0);
    REQUIRE(remainder.GetDecimal() == 0);
}



TEST_CASE("Left shift of two") {
    BiNumber first(0);
    BiNumber last(11);
    first.ShiftToLeft(last);
    REQUIRE(first.GetDecimal() == 1);
    REQUIRE(last.GetDecimal() == 6);
}

TEST_CASE("Left shift of two2") {
    BiNumber first(0);
    BiNumber last(5);
    first.ShiftToLeft(last);
    REQUIRE(first.GetDecimal() == 0);
    REQUIRE(last.GetDecimal() == 10);
}


TEST_CASE("Check converting to binary") {
    REQUIRE(BiNumber(5).GetBinary() == std::vector<int>{1, 0, 1, 0});
    REQUIRE(BiNumber(7).GetBinary() == std::vector<int>{1, 1, 1, 0});
    REQUIRE(BiNumber(15).GetBinary() == std::vector<int>{1, 1, 1, 1});
    REQUIRE(BiNumber(0).GetBinary() == std::vector<int>{0, 0, 0, 0});
}

TEST_CASE("Check actual bits") {
    REQUIRE(BiNumber(5).GetNumberOfActualBits() == 3);
    REQUIRE(BiNumber(1).GetNumberOfActualBits() == 1);
    REQUIRE(BiNumber(0).GetNumberOfActualBits() == 0);
    REQUIRE(BiNumber(3).GetNumberOfActualBits() == 2);
    REQUIRE(BiNumber(7).GetNumberOfActualBits() == 3);
    REQUIRE(BiNumber(8).GetNumberOfActualBits() == 4);
}

TEST_CASE("Check converting to inverted binary") {
    REQUIRE(BiNumber(5).GetInvertedBinary() == std::vector<int>{0, 1, 0, 1});
    REQUIRE(BiNumber(7).GetInvertedBinary() == std::vector<int>{0, 0, 0, 1});
    REQUIRE(BiNumber(15).GetInvertedBinary() == std::vector<int>{0, 0, 0, 0});
}

TEST_CASE("Check addition") {
    REQUIRE(BiNumber(5).BiNumber(BiNumber(5)).GetDecimal() == 10);
    REQUIRE(BiNumber(1).BiNumber(BiNumber(5)).GetDecimal() == 6);
    REQUIRE(BiNumber(10).BiNumber(BiNumber(5)).GetDecimal() == 15);
    REQUIRE(BiNumber(12).BiNumber(BiNumber(3)).GetDecimal() == 15);
}

TEST_CASE("Check substraction") {
    auto bin = BiNumber(1);
    bin.Subtract(BiNumber(3));
    REQUIRE(bin.GetBinary() == std::vector<int>{0, 1, 1, 1});
    REQUIRE(BiNumber(5).BiNumber(BiNumber(5)).GetDecimal() == 0);
    REQUIRE(BiNumber(10).BiNumber(BiNumber(5)).GetDecimal() == 5);
    REQUIRE(BiNumber(10).BiNumber(BiNumber(0)).GetDecimal() == 10);
    REQUIRE(BiNumber(10).BiNumber(BiNumber(15)).GetBinary() == std::vector<int>{1, 1, 0, 1});
}

TEST_CASE("Check converting to additional code binary") {
    REQUIRE(BiNumber(5).GetAdditionalBinary() == std::vector<int>{1, 1, 0, 1});
    REQUIRE(BiNumber(4).GetAdditionalBinary() == std::vector<int>{0, 0, 1, 1});
    REQUIRE(BiNumber(15).GetAdditionalBinary() == std::vector<int>{1, 0, 0, 0});
}

TEST_CASE("Check converting to decimal") {
    REQUIRE(BiNumber(5).GetDecimal() == 5);
    REQUIRE(BiNumber(7).GetDecimal() == 7);
    REQUIRE(BiNumber(15).GetDecimal() == 15);
    REQUIRE(BiNumber(0).GetDecimal() == 0);
}

TEST_CASE("Check left shift") {
    REQUIRE(BiNumber(5).ShiftToLeft().GetDecimal() == 10);
    REQUIRE(BiNumber(7).ShiftToLeft().GetDecimal() == 14);
    REQUIRE(BiNumber(15).ShiftToLeft().GetDecimal() == 14);
    REQUIRE(BiNumber(0).ShiftToLeft().GetDecimal() == 0);
}

TEST_CASE("Check right shift") {
    REQUIRE(BiNumber(5).ShiftToRight().GetDecimal() == 2);
    REQUIRE(BiNumber(7).ShiftToRight().GetDecimal() == 3);
    REQUIRE(BiNumber(15).ShiftToRight().GetDecimal() == 7);
    REQUIRE(BiNumber(14).ShiftToRight().GetDecimal() == 7);
    REQUIRE(BiNumber(12).ShiftToRight().GetDecimal() == 6);
    REQUIRE(BiNumber(0).ShiftToRight().GetDecimal() == 0);
}

TEST_CASE("Check string") {
    REQUIRE(BiNumber(5).ToString() == "1010");
}