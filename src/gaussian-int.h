#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <climits>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cctype>

const std::regex REAL_REGEX{"([+-]?\\d+)"};
const std::regex IMAG_REGEX{"([+-]?)(\\d*)([ij]?)"};
const std::regex REAL_IMAG_REGEX{"([+-]?\\d+)([+-])(\\d*)([ij]?)"};
const std::regex IMAG_REAL_REGEX{"([+-]?)(\\d*)([ij])([+-]\\d+)"};

class GaussianInteger {
    int real;
    int imag;
  public:
    // Constructors
    GaussianInteger();
    GaussianInteger(int real, int imag);
    GaussianInteger(long real, long imag);

    // Accessors
    int getReal() const;
    int getImag() const;
    void setReal(int real);
    void setImag(int imag);

    // Operators
    GaussianInteger operator+(const GaussianInteger& rhs) const;
    GaussianInteger operator-(const GaussianInteger& rhs) const;
    GaussianInteger operator-() const;
    GaussianInteger operator*(const GaussianInteger& rhs) const;
    GaussianInteger operator/(const GaussianInteger& rhs) const;
    bool operator==(const GaussianInteger& rhs) const;
    bool operator!=(const GaussianInteger& rhs) const;

    // Methods
    std::string toString() const;
    GaussianInteger conjugate() const;
    long norm() const;
    std::vector<GaussianInteger> factorise() const;
    GaussianInteger findPrimeFactor() const;
};

GaussianInteger fromString(std::string& input);
long flooredSqrt(long n);
std::ostream& operator<<(std::ostream& out, const GaussianInteger& g);
