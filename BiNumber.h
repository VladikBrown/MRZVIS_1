#ifndef PIPELINE_NON_RESTORING_DIVISION_BINUMBER_H
#define PIPELINE_NON_RESTORING_DIVISION_BINUMBER_H

#include <vector>
#include <algorithm>



class BiNumber {
public:
    explicit BiNumber(int n) {
        data_number = toBinary(n);
    }

    explicit BiNumber(const std::vector<int> num) {
        data_number = num;
    }

    BiNumber(const BiNumber &number) {
        data_number = number.data_number;
    }

    BiNumber &operator=(const BiNumber &number) {
        data_number = number.data_number;
        return *this;
    }

    [[nodiscard]] std::vector<int> GetBinary() const {
        return data_number;
    }

    [[nodiscard]] std::vector<int> GetInvertedBinary() const {
        std::vector<int> result;
        result.resize(4);
        for (int i = 0; i < data_number.size(); ++i) {
            result[i] = !data_number[i];
        }
        return result;
    }

    BiNumber Add(const BiNumber &num) {
        std::vector<int> sum(SIZE, 0);

        int carry = 0;
        for (int i = 0; i < SIZE; i++) {
            sum[i] = ((data_number[i] ^ num.data_number[i]) ^ carry);
            carry = ((data_number[i] & num.data_number[i]) | (data_number[i] & carry)) | (num.data_number[i] & carry);
        }

        BiNumber res(0);
        res.data_number = sum;
        this->data_number = sum;
        return res;
    }

    BiNumber Subtract(const BiNumber &num) {
        auto addNum = num.GetAdditionalBinary();
        auto additionalBinary = BiNumber(addNum);
        this->data_number = Add(additionalBinary).data_number;
        return *this;
    }


    void SetFirstBit(bool bit) {
        data_number[0] = bit;
    }

    void SetLastBit(bool bit) {
        data_number[SIZE-1] = bit;
    }

    int GetFirstBit() const {
        return data_number[0];
    }

    int GetLastBit() const {
        return data_number[SIZE-1];
    }

    [[nodiscard]] std::vector<int> GetAdditionalBinary() const {
        BiNumber one(0);
        one.data_number = ONE;
        BiNumber res(0);
        res.data_number = GetInvertedBinary();
        return res.Add(one).GetBinary();
    }

    [[nodiscard]] int64_t GetDecimal() const {
        return toDecimal();
    }

    int GetNumberOfActualBits() const {
        for (auto it = data_number.rbegin(); it != data_number.rend(); ++it) {
            if (*it == 1) {
                return data_number.rend() - it;
            }
        }
        return 0;
    }

    void Log(const std::string &name, std::ostream &os) const {
        os << name << ": " << NormalizedOutput() << std::endl;
    }

    BiNumber ShiftToLeft() {
        std::vector<int> temp = std::vector<int>(data_number.begin(), data_number.end() - 1);
        temp.emplace(temp.begin(), 0);
        data_number = temp;
        return *this;
    }

    BiNumber ShiftToLeft(BiNumber &num) {
        ShiftToLeft();
        data_number[0] = num.GetLastBit();
        num.ShiftToLeft();
        return *this;
    }

    BiNumber ShiftToRight() {
        std::vector<int> temp = std::vector<int>(next(data_number.begin()), data_number.end());
        temp.push_back(0);
        data_number = temp;
        return *this;
    }

    std::string ToString() const {
        std::string res;
        for (auto x: data_number) {
            res += std::to_string(x);
        }
        return res;
    }

    std::string NormalizedOutput() const {
        auto res = ToString();
        return {res.rbegin(), res.rend()};
    }

private:
    const int SIZE = 4;
    std::vector<int> data_number;
    const std::vector<int> ONE = {1, 0, 0, 0};

    static std::vector<int> toBinary(int n) {
        int mod;
        std::vector<int> result;

        for (int i = 0; n > 0; i++) {
            mod = n % 2;
            n = (n - mod) / 2;
            result.push_back(mod);
        }

        for (int i = 0; i < result.size() - 4; ++i) {
            result.push_back(0);
        }
        return std::move(result);
    }

    [[nodiscard]] int64_t toDecimal() const {
        int64_t result = 0;
        for (size_t i = 0; i < data_number.size(); ++i) {
            if (data_number[i] == 1) {
                result += pow(2, i);
            }
        }
        return result;
    }
};


#endif //PIPELINE_NON_RESTORING_DIVISION_BINUMBER_H
