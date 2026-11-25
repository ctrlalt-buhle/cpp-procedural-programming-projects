# Procedural Programming in C++: Cafeteria Orders, Shopping Cart, Scores and Banking

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
![Tests](https://img.shields.io/badge/tests-21%20passing-brightgreen)
![Focus](https://img.shields.io/badge/Focus-Procedural%20Programming-blue)

Four console programs written in C++ that cover the core of procedural programming: variables and constants, decision-making, loops, arrays, functions, pass-by-reference, file handling and input validation.

## Academic context

This repository contains my project for the **Procedural Programming (ITPPA1)** module of the BSc Information Technology programme at **Eduvos** (NQF Level 5). It was an individual assessment worth 40% of the module mark. A summary of the brief is in [`docs/project_brief.md`](docs/project_brief.md).

The version here is a **cleaned-up and hardened version of my submission**: I kept the required structure and function signatures, and added robust input handling and automated tests (see [What I improved](#what-i-improved)).

## The programs

| # | Program | What it does | Source |
|---|---|---|---|
| 1 | **Cafeteria Order System** | Takes a customer's name and up to 8 menu items, totals the bill, gives a 10% discount above R100 and saves the bill to `CafeteriaBill.txt` | [`q1_cafeteria_order_system.cpp`](src/q1_cafeteria_order_system.cpp) |
| 2 | **Shopping Cart** | Items and quantities with a 5% discount above R200, saved to `ShoppingCartBill.txt`. Includes the design: [flowchart](docs/shopping_cart_flowchart.md) and [algorithm](docs/shopping_cart_algorithm.md) | [`q2_shopping_cart.cpp`](src/q2_shopping_cart.cpp) |
| 3 | **Student Scores** | Stores 5 scores in an array, then uses loops to find the average, highest and lowest and list the scores | [`q3_student_scores.cpp`](src/q3_student_scores.cpp) |
| 4 | **Bank Account Management System** | Menu-driven program to create an account, deposit, withdraw, check the balance and view the details, with the bank's rules enforced | [`q4_bank_account_system.cpp`](src/q4_bank_account_system.cpp) |

All four share [`input_utils.h`](src/input_utils.h), a small header of safe input functions.

## Sample run: Bank Account Management System (bad input handled)

```
--- Bank Account Management System ---
1. Create Account
2. Deposit Money
3. Withdraw Money
4. Check Balance
5. Display Account Details
6. Exit
Enter your choice (1-6): abc
Invalid input. Please enter a whole number between 1 and 6.
Enter your choice (1-6): 1
Enter your name: Sam
Enter your account number: 77
Enter your initial deposit (must be greater than 0): R0
Invalid input. Please enter a number greater than 0.
Enter your initial deposit (must be greater than 0): R250
Account created successfully!
...
Enter your choice (1-6): 3
Enter amount to withdraw: R900
Insufficient funds. Current balance: R250.00
```

More transcripts are in [`samples/`](samples/).

## Build and run

You need a C++17 compiler (g++, clang or Visual Studio).

**With g++ or clang (macOS, Linux, Windows with MinGW):**

```bash
make                       # builds all four programs into build/
./build/q1_cafeteria_order_system
./build/q4_bank_account_system
```

or compile one program directly:

```bash
g++ -std=c++17 -Wall -Wextra -o cafeteria src/q1_cafeteria_order_system.cpp
```

**With CMake (including Visual Studio's "Open Folder" mode):**

```bash
cmake -S . -B build
cmake --build build
```

**Run the tests** (needs Bash and g++):

```bash
make test        # or: bash tests/run_tests.sh
```

The tests feed scripted input to each program and check the output. They cover normal use, the discount boundaries (exactly R100 and R200 get no discount), invalid input and the bank rules.

## What I improved

| Area | Submitted version | This version |
|---|---|---|
| Invalid input | Typing a letter where a number was expected put `cin` into a failed state and could loop forever | Every number is read as a whole line and checked, and the program asks again |
| Names | `cin >> name` read only the first word | Full names accepted (`getline`) and blank names rejected |
| Money format | Q1 bill showed values like `R80` | Two decimals everywhere (`R80.00`) |
| Item and quantity checks | Q2 accepted zero or negative quantities | Quantity must be 1-99 and the y/n question accepts only y or n |
| Q2 design | Flowchart had no decisions or loop, and the algorithm assumed 5 items while the code used 8 | Flowchart with decision points and the retry loop, and an algorithm that matches the code |
| Bank system | Re-creating an account silently overwrote it; account number and amounts were not checked | Asks before replacing; positive amounts and account numbers enforced |
| Scores | No validation | Scores must be whole numbers from 0 to 100 |
| Quality | One copy of the checks per program | Shared `input_utils.h`, constants and small functions, warning-free build, automated tests |

## Concepts demonstrated

- Constants and data types, `const`, `static_cast`
- Selection (`if`, `switch`) and loops (`for`, `while`, `do-while`)
- Arrays, including parallel arrays for menu names and prices
- Functions, prototypes, pass-by-reference and `const` references
- File output with `ofstream` and error handling when a file cannot be opened
- Input validation, stream formatting (`<iomanip>`) and clean program exit
- Designing with a flowchart and an algorithm before coding
- Testing with a shell script

## Repository structure

```
.
├── src/                 # the four programs and the shared input helpers
├── docs/                # Q2 flowchart and algorithm, summary of the brief
├── samples/             # example program output
├── tests/run_tests.sh   # automated smoke tests
├── Makefile
├── CMakeLists.txt
└── LICENSE
```

## Author

**Buhle Malinga**, BSc IT (Data Science), Eduvos
Portfolio: [ctrlalt-buhle.github.io/portfolio](https://ctrlalt-buhle.github.io/portfolio/)

## Licence

The code is released under the MIT Licence (see [`LICENSE`](LICENSE)). The assessment brief belongs to Eduvos and is summarised, not reproduced, here.
