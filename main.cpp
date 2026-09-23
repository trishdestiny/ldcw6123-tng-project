/**
 * LDCW6123 - Fundamentals of Digital Competence for Programmer
 * Group Project: Touch 'n Go Smart Transit & Financial Ecosystem Simulator
 * Leader / Maintainer: Member 1
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// User Account State Structure
struct TNGAccount {
    string cardID = "TNG-8829-NFC";
    double physicalCardBalance = 15.00;
    double eWalletBalance = 50.00;
    double goPlusBalance = 120.00;
    bool autoReloadEnabled = true;
};

// Function Prototypes for Team Allocation
void displayDashboard(const TNGAccount& user);
void processTransitPayment(TNGAccount& user);     // Assigned to Member 4
void processNfcReload(TNGAccount& user);          // Assigned to Member 4 & 5
void calculateGoPlusYield(const TNGAccount& user); // Assigned to Member 6
int getValidatedMenuChoice();                     // Assigned to Member 5

int main() {
    TNGAccount currentUser;
    int choice = 0;

    cout << "=========================================================\n";
    cout << "    LDCW6123: TOUCH 'N GO SMART CONSOLE ENGINE (v1.0)    \n";
    cout << "       Architecture Initiated by Group Project Lead      \n";
    cout << "=========================================================\n";

    do {
        displayDashboard(currentUser);
        cout << "\n[MAIN MENU]\n";
        cout << "1. Simulate Toll / Transit Gate (RFID / NFC Tap)\n";
        cout << "2. Reload Physical Card via eWallet (NFC Direct)\n";
        cout << "3. Calculate GO+ Micro-Yield Daily Returns\n";
        cout << "4. Exit Simulator\n";
        cout << "Select an option (1-4): ";

        choice = getValidatedMenuChoice();

        switch (choice) {
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
                cout << "\nThank you for using TNG Smart Console. Safe travels!\n";
                break;
            default:
                cout << "\n[!] Invalid selection. Please choose between 1 and 4.\n";
        }
    } while (choice != 4);

    return 0;
}

void displayDashboard(const TNGAccount& user) {
    cout << "\n------------------ ACCOUNT SUMMARY ------------------\n";
    cout << " Card ID            : " << user.cardID << "\n";
    cout << fixed << setprecision(2);
    cout << " Physical NFC Card  : RM " << user.physicalCardBalance << "\n";
    cout << " eWallet Balance    : RM " << user.eWalletBalance << "\n";
    cout << " GO+ Investment Bal : RM " << user.goPlusBalance << "\n";
    cout << " Auto-Reload Status : " << (user.autoReloadEnabled ? "ENABLED (Linked to GO+)" : "DISABLED") << "\n";
    cout << "-----------------------------------------------------\n";
}

// Starter fallback implementations (Members 4, 5, 6 will replace these in their branches)
void processTransitPayment(TNGAccount& user) {
    cout << "\n[INFO] Transit module placeholder - assigned to Member 4 (feature/fare-engine).\n";
}

void processNfcReload(TNGAccount& user) {
    cout << "\n[INFO] NFC Reload module placeholder - assigned to Member 5 (feature/validation-ux).\n";
}

void calculateGoPlusYield(const TNGAccount& user) {
    cout << "\n[INFO] GO+ Yield module placeholder - assigned to Member 6 (feature/micro-yield).\n";
}

int getValidatedMenuChoice() {
    int input;
    if (!(cin >> input)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return -1;
    }
    return input;
}