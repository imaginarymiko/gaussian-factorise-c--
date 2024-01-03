#include "gaussian-int.h"

GaussianInteger::GaussianInteger(): real(0), imag(0) {}

GaussianInteger::GaussianInteger(int real, int imag): real(real), imag(imag) {
    if (real == INT_MIN || real == INT_MAX || imag == INT_MIN || imag == INT_MAX) {
        throw std::overflow_error("GaussianInteger overflow");
    }
}

GaussianInteger::GaussianInteger(long real, long imag) {
    if (real <= INT_MIN || real >= INT_MAX || imag <= INT_MIN || imag >= INT_MAX) {
        throw std::overflow_error("GaussianInteger overflow");
    } else {
        this->real = static_cast<int>(real);
        this->imag = static_cast<int>(imag);
    }
}

// Accessors
int GaussianInteger::getReal() const { return real; }
int GaussianInteger::getImag() const { return imag; }
void GaussianInteger::setReal(int real) { 
    if (real == INT_MIN || real == INT_MAX) {
        throw std::overflow_error("GaussianInteger overflow");
    } else {
        this->real = real; 
    }
}
void GaussianInteger::setImag(int imag) { 
    if (imag == INT_MIN || imag == INT_MAX) {
        throw std::overflow_error("GaussianInteger overflow");
    } else {
        this->imag = imag; 
    }
}

// Operators
GaussianInteger GaussianInteger::operator+(const GaussianInteger& rhs) const {
    long re = static_cast<long>(real) + rhs.real;
    long im = static_cast<long>(imag) + rhs.imag;
    try {
        return GaussianInteger(re, im);
    } catch (std::overflow_error& e) {
        throw std::overflow_error("GaussianInteger overflow");
    }
}
GaussianInteger GaussianInteger::operator-(const GaussianInteger& rhs) const {
    return GaussianInteger(real - rhs.real, imag - rhs.imag);
}
GaussianInteger GaussianInteger::operator-() const {
    return GaussianInteger(-real, -imag);
}
GaussianInteger GaussianInteger::operator*(const GaussianInteger& rhs) const {
    long re = static_cast<long>(real) * rhs.real - static_cast<long>(imag) * rhs.imag;
    long im = static_cast<long>(real) * rhs.imag + static_cast<long>(imag) * rhs.real;
    try {
        return GaussianInteger(re, im);
    } catch (std::overflow_error& e) {
        throw std::overflow_error("GaussianInteger overflow");
    }
}
bool isDivisibleBy(const GaussianInteger& g1, const GaussianInteger& g2) {
    // Helper function to check if a GaussianInteger is divisible by another
    long divisorNorm = g2.norm();
    long realPart = static_cast<long>(g1.getReal());
    long imagPart = static_cast<long>(g1.getImag());
    bool divisible1 = (realPart * g2.getReal() + imagPart * g2.getImag()) % divisorNorm == 0;
    bool divisible2 = (-realPart * g2.getImag() + imagPart * g2.getReal()) % divisorNorm == 0;
    return divisible1 && divisible2;
}
GaussianInteger GaussianInteger::operator/(const GaussianInteger& rhs) const {
    if (rhs.real == 0 && rhs.imag == 0) {
        throw std::invalid_argument("Division by zero");
    } else if (!isDivisibleBy(*this, rhs)) {
        throw std::invalid_argument("Division not exact");
    } else {
        long re = (static_cast<long>(real) * rhs.real + static_cast<long>(imag) * rhs.imag) / rhs.norm();
        long im = (static_cast<long>(-real) * rhs.imag + static_cast<long>(imag) * rhs.real) / rhs.norm();
        try {
            return GaussianInteger(re, im);
        } catch (std::overflow_error& e) {
            throw std::overflow_error("GaussianInteger overflow");
        }
    }
}
bool GaussianInteger::operator==(const GaussianInteger& rhs) const {
    return real == rhs.real && imag == rhs.imag;
}
bool GaussianInteger::operator!=(const GaussianInteger& rhs) const {
    return !(*this == rhs);
}
ostream& operator<<(ostream& os, const GaussianInteger& g) {
    os << g.toString() << endl;
    return os;
}

