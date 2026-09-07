#include <iostream>
using namespace std;

// Inheritance: each concrete payment type IS-A Payment and must implement pay()
class UpiPayment : public Payment {
public:
    bool pay(double amt) override {
        amount = amt;
        char confirm;
        cout << "  [UPI] Confirm payment of Rs." << amount << "? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            cout << "  [UPI] Rs." << amount << " paid successfully\n";
            return true;
        }
        cout << "  [UPI] Payment failed\n";
        return false;
    }
};

class CardPayment : public Payment {
public:
    bool pay(double amt) override {
        amount = amt;
        char confirm;
        cout << "  [Card] Confirm payment of Rs." << amount << "? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            cout << "  [Card] Rs." << amount << " paid successfully\n";
            return true;
        }
        cout << "  [Card] Payment failed\n";
        return false;
    }
};

class CashPayment : public Payment {
public:
    bool pay(double amt) override {
        amount = amt;
        char confirm;
        cout << "  [Cash] Confirm payment of Rs." << amount << "? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            cout << "  [Cash] Rs." << amount << " paid successfully\n";
            return true;
        }
        cout << "  [Cash] Payment failed\n";
        return false;
    }
};
