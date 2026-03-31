/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef RATION_NUM_H
#define RATION_NUM_H
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <numeric>
#include <sstream>

#include "log.h"

// (n / m) m>0
struct RationNum {
    int64_t n = 0;
    int64_t m = 1;
    int64_t maxPrecision = 10000000; // 最大精度为小数点后7位
    static constexpr int64_t kMaxFractionOverflow = 1000000000000000LL; // 1e15
    static constexpr int kMaxContinuedFractionIterations = 20;
    static constexpr double kDoubleMinThreshold = 1e-15;
    RationNum() {}
    RationNum(const RationNum& other) : n(other.n), m(other.m), maxPrecision(other.maxPrecision) {}
    explicit RationNum(int64_t num) : n(num) {}
    RationNum(int64_t num1, int64_t num2) : n(num1), m(num2)
    {
        if (m == 0) {
            n = 0;
            m = 1;
        }
    }
    explicit RationNum(std::string& r1)
    {
        size_t pos = r1.find("/");
        if (pos == std::string::npos) {
            this->n = atoll(r1.c_str());
        } else {
            std::string str1 = r1.substr(0, pos);
            this->n = atoll(str1.c_str());
            std::string str2 = r1.substr(pos + 1, r1.size());
            this->m = atoll(str2.c_str());
        }
        if (m == 0) {
            n = 0;
            m = 1;
        }
    }
    void Simplify()
    {
        if (m < 0) {
            n = -n;
            m = -m;
        }
        int64_t gcd = std::gcd(std::abs(this->n), this->m);
        this->n /= gcd;
        this->m /= gcd;

        if (maxPrecision > 0 && m > maxPrecision) {
            double val = static_cast<double>(n) / static_cast<double>(m);
            int64_t newN = static_cast<int64_t>(std::round(std::abs(val) * static_cast<double>(maxPrecision)));
            newN *= val < 0 ? -1 : 1;
            n = newN;
            m = maxPrecision;
        }
    }
    RationNum& operator=(const int64_t& r1)
    {
        this->n = r1;
        this->m = 1;
        return *this;
    }
    RationNum& operator=(const RationNum& r1)
    {
        this->n = r1.n;
        this->m = r1.m;
        return *this;
    }

    RationNum operator*(const RationNum& r1) const
    {
        RationNum rNew(this->n * r1.n, this->m * r1.m);
        rNew.Simplify();
        return rNew;
    }
    RationNum& operator*=(const RationNum& r1)
    {
        *this = *this * r1;
        return *this;
    }
    RationNum& operator*=(const int64_t& r1)
    {
        *this = ((*this) * RationNum(r1));
        return *this;
    }

    // 所有除数由调用方保证不为0
    RationNum operator/(const RationNum& r1) const
    {
        RationNum rNew(n, m);
        if (r1.n == 0) { // 如果r1的分子等于0，说明发生了除零错误，转为除以1/maxPrecision
            rNew.n *= maxPrecision;
        } else {
            rNew.n *= r1.m;
            rNew.m *= r1.n;
        }
        if (rNew.m < 0) {
            rNew.n = -rNew.n;
            rNew.m = -rNew.m;
        }
        rNew.Simplify();
        return rNew;
    }

    RationNum& operator/=(const RationNum& r1)
    {
        *this = *this / r1;
        return *this;
    }
    RationNum& operator/=(const int64_t& r1)
    {
        *this = ((*this) / RationNum(r1));
        return *this;
    }
    friend RationNum operator/(const int& a, const RationNum& b)
    {
        return RationNum(a) / b;
    }

    RationNum operator+(const RationNum& r1) const
    {
        int64_t newM = std::lcm(this->m, r1.m);
        int64_t newN = ((newM / this->m) * this->n) + ((newM / r1.m) * r1.n);
        RationNum rNew(newN, newM);
        rNew.Simplify();
        return rNew;
    }

    RationNum& operator+=(const RationNum& r1)
    {
        *this = *this + r1;
        return *this;
    }

    RationNum operator-(const RationNum& r1) const
    {
        int64_t newM = std::lcm(this->m, r1.m);
        int64_t newN = ((newM / this->m) * this->n) - ((newM / r1.m) * r1.n);
        RationNum rNew(newN, newM);
        rNew.Simplify();
        return rNew;
    }
    RationNum& operator-=(const RationNum& r1)
    {
        *this = *this - r1;
        return *this;
    }
    RationNum operator-() const
    {
        return RationNum(-this->n, this->m);
    }
    friend RationNum operator-(const int& a, const RationNum& b)
    {
        return RationNum(a) - b;
    }

