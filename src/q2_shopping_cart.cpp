// ----------------------------------------------------------------------------
// Question 2: Shopping Cart Program
// Implements the flowchart and algorithm in docs/. The customer chooses items
// and quantities, a 5% discount applies when the total exceeds R200, and the
// final bill is saved to a text file.
// ----------------------------------------------------------------------------
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "input_utils.h"

using namespace std;

// ---- Constants ----------------------------------------------------------------
const int NUM_ITEMS = 8;
const string ITEM_NAMES[NUM_ITEMS] = {"Coffee", "Sandwich", "Salad", "Juice",
                                      "Muffin", "Pizza Slice", "Soup", "Burger"};
const double ITEM_PRICES[NUM_ITEMS] = {15.00, 30.00, 25.00, 10.00, 20.00, 35.00, 18.00, 40.00};

const double DISCOUNT_RATE      = 0.05;    // 5% discount
const double DISCOUNT_THRESHOLD = 200.00;  // applies if the total EXCEEDS R200
const int MAX_QUANTITY          = 99;
const string BILL_FILE          = "ShoppingCartBill.txt";

// ---- Function prototypes -----------------------------------------------------
void displayMenu();
void printBill(ostream& out, const string& customerName, const int quantities[],
               double total, double discount, double finalTotal);

int main() {
    cout << "Welcome to the Online Shopping Cart System\n";
    const string customerName = input::readNonEmpty("Please enter your name: ");

    displayMenu();

    int quantities[NUM_ITEMS] = {0};  // how many of each item is in the cart
    double totalCost = 0.0;

    // Keep adding items until the customer says no
    bool addMore = true;
    while (addMore) {
        const int choice = input::readInt("\nSelect an item by number (1-8): ", 1, NUM_ITEMS);
        const int quantity = input::readInt("Enter the quantity: ", 1, MAX_QUANTITY);

        quantities[choice - 1] += quantity;
        totalCost += ITEM_PRICES[choice - 1] * quantity;

        addMore = input::readYesNo("Would you like to add another item? (y/n): ");
    }

    // Discount decision
    const double discount = (totalCost > DISCOUNT_THRESHOLD) ? totalCost * DISCOUNT_RATE : 0.0;
    const double finalTotal = totalCost - discount;

    // Show the bill on screen
    cout << "\n";
    printBill(cout, customerName, quantities, totalCost, discount, finalTotal);

    // Write the bill to a file
    ofstream outFile(BILL_FILE);
    if (outFile.is_open()) {
        printBill(outFile, customerName, quantities, totalCost, discount, finalTotal);
        outFile.close();
        cout << "\nThe bill has been successfully written to " << BILL_FILE << "\n";
    } else {
        cout << "\nError: could not open " << BILL_FILE << " to save the bill.\n";
        return 1;
    }
    return 0;
}

void displayMenu() {
    cout << "\nMenu:\n" << fixed << setprecision(2);
    for (int i = 0; i < NUM_ITEMS; i++) {
        cout << (i + 1) << ". " << ITEM_NAMES[i] << " - R" << ITEM_PRICES[i] << "\n";
    }
}

// Prints the bill to any output stream, so the same code writes to the screen and to the file.
void printBill(ostream& out, const string& customerName, const int quantities[],
               double total, double discount, double finalTotal) {
    out << fixed << setprecision(2);
    out << "Customer Name: " << customerName << "\n";
    out << "Items:\n";
    for (int i = 0; i < NUM_ITEMS; i++) {
        if (quantities[i] > 0) {
            out << "  " << quantities[i] << " x " << ITEM_NAMES[i] << " @ R" << ITEM_PRICES[i]
                << " = R" << quantities[i] * ITEM_PRICES[i] << "\n";
        }
    }
    out << "Total Cost: R" << total << "\n";
    out << "Discount: R" << discount << "\n";
    out << "Final Total after Discount: R" << finalTotal << "\n";
}
