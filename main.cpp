/**
 * MMU LDCW6123 - Fundamentals of Digital Competence for Programmer
 * Group Project: Touch 'n Go Smart Transit & Financial Ecosystem Simulator (v2.0)
 * 
 * Hey guys, this builds on our initial scaffold. We've got the transit deduction, 
 * NFC reload, and the GO+ micro-yield logic all plugged in with input validation.
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Quick struct to track the user's wallet states across cards and eWallet
struct TNGAccount {
    string cardID = "TNG-8829-NFC";
    double physicalCardBalance = 15.00; // Physical card balance
    double eWalletBalance = 45.00;      // eWallet app balance
    double goPlusBalance = 150.00;      // GO+ investment balance
    bool autoReloadLinked = true;       // Pull from GO+ if eWallet runs dry
};

// Prototypes for our main features
void displayDashboard(const TNGAccount& user);
void processTransitPayment(TNGAccount& user);
void processNfcReload(TNGAccount& user);
void calculateGoPlusYield(const TNGAccount& user);
int getValidatedInt(int minVal, int maxVal);
double getValidatedDouble(double minVal);

int main() {
    TNGAccount currentUser;
    int mainChoice = 0;

    cout << "=========================================================\n";
    cout << "    LDCW6123: TOUCH 'N GO SMART CONSOLE ENGINE (v2.0)    \n";
    cout << "=========================================================\n";

    // Main app loop - keeps running until the user decides to quit
    do {
        displayDashboard(currentUser);
        cout << "\n[MAIN MENU]\n";
        cout << "1. Simulate Toll / Rail Transit Gate (RFID / NFC Tap)\n";
        cout << "2. Reload Physical Card via eWallet (NFC Direct)\n";
        cout << "3. Calculate GO+ Daily Micro-Yield Returns\n";
        cout << "4. Exit Simulator\n";
        cout << "Select an option (1-4): ";

        mainChoice = getValidatedInt(1, 4);

        switch (mainChoice) {
            case 1:
                processTransitPayment(currentUser);
                break;
            case 2:
                processNfcReload(currentUser);
                break;
            case 3:
                calculateGoPlusYield(currentUser);
                break;
            case 4:
                cout << "\n[SYSTEM] Thanks for using the TNG Simulator. Safe travels!\n";
                break;
            default:
                cout << "\n[!] Invalid selection. Please pick between 1 and 4.\n";
        }
    } while (mainChoice != 4);

    return 0;
}

// Shows current balances across all accounts
void displayDashboard(const TNGAccount& user) {
    cout << "\n=================== CURRENT WALLET STATE ===================\n";
    cout << " Card Serial Number : " << user.cardID << "\n";
    cout << fixed << setprecision(2);
    cout << " 1. Physical NFC Card Balance : RM " << user.physicalCardBalance << "\n";
    cout << " 2. eWallet Available Balance : RM " << user.eWalletBalance << "\n";
    cout << " 3. GO+ Investment Principal  : RM " << user.goPlusBalance << "\n";
    cout << " Auto-Deduction / Reload Link : " 
         << (user.autoReloadLinked ? "ACTIVE (GO+ -> eWallet)" : "OFFLINE") << "\n";
    cout << "============================================================\n";
}

// Handles toll plaza and train station deductions
void processTransitPayment(TNGAccount& user) {
    cout << "\n--- TRANSIT & TOLL GATE SELECTION ---\n";
    cout << "1. Highway Express Toll (RFID / SmartTAG)\n";
    cout << "2. RapidKL LRT / MRT Gate (NFC Tap)\n";
    cout << "Select transit mode (1-2): ";
    
    int mode = getValidatedInt(1, 2);
    double fare = 0.0;
    string locationName = "";

    // Set prices depending on the highway or train route selected
    if (mode == 1) {
        cout << "\nSelect Highway Plaza:\n";
        cout << "1. MEX Highway (Putrajaya -> KL)       - RM 3.50\n";
        cout << "2. LDP Toll (Sunway -> Damansara)      - RM 2.10\n";
        cout << "3. PLUS Elite (Cyberjaya -> Shah Alam) - RM 4.80\n";
        cout << "Select toll plaza (1-3): ";
        int plaza = getValidatedInt(1, 3);
        
        switch (plaza) {
            case 1: fare = 3.50; locationName = "MEX Putrajaya Toll"; break;
            case 2: fare = 2.10; locationName = "LDP Sunway Plaza"; break;
            case 3: fare = 4.80; locationName = "PLUS Cyberjaya Toll"; break;
        }
    } else {
        cout << "\nSelect Rail Transit Distance:\n";
        cout << "1. Short Hop (1 - 3 stations)          - RM 1.60\n";
        cout << "2. Medium Commute (4 - 8 stations)     - RM 2.90\n";
        cout << "3. Cross-City Line (9+ stations)       - RM 4.20\n";
        cout << "Select commute distance (1-3): ";
        int commute = getValidatedInt(1, 3);

        switch (commute) {
            case 1: fare = 1.60; locationName = "LRT Short Hop"; break;
            case 2: fare = 2.90; locationName = "LRT Medium Commute"; break;
            case 3: fare = 4.20; locationName = "MRT Cross-City Line"; break;
        }
    }

    cout << "\nSelect Payment Channel:\n";
    cout << "1. Tap Physical NFC Card\n";
    cout << "2. eWallet Direct (PayDirect / RFID)\n";
    cout << "Choice (1-2): ";
    int channel = getValidatedInt(1, 2);

    cout << "\nProcessing deduction of RM " << fare << " at " << locationName << "...\n";

    if (channel == 1) {
        // Physical NFC card check
        if (user.physicalCardBalance >= fare) {
            user.physicalCardBalance -= fare;
            cout << ">>> [BARRIER OPEN - PROCEED] <<<\n";
            cout << "Paid using physical NFC card. Remaining balance: RM " << user.physicalCardBalance << "\n";
        } else {
            cout << ">>> [ACCESS DENIED - INSUFFICIENT BALANCE] <<<\n";
            cout << "[!] Card only has RM " << user.physicalCardBalance 
                 << ", but fare is RM " << fare << ".\n";
            cout << "Top up via Menu Option 2 first.\n";
        }
    } else {
        // eWallet flow with auto-deduct from GO+ if balance isn't enough
        if (user.eWalletBalance >= fare) {
            user.eWalletBalance -= fare;
            cout << ">>> [BARRIER OPEN - RFID DETECTED] <<<\n";
            cout << "Paid via eWallet PayDirect. Remaining: RM " << user.eWalletBalance << "\n";
        } else if (user.autoReloadLinked && (user.eWalletBalance + user.goPlusBalance >= fare)) {
            // Pull the remaining amount needed straight from GO+
            double deficit = fare - user.eWalletBalance;
            user.goPlusBalance -= deficit;
            user.eWalletBalance = 0.0;
            cout << ">>> [BARRIER OPEN - AUTO-RELOAD TRIGGERED] <<<\n";
            cout << "eWallet was short. Pulled RM " << deficit << " straight from GO+.\n";
            cout << "Updated eWallet: RM " << user.eWalletBalance 
                 << " | Updated GO+: RM " << user.goPlusBalance << "\n";
        } else {
            cout << ">>> [ACCESS DENIED - TRANSACTION FAILED] <<<\n";
            cout << "[!] Even with GO+ linked, you don't have enough funds for this trip.\n";
        }
    }
}

// Simulates tapping the card on the phone to transfer funds
void processNfcReload(TNGAccount& user) {
    cout << "\n--- NFC DIRECT PHYSICAL CARD RELOAD ---\n";
    cout << "Current Physical Card Balance : RM " << user.physicalCardBalance << "\n";
    cout << "Available eWallet Balance     : RM " << user.eWalletBalance << "\n";
    cout << "\nEnter amount to reload into Physical Card (RM): ";
    double reloadAmount = getValidatedDouble(1.00);

    if (user.eWalletBalance >= reloadAmount) {
        user.eWalletBalance -= reloadAmount;
        user.physicalCardBalance += reloadAmount;
        cout << "\n[OK] Hold your physical card against the back of your phone...\n";
        cout << "[OK] NFC write successful!\n";
        cout << "New Physical Card Balance : RM " << user.physicalCardBalance << "\n";
        cout << "New eWallet Balance       : RM " << user.eWalletBalance << "\n";
    } else {
        cout << "\n[!] Can't reload: You only have RM " << user.eWalletBalance 
             << " in your eWallet, which is less than RM " << reloadAmount << ".\n";
    }
}

// Simple compounding calculation for GO+ daily returns
void calculateGoPlusYield(const TNGAccount& user) {
    cout << "\n--- GO+ DAILY MICRO-YIELD EARNINGS CALCULATOR ---\n";
    cout << "Current GO+ Principal: RM " << user.goPlusBalance << "\n";
    cout << "Use current principal? (1 for Yes, 2 for Custom Amount): ";
    int choice = getValidatedInt(1, 2);

    double principal = user.goPlusBalance;
    if (choice == 2) {
        cout << "Enter custom investment principal (RM): ";
        principal = getValidatedDouble(10.00);
    }

    cout << "How many days do you want to project for? (e.g. 30, 90, 365): ";
    int days = getValidatedInt(1, 3650);

    const double annualRate = 0.0345; // Based on realistic ~3.45% p.a.
    double dailyRate = annualRate / 365.0;
    double totalInterest = 0.0;
    double runningPrincipal = principal;

    // Daily compounding loop
    for (int d = 1; d <= days; ++d) {
        double dayYield = runningPrincipal * dailyRate;
        totalInterest += dayYield;
        runningPrincipal += dayYield;
    }

    cout << fixed << setprecision(2);
    cout << "\n================= YIELD PROJECTION REPORT =================\n";
    cout << " Initial Investment     : RM " << principal << "\n";
    cout << " Daily Base Return Rate : 3.45% p.a. (" << setprecision(5) << (dailyRate * 100) << "% daily)\n";
    cout << setprecision(2);
    cout << " Investment Horizon     : " << days << " days\n";
    cout << " Total Interest Earned  : RM " << totalInterest << "\n";
    cout << " Final Projected Balance: RM " << runningPrincipal << "\n";
    cout << "===========================================================\n";
}

// Catches bad inputs so the terminal doesn't crash on letters/symbols
int getValidatedInt(int minVal, int maxVal) {
    int val;
    while (!(cin >> val) || val < minVal || val > maxVal) {
        cout << "[!] Oops, invalid choice. Please enter a number between " << minVal << " and " << maxVal << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return val;
}

double getValidatedDouble(double minVal) {
    double val;
    while (!(cin >> val) || val < minVal) {
        cout << "[!] Please enter a valid amount of at least RM " << fixed << setprecision(2) << minVal << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return val;
}