// Methods
string GaussianInteger::toString() const {
    string real_str = to_string(real);
    string imag_str;
    if (imag == 1) {
        imag_str = "";
    } else if (imag == -1) {
        imag_str = "-";
    } else {
        imag_str = to_string(imag);
    }
    if (imag == 0) {
        return real_str;
    } else if (real == 0) {
        return imag_str + "i";
    } else if (imag > 0) {
        return real_str + " + " + imag_str + "i";
    } else {
        return real_str + " - " + to_string(-imag) + "i";
    }
}
GaussianInteger GaussianInteger::conjugate() const {
    return GaussianInteger(real, -imag);
}
long GaussianInteger::norm() const {
    // Prevent overflow by casting to long before multiplying
    return static_cast<long>(real) * real + static_cast<long>(imag) * imag;
}
GaussianInteger GaussianInteger::findPrimeFactor() const {
    // Find a Gaussian prime factor of a GaussianInteger
    long n = norm();
    if (n % 2 == 0) {
        return GaussianInteger(1, 1);
    } else {
        long m = flooredSqrt(n);
        for (long i = 3; i <= m; i += 2) {
            if (n % i == 0) {
                if (i % 4 == 3) {
                    return GaussianInteger(i, 0l);
                } else {
                    for (long re = flooredSqrt(i); re > 0; re--) {
                        long im = flooredSqrt(i - re * re);
                        if (re * re + im * im == i) {
                            if (re > INT_MAX || im > INT_MAX) {
                                throw std::overflow_error("GaussianInteger overflow");
                            } else if (isDivisibleBy(*this, GaussianInteger(static_cast<int>(re), static_cast<int>(im)))) {
                                return GaussianInteger(static_cast<int>(re), static_cast<int>(im));
                            }
                        }
                    }
                }
            }
        }
        GaussianInteger g = *this;
        while (g.real < 0 || g.imag < 0) {
            g = g * GaussianInteger(0, 1);
        }
        return g;
    }
}
vector<GaussianInteger> GaussianInteger::factorise() const {
    // Factorise a GaussianInteger into Gaussian primes
    vector<GaussianInteger> factors;
    GaussianInteger g = *this;
    if (g.norm() <= 1) {
        factors.push_back(g);
        return factors;
    }
    GaussianInteger gCheck = GaussianInteger(1, 0);
    while (g.norm() > 1) {
        GaussianInteger prime = g.findPrimeFactor();
        factors.push_back(prime);
        g = g / prime;
        gCheck = gCheck * prime;
    }
    gCheck = gCheck * g;
    if (g.norm() != 1 || gCheck != *this) {
        throw std::runtime_error("Factorisation failed");
    }
    if (g.getReal() != 1) factors.push_back(g);
    sort(factors.begin(), factors.end(), [](const GaussianInteger& g1, const GaussianInteger& g2) {
        return (g1.norm() < g2.norm()) || ((g1.norm() == g2.norm()) && (g1.getReal() < g2.getReal()));
    });
    return factors;
}
long flooredSqrt(long n) {
    // Find the square root of a long
    if (n < 0) {
        throw std::invalid_argument("Cannot find square root of negative number");
    } else {
        return static_cast<long>(sqrt(n));
    }
}
GaussianInteger fromString(string input) {
    // Parse a string into a GaussianInteger
    int real_comp;
    int imag_comp;
    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
    smatch match;
    if (regex_match(input, match, REAL_REGEX)) {
        real_comp = stoi(match[1]);
        imag_comp = 0;
    } else if (regex_match(input, match, IMAG_REGEX)) {
        real_comp = 0;
        imag_comp = (match[1] == "-" ? -1 : 1) * (match[2].str().empty() ? 1 : stoi(match[2]));
    } else if (regex_match(input, match, REAL_IMAG_REGEX)) {
        real_comp = stoi(match[1]);
        imag_comp = (match[2] == "-" ? -1 : 1) * (match[3].str().empty() ? 1 : stoi(match[3]));
    } else if (regex_match(input, match, IMAG_REAL_REGEX)) {
        real_comp = stoi(match[4]);
        imag_comp = (match[1] == "-" ? -1 : 1) * (match[2].str().empty() ? 1 : stoi(match[2]));
    } else {
        throw std::invalid_argument("Invalid input: " + input);
    }
    if (real_comp == INT_MIN || real_comp == INT_MAX || imag_comp == INT_MIN || imag_comp == INT_MAX) {
        throw std::overflow_error("GaussianInteger overflow");
    } else {
        return GaussianInteger(real_comp, imag_comp);
    }
}


