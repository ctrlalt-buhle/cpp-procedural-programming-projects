// ----------------------------------------------------------------------------
// Question 1: Cafeteria Order System
// Calculates a customer's cafeteria bill, applies a 10% discount when the total
// exceeds R100, and writes the customer's details and final bill to a file.
// ----------------------------------------------------------------------------
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "input_utils.h"

using namespace std;

// ---- Constants ----------------------------------------------------------------
const double COFFEE_PRICE   = 15.00;
const double SANDWICH_PRICE = 30.00;
const double SALAD_PRICE    = 25.00;
const double JUICE_PRICE    = 10.00;
const double MUFFIN_PRICE   = 20.00;
const double PIZZA_PRICE    = 35.00;
const double SOUP_PRICE     = 18.00;
const double BURGER_PRICE   = 40.00;

const double DISCOUNT_RATE      = 0.10;    // 10% discount
const double DISCOUNT_THRESHOLD = 100.00;  // discount applies if the bill EXCEEDS R100

const int MENU_SIZE = 8;
const int MAX_ITEMS = 8;
const string MENU_NAMES[MENU_SIZE] = {"Coffee", "Sandwich", "Salad", "Juice",
                                      "Muffin", "Pizza Slice", "Soup", "Burger"};
const double MENU_PRICES[MENU_SIZE] = {COFFEE_PRICE, SANDWICH_PRICE, SALAD_PRICE, JUICE_PRICE,
                                       MUFFIN_PRICE, PIZZA_PRICE, SOUP_PRICE, BURGER_PRICE};
const string BILL_FILE = "CafeteriaBill.txt";

// ---- Function prototypes -----------------------------------------------------
void displayMenu();
double calculateTotal(int numberOfItems);
double calculateDiscount(double total);
bool writeBillToFile(const string& name, const string& surname, double finalBill);

int main() {
    // 1. Customer details
    const string name = input::readNonEmpty("Enter your name: ");
    const string surname = input::readNonEmpty("Enter your surname: ");

    // 2. How many items (the menu has 8 items; the customer may order up to 8)
    const int numberOfItems =
        input::readInt("How many items would you like to order (up to 8)? ", 1, MAX_ITEMS);

    // 3. Menu and selections
    displayMenu();
    const double totalBill = calculateTotal(numberOfItems);

    // 4. Discount
    const double discount = calculateDiscount(totalBill);
    const double finalBill = totalBill - discount;

    // 5. Show the bill
    cout << fixed << setprecision(2);
    cout << "Total Bill: R" << totalBill << endl;
    if (discount > 0.0) {
        cout << "Discount applied (" << static_cast<int>(DISCOUNT_RATE * 100) << "%): R" << discount << endl;
    } else {
        cout << "No discount applied." << endl;
    }
    cout << "Final Bill: R" << finalBill << endl;

    // 6. Save the bill and report success or failure
    if (writeBillToFile(name, surname, finalBill)) {
        cout << "The bill has been written to " << BILL_FILE << "." << endl;
    } else {
        cout << "Error: could not open " << BILL_FILE << " to write the bill." << endl;
        return 1;
    }
    return 0;
}

// Print the numbered menu with prices.
void displayMenu() {
    cout << "\nCafeteria Menu:\n" << fixed << setprecision(2);
    for (int i = 0; i < MENU_SIZE; i++) {
        cout << (i + 1) << ". " << MENU_NAMES[i] << " - R" << MENU_PRICES[i] << "\n";
    }
}

// Ask for each item (validated as 1-8) and add up the prices.
double calculateTotal(int numberOfItems) {
    double total = 0.0;
    for (int i = 1; i <= numberOfItems; i++) {
        const int choice =
            input::readInt("Select item " + to_string(i) + " (1-8): ", 1, MENU_SIZE);
        total += MENU_PRICES[choice - 1];
    }
    return total;
}

// 10% discount only when the total is MORE than R100 (exactly R100 gets none).
double calculateDiscount(double total) {
    return (total > DISCOUNT_THRESHOLD) ? total * DISCOUNT_RATE : 0.0;
}

// Write the customer's name, surname and final bill. Returns false if the file cannot be opened.
bool writeBillToFile(const string& name, const string& surname, double finalBill) {
    ofstream outFile(BILL_FILE);
    if (!outFile.is_open()) return false;
    outFile << fixed << setprecision(2);
    outFile << "Customer: " << name << " " << surname << "\n";
    outFile << "Final Bill: R" << finalBill << "\n";
    outFile.close();
    return true;
}
