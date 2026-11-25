# Question 2.2: Shopping Cart algorithm

Matches the flowchart in [`shopping_cart_flowchart.md`](shopping_cart_flowchart.md) and the program in [`src/q2_shopping_cart.cpp`](../src/q2_shopping_cart.cpp).

## Constants and variables

- `ITEM_NAMES[8]` and `ITEM_PRICES[8]`: the store's predefined items and their prices (Coffee R15, Sandwich R30, Salad R25, Juice R10, Muffin R20, Pizza Slice R35, Soup R18, Burger R40).
- `DISCOUNT_RATE = 0.05` and `DISCOUNT_THRESHOLD = 200.00`.
- `customerName` (text), `quantities[8]` (how many of each item is in the cart, all starting at 0), `totalCost = 0`, `discount`, `finalTotal`.

## Steps

1. **Start.**
2. **Prompt for the customer's name.** Display "Please enter your name:" and read `customerName`. Repeat while the name is blank.
3. **Display the menu.** Show each item number, name and price.
4. **Select items** (repeat until the customer chooses to stop):
   1. Prompt for an item number. If it is not a whole number from 1 to 8, display an error and ask again.
   2. Prompt for a quantity. If it is not a whole number from 1 to 99, display an error and ask again.
   3. Add the quantity to `quantities[item - 1]`.
   4. Calculate `itemCost = ITEM_PRICES[item - 1] x quantity` and set `totalCost = totalCost + itemCost`.
   5. Ask "Would you like to add another item? (y/n)". Accept only y or n. If the answer is y, go back to 4.1.
5. **Calculate the discount.**
   - If `totalCost > DISCOUNT_THRESHOLD`, then `discount = totalCost x DISCOUNT_RATE`.
   - Otherwise `discount = 0`.
6. **Calculate the final total:** `finalTotal = totalCost - discount`.
7. **Display the bill:** customer name, each item bought with quantity and cost, total cost, discount and final total, with two decimal places.
8. **Write the bill to a text file.**
   1. Open `ShoppingCartBill.txt` for writing.
   2. If the file opened: write the same bill to the file, close the file, and display "The bill has been successfully written to ShoppingCartBill.txt".
   3. Otherwise: display "Error: could not open ShoppingCartBill.txt to save the bill."
9. **End.**
