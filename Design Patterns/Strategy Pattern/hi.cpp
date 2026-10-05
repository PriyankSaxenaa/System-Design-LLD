#include <iostream>
using namespace std;

// Strategy
class PaymentStrategy {
public:
    virtual void pay() = 0;
    virtual ~PaymentStrategy() {}
};

// Concrete Strategy 1
class CreditCard : public PaymentStrategy {
public:
    void pay() override {
        cout << "Paid using Credit Card\n";
    }
};

// Concrete Strategy 2
class UPI : public PaymentStrategy {
public:
    void pay() override {
        cout << "Paid using UPI\n";
    }
};

// Context
class Payment {
    PaymentStrategy* strategy;

public:
    Payment(PaymentStrategy* s) {
        strategy = s;
    }

    void makePayment() {
        strategy->pay();
    }
};

int main() {

    Payment p1(new CreditCard());
    p1.makePayment();

    Payment p2(new UPI());
    p2.makePayment();

    return 0;
}