    bool operator>(const RationNum& r1) const
    {
        return this->n * r1.m > r1.n * this->m;
    }
    bool operator>(const int& r1) const
    {
        return this->n > r1 * this->m;
    }
    friend bool operator>(const int& a, const RationNum& b)
    {
        return a * b.m > b.n;
    }

    bool operator>=(const RationNum& r1) const
    {
        return this->n * r1.m >= r1.n * this->m;
    }
    bool operator>=(const int& r1) const
    {
        return this->n >= r1 * this->m;
    }
    friend bool operator>=(const int& a, const RationNum& b)
    {
        return a * b.m >= b.n;
    }

    bool operator<(const RationNum& r1) const
    {
        return this->n * r1.m < r1.n * this->m;
    }
    bool operator<(const int& r1) const
    {
        return this->n < r1 * this->m;
    }
    friend bool operator<(const int& a, const RationNum& b)
    {
        return a * b.m < b.n;
    }

    bool operator<=(const RationNum& r1) const
    {
        return this->n * r1.m <= r1.n * this->m;
    }
    bool operator<=(const int& r1) const
    {
        return this->n <= r1 * this->m;
    }
    friend bool operator<=(const int& a, const RationNum& b)
    {
        return a * b.m <= b.n;
    }

    bool operator==(const RationNum& r1) const
    {
        return this->n * r1.m == r1.n * this->m;
    }
    bool operator==(const int& r1) const
    {
        return this->n == r1 * this->m;
    }
    bool operator==(const uint64_t& r1) const
    {
        return this->n == static_cast<int>(r1) * this->m;
    }
    friend bool operator==(const int& a, const RationNum& b)
    {
        return (a * b.m) == b.n;
    }

    bool operator!=(const RationNum& r1) const
    {
        return this->n * r1.m != r1.n * this->m;
    }
    bool operator!=(const int& r1) const
    {
        return this->n != r1 * this->m;
    }
    friend bool operator!=(const int& a, const RationNum& b)
    {
        return a * b.m != b.n;
    }

    RationNum Abs() const
    {
        return RationNum(std::abs(this->n), this->m);
    }
    int64_t ToInt()
    {
        return (this->n / this->m);
    }
    double ToDouble()
    {
        return static_cast<double>(this->n) / static_cast<double>(this->m);
    }

    static RationNum FromDouble(double v, double epsilon = 1e-12)
    {
        if (v < 0) {
            RationNum res = FromDouble(-v, epsilon);
            return RationNum(-res.n, res.m);
        }

        double x = v;
        
        // 迭代所需的变量：h/k 表示当前的分数
        int64_t h0 = 0;
        int64_t h1 = 1; // 分子序列
        int64_t k0 = 1;
        int64_t k1 = 0; // 分母序列
        
        // 限制迭代次数防止死循环或溢出
        for (int i = 0; i < kMaxContinuedFractionIterations; i++) {
            int64_t a = static_cast<int64_t>(std::floor(x));
            int64_t h2 = a * h1 + h0;
            int64_t k2 = a * k1 + k0;

            // 检查溢出保护：如果分母或分子过大，停止迭代
            if (std::abs(h2) > 1e15 || std::abs(k2) > 1e15) {
                break;
            }
            h0 = h1; 
            h1 = h2;
            k0 = k1; 
            k1 = k2;

            if (std::abs(v - static_cast<double>(h1) / k1) < epsilon) {
                break;
            }

            double r = x - a;
            if (std::abs(r) < kDoubleMinThreshold) {
                break;
            }
            x = 1.0 / r;
        }

        return RationNum(h1, k1);
    }

    RationNum Pow(int exp)
    {
        return RationNum(std::pow(this->n, exp), std::pow(this->m, exp));
    }

    std::string Print() const
    {
        std::stringstream ss;
        if (this->m == 1) {
            ss << this->n;
        } else {
            ss << std::fixed << std::setprecision(1) << static_cast<float>(this->n) / static_cast<float>(this->m);
        }
        return ss.str();
    }

    // if it is an integer, then +/- 1, else round to the closest integer
    RationNum UpperRound()
    {
        int64_t n1 = (this->m == 1)
                         ? (this->n + 1)
                         : static_cast<int64_t>(std::ceil(static_cast<double>(this->n) / static_cast<double>(this->m)));
        return RationNum(n1);
    }
    RationNum LowerRound()
    {
        int64_t n1 = (this->m == 1) ? (this->n - 1)
                                    : static_cast<int64_t>(
                                          std::floor(static_cast<double>(this->n) / static_cast<double>(this->m)));
        return RationNum(n1);
    }
};
#endif