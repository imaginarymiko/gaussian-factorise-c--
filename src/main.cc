#include <iostream>
#include <random>
#include "gaussian-int.hh"

int getRandomInt(int min, int max) {
    // Returns a random integer in the range [min, max]
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(gen);
}

void printHelp() {
    std::cout << "Gaussian Integer Factoriser (C++)\n";
    std::cout << "Usage:\n";
    std::cout << "    ./gaussian-factorise\n";
    std::cout << "    ./gaussian-factorise <-h/-help/h/help>\n";
    std::cout << "    ./gaussian-factorise <-r/-random/r/random>\n";
    std::cout << "    ./gaussian-factorise [integer]\n";
    std::cout << "\n";
    std::cout << "If no argument is given, the program will prompt the user for an Gaussian integer.\n";
    std::cout << "If the provided Gaussian integer is \"random\" or \"r\", the program will generate a random integer.\n";
    std::cout << "Otherwise, the argument will be interpreted as an integer.\n";
    std::cout << "\n";
    std::cout << "The program will then factorise the integer into Gaussian primes.\n";
    std::cout << "\n";
    std::cout << "Also accepts j as the imaginary unit. a + bi and bi + a are both accepted forms.\n";
    std::cout << "\n";
    std::cout << "Examples:\n";
    std::cout << "    ./gaussian-factorise 2 \n";
    std::cout << "        Output: (-i)(1 + i)(1 + i)\n";
    std::cout << "    ./gaussian-factorise 7\n";
    std::cout << "        Output: (7)\n";
    std::cout << "    ./gaussian-factorise 425 - 470i\n";
    std::cout << "        Output: (-1)(1 + 2i)(2 + i)(94 + 85i)\n";
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    std::string arg;
    if (argc > 1) arg = argv[1];
    try {
        if (argc == 1) {
            while (true) {
                std::cout << "Enter a Gaussian integer: " << std::endl;
                std::string input;
                std::cin >> input;
                GaussianInteger g;
                if (input == "quit" || input == "q") {
                    break;
                } else if (input == "random" || input == "r") {
                    int real = getRandomInt(-1000, 1000);
                    int imag = getRandomInt(-1000, 1000);
                    g = GaussianInteger(real, imag);
                } else if (input == "help" || input == "h") {
                    printHelp();
                } else {
                    g = fromString(input);
                }
                std::cout << "Gaussian integer: " << g << std::endl;
                std::vector<GaussianInteger> factors = g.factorise();
                for (GaussianInteger& factor: factors) {
                    std::cout << ("(" + factor.toString() + ")");
                }
                std::cout << std::endl;
            }
        } else if (arg == "-random" || arg == "-r" || arg == "random" || arg == "r") {
            int real = getRandomInt(-1000, 1000);
            int imag = getRandomInt(-1000, 1000);
            GaussianInteger g = GaussianInteger(real, imag);
            std::cout << "Gaussian integer: " << g << std::endl;
            std::vector<GaussianInteger> factors = g.factorise();
            for (GaussianInteger& factor: factors) {
                std::cout << ("(" + factor.toString() + ")");
            }
            std::cout << std::endl;
        } else if (arg == "-help" || arg == "-h" || arg == "help" || arg == "h") {
            printHelp();
        } else {
            std::string input = "";
            for (int i = 1; i < argc; i++) {
                input += argv[i];
            }
            GaussianInteger g = fromString(input);
            std::cout << "Gaussian integer: " << g << std::endl;
            std::vector<GaussianInteger> factors = g.factorise();
            for (GaussianInteger& factor: factors) {
                std::cout << ("(" + factor.toString() + ")");
            }
            std::cout << std::endl;
        }
    } catch (std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 1;
    } catch (std::overflow_error& e) {
        std::cerr << "Overflow error: " << e.what() << std::endl;
        return 2;
    } catch (std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 3;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return -1;
    }
    return 0;
}
