#include <iostream>
#include <random>
#include "gaussian-int.h"

using namespace std;

int getRandomInt(int min, int max) {
    // Returns a random integer in the range [min, max]
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(gen);
}

void printHelp() {
    cout << "Gaussian Integer Factoriser (C++)\n";
    cout << "Usage:\n";
    cout << "    ./gaussian-factorise\n";
    cout << "    ./gaussian-factorise <-h/-help/h/help>\n";
    cout << "    ./gaussian-factorise <-r/-random/r/random>\n";
    cout << "    ./gaussian-factorise [integer]\n";
    cout << "\n";
    cout << "If no argument is given, the program will prompt the user for an Gaussian integer.\n";
    cout << "If the provided Gaussian integer is \"random\" or \"r\", the program will generate a random integer.\n";
    cout << "Otherwise, the argument will be interpreted as an integer.\n";
    cout << "\n";
    cout << "The program will then factorise the integer into Gaussian primes.\n";
    cout << "\n";
    cout << "Also accepts j as the imaginary unit. a + bi and bi + a are both accepted forms.\n";
    cout << "\n";
    cout << "Examples:\n";
    cout << "    ./gaussian-factorise 2 \n";
    cout << "        Output: (-i)(1 + i)(1 + i)\n";
    cout << "    ./gaussian-factorise 7\n";
    cout << "        Output: (7)\n";
    cout << "    ./gaussian-factorise 425 - 470i\n";
    cout << "        Output: (-1)(1 + 2i)(2 + i)(94 + 85i)\n";
    cout << endl;
}

int main(int argc, char** argv) {
    string arg;
    if (argc > 1) arg = argv[1];
    try {
        if (argc == 1) {
            while (true) {
                cout << "Enter a Gaussian integer: " << endl;
                string input;
                cin >> input;
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
                cout << "Gaussian integer: " << g << endl;
                vector<GaussianInteger> factors = g.factorise();
                for (GaussianInteger factor: factors) {
                    cout << ("(" + factor.toString() + ")");
                }
                cout << endl;
            }
        } else if (arg == "-random" || arg == "-r" || arg == "random" || arg == "r") {
            int real = getRandomInt(-1000, 1000);
            int imag = getRandomInt(-1000, 1000);
            GaussianInteger g = GaussianInteger(real, imag);
            cout << "Gaussian integer: " << g << endl;
            vector<GaussianInteger> factors = g.factorise();
            for (GaussianInteger factor: factors) {
                cout << ("(" + factor.toString() + ")");
            }
            cout << endl;
        } else if (arg == "-help" || arg == "-h" || arg == "help" || arg == "h") {
            printHelp();
        } else {
            string input = "";
            for (int i = 1; i < argc; i++) {
                input += argv[i];
            }
            GaussianInteger g = fromString(input);
            cout << "Gaussian integer: " << g << endl;
            vector<GaussianInteger> factors = g.factorise();
            for (GaussianInteger factor: factors) {
                cout << ("(" + factor.toString() + ")");
            }
            cout << endl;
        }
    } catch (std::invalid_argument& e) {
        cerr << "Invalid argument: " << e.what() << endl;
        return 1;
    } catch (std::overflow_error& e) {
        cerr << "Overflow error: " << e.what() << endl;
        return 1;
    } catch (std::runtime_error& e) {
        cerr << "Runtime error: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Unknown error" << endl;
        return 1;
    }
    return 0;
}
