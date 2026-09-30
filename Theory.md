# Christensen Disruptive Innovation Theory Mapping

## Project
MMU LDCW6123 – Fundamentals of Digital Competence for Programmer

## System
Touch 'n Go Smart Transit & Financial Ecosystem Simulator (v2.0)

## Purpose

This document explains how the menu options, decision-making logic, and mathematical algorithms in `main.cpp` represent the evolution of Touch 'n Go using Clayton Christensen's Disruptive Innovation framework.

The simulator provides a simplified computational model of Touch 'n Go's development from transport payment services toward broader digital financial services.

---

## 1. Innovation Lifecycle Mapping

| Stage | Touch 'n Go Development | Simulator Representation | Innovation Interpretation |
|---|---|---|---|
| 1997 | Smart Card / Transit Payment | Menu 1 | Sustaining Innovation |
| 2017 | eWallet / Digital Payment | Menu 2 | Low-End Disruption Pathway |
| 2021 | GO+ / Financial Service | Menu 3 | New-Market Disruption Pathway |

The classifications above represent the project's analytical interpretation of Christensen's framework.

---

## 2. Menu 1 – Transit and Toll Payment

The first menu option calls:

```cpp
case 1:
    processTransitPayment(currentUser);
    break;

The function is:

void processTransitPayment(TNGAccount& user)

This module simulates Touch 'n Go's transport-payment function.

Users can select:

Highway Express Toll
RapidKL LRT / MRT
Commercial Mall Parking

The program then calculates or selects the appropriate fare.

Innovation Theory Mapping

This represents an established market and an existing customer need: making transport and toll payments easier and faster.

Within this project's analysis, this stage is treated as a Sustaining Innovation because it improves an existing payment activity rather than creating a completely new financial market.

3. Menu 2 – NFC Physical Card Reload

The second menu option calls:

case 2:
    processNfcReload(currentUser);
    break;

The function is:

void processNfcReload(TNGAccount& user)

This module connects the physical card with the digital eWallet balance.

The program accepts a reload amount:

double reloadAmount = getValidatedDouble(1.00);

It then checks whether enough money exists in the eWallet:

if (user.eWalletBalance >= reloadAmount)

If sufficient funds are available, the program performs the transfer:

user.eWalletBalance -= reloadAmount;
user.physicalCardBalance += reloadAmount;
Innovation Theory Mapping

Within this project's analysis, the eWallet/NFC pathway is associated with a Low-End Disruption Pathway because it provides a simpler and more accessible digital payment mechanism for everyday users and smaller transactions.

The program demonstrates the connection:

eWallet → Physical Card → NFC Payment

This reduces the need for a separate manual top-up process by allowing the digital wallet to reload the physical card.

4. Menu 3 – GO+ Daily Micro-Yield Calculator

The third menu option calls:

case 3:
    calculateGoPlusYield(currentUser);
    break;

The function is:

void calculateGoPlusYield(const TNGAccount& user)

This module represents the financial-service expansion of the Touch 'n Go ecosystem.

The user can either use the existing GO+ balance or enter a custom investment principal:

double principal = user.goPlusBalance;

if (choice == 2) {
    principal = getValidatedDouble(10.00);
}
Innovation Theory Mapping

Within this project's analysis, this module represents a New-Market Disruption Pathway.

The system moves beyond the original transport-payment purpose and models access to an investment-related financial service.

The conceptual transition is:

Transport Payment
        ↓
Digital Wallet
        ↓
Financial Service

This represents expansion into a new customer use case rather than only improving the original transport-payment function.

5. GO+ Mathematical Model

The simulator uses a simplified daily compounding calculation.

The annual rate is represented in the program as:

const double annualRate = 0.0345;

The daily rate is calculated using:

double dailyRate = annualRate / 365.0;

For every day, the program calculates:

double dayYield = runningPrincipal * dailyRate;

The principal is then updated:

runningPrincipal += dayYield;

The calculation is repeated using a for loop:

for (int d = 1; d <= days; ++d)

The simplified mathematical model is:

Daily Yield = Current Principal × Daily Rate

New Principal = Current Principal + Daily Yield

The calculation demonstrates how the simulator models financial growth over time.

The rate and calculation are used only as a simplified educational model and should not be interpreted as a prediction of actual GO+ returns.

6. Transit Fare Decision Logic

Menu 1 uses conditional logic to determine the selected transport service.

if (mode == 1)

represents highway toll payment.

else if (mode == 2)

represents rail transit.

else if (mode == 3)

represents commercial parking.

The program also uses switch statements to select specific locations and prices.

Example:

switch (plaza) {
    case 1: fare = 3.50; locationName = "MEX Putrajaya Toll"; break;
    case 2: fare = 2.10; locationName = "LDP Sunway Plaza"; break;
    case 3: fare = 4.80; locationName = "PLUS Cyberjaya Toll"; break;
}

This demonstrates different service pathways within the same digital system.

7. Payment Channel Logic

After calculating the fare, the user selects a payment channel:

1. Tap Physical NFC Card
2. eWallet Direct

For the physical card, the program checks:

if (user.physicalCardBalance >= fare)

If sufficient funds exist, the fare is deducted:

user.physicalCardBalance -= fare;

For the eWallet, the program checks:

if (user.eWalletBalance >= fare)

and deducts the fare from the eWallet.

This demonstrates the movement between physical and digital payment channels within the same ecosystem.

8. GO+ Auto-Reload Logic

The simulator also contains an integration path between GO+ and the eWallet.

The program checks:

else if (user.autoReloadLinked && 
         (user.eWalletBalance + user.goPlusBalance >= fare))

It calculates the amount needed:

double deficit = fare - user.eWalletBalance;

Then the required amount is deducted from GO+:

user.goPlusBalance -= deficit;

The eWallet is then updated:

user.eWalletBalance = 0.0;

Conceptually:

GO+ → eWallet → Payment

This demonstrates how different services can be integrated into one digital ecosystem.

9. Input Validation

The simulator contains two validation functions:

int getValidatedInt(int minVal, int maxVal);

and:

double getValidatedDouble(double minVal);

The integer validation uses:

while (!(cin >> val) || val < minVal || val > maxVal)

This prevents invalid menu selections from entering the system.

For example, the main menu accepts values from 1 to 4:

mainChoice = getValidatedInt(1, 4);

This ensures that user input follows a defined system pathway.

10. Main Algorithmic Flow

The overall simulator follows this structure:

START
  ↓
Display Wallet Dashboard
  ↓
Display Main Menu
  ↓
User Selects Option
  ↓
 ┌───────────────┬────────────────┬──────────────────┐
 │               │                │                  │
Menu 1         Menu 2           Menu 3             Menu 4
 │               │                │                  │
Transit         NFC Reload       GO+ Yield           Exit
Payment         Physical Card    Calculation          │
 │               │                │                  │
Fare Logic      Balance Check    Daily Formula       END
 │               │                │
Payment         Transfer         Yield Projection
 │               │                │
 └───────────────┴────────────────┘
                 ↓
          Return to Main Menu

The simulator remains active using the do-while loop:

do {
    ...
} while (mainChoice != 4);

This allows users to access multiple services before exiting.

11. Christensen Theory Mapping Summary

The simulator maps the innovation lifecycle to the following conceptual progression:

Existing Transport Service
          ↓
Sustaining Innovation
          ↓
Digital Payment / eWallet
          ↓
Low-End Disruption Pathway
          ↓
Financial Service / GO+
          ↓
New-Market Disruption Pathway

The S-curve shown in the project poster is a conceptual representation of this progression.

The curves are illustrative and are not based on quantitative performance measurements.

12. Conclusion

The main.cpp simulator provides a simplified technical representation of Touch 'n Go's evolution from transport payment technology toward a broader digital financial ecosystem.

Menu 1 represents the established transport-payment service.

Menu 2 represents the integration of physical and digital payment.

Menu 3 represents expansion into an investment-related financial service.

The use of conditional statements, switch statements, loops, balance calculations, and daily yield formulas provides the algorithmic structure required to simulate these different stages.

Overall, the program connects the technical implementation with the Christensen innovation framework used in the project's A3 poster.

```bash
git checkout -b docs/christensen-theory
git add THEORY.md
git commit -m "docs: map simulator modules to Christensen disruption theory"
git push -u origin docs/christensen-theory
