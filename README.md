Gaussian Integer Factoriser (C++)

Usage:
    ./gaussian-factorise
    ./gaussian-factorise -help
    ./gaussian-factorise -h
    ./gaussian-factorise help
    ./gaussian-factorise h
    ./gaussian-factorise [integer]
    ./gaussian-factorise -random
    ./gaussian-factorise -r
    ./gaussian-factorise random
    ./gaussian-factorise r

    If no argument is given, the program will prompt the user for an Gaussian integer.
    If the provided Gaussian integer is "random" or "r", the program will generate a random integer.
    Otherwise, the argument will be interpreted as an integer.

    The program will then factorise the integer into Gaussian primes.

    Also accepts j as the imaginary unit. a + bi and bi + a are both accepted forms.

    Examples:
        ./gaussian-factorise 2 
            Output: (-i)(1 + i)(1 + i)
        ./gaussian-factorise 7
            Output: (7)
        ./gaussian-factorise 425 - 470i
            Output: (-1)(1 + 2i)(2 + i)(94 + 85i)
