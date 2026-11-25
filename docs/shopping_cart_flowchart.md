# Question 2.1: Shopping Cart flowchart

The diagram below shows the logic implemented in [`src/q2_shopping_cart.cpp`](../src/q2_shopping_cart.cpp). Rounded boxes are the start and end, parallelograms are input and output, rectangles are processing steps, and diamonds are decisions. GitHub draws it automatically.

```mermaid
flowchart TD
    A(["Start"]) --> B[/"Input customer name"/]
    B --> C[/"Display menu of 8 items with prices"/]
    C --> D["totalCost = 0"]
    D --> E[/"Input item number"/]
    E --> F{"Item number between 1 and 8?"}
    F -- "No" --> G[/"Display error message"/]
    G --> E
    F -- "Yes" --> H[/"Input quantity"/]
    H --> I{"Quantity between 1 and 99?"}
    I -- "No" --> J[/"Display error message"/]
    J --> H
    I -- "Yes" --> K["totalCost = totalCost + price x quantity"]
    K --> L[/"Ask: add another item? y or n"/]
    L --> M{"Answer is y?"}
    M -- "Yes" --> E
    M -- "No" --> N{"totalCost > R200?"}
    N -- "Yes" --> O["discount = totalCost x 0.05"]
    N -- "No" --> P["discount = 0"]
    O --> Q["finalTotal = totalCost - discount"]
    P --> Q
    Q --> R[/"Display total, discount and final total"/]
    R --> S["Open ShoppingCartBill.txt"]
    S --> T{"File opened?"}
    T -- "Yes" --> U["Write bill to file and close it"]
    U --> V[/"Display success message"/]
    T -- "No" --> W[/"Display error message"/]
    V --> X(["End"])
    W --> X
```
