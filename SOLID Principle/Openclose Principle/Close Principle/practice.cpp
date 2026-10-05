#include<bits/stdc++.h>
using namespace std;
class PaymentMethod {
public:
    virtual void pay() {
        cout<<"fixed abstract class";
    };
    virtual ~PaymentMethod() = default;
};

class UPI : public PaymentMethod {
public:
    void pay() override {
        cout << "Paying via UPI\n";
    }
};

class Card : public PaymentMethod {
public:
    void pay() override {
        cout << "Paying via Card\n";
    }
};

class NetBanking : public PaymentMethod {
public:
    void pay() override {
        cout << "Paying via Net Banking\n";
    }
};

int main(){
    PaymentMethod* p=new UPI();
    p->pay();
}