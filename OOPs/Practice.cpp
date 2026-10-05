#include <iostream>
using namespace std;

class Payment {
public:
    virtual void pay() {
        cout << "Generic payment\n";
    }

    virtual ~Payment() = default;
};

class UPI : public Payment {
public:
    void pay() override {
        cout << "Paying through UPI\n";
    }
};

class Card : public Payment {
public:
    void pay() override {
        cout << "Paying through Card\n";
    }
};

int main() {
    UPI upi;
    Card card;

    Payment* p = &upi;
    p->pay();  // Paying through UPI

    p = &card;
    p->pay();  // Paying through Card
}