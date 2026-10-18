#include <iostream>
using namespace std;

// Component
class Coffee {
public:
    virtual int cost() = 0;
    virtual ~Coffee() {}
};

// Concrete Component
class SimpleCoffee : public Coffee {
public:
    int cost() override {
        return 50;
    }
};

// Base Decorator
class CoffeeDecorator : public Coffee {
protected:
    Coffee* coffee;

public:
    CoffeeDecorator(Coffee* coffee) {
        this->coffee = coffee;
    }
};

// Concrete Decorator
class Milk : public CoffeeDecorator {
public:
    Milk(Coffee* coffee) : CoffeeDecorator(coffee) {}

    int cost() override {
        return coffee->cost() + 20;
    }
};

class Sugar : public CoffeeDecorator {
public:
    Sugar(Coffee* coffee) : CoffeeDecorator(coffee) {}

    int cost() override {
        return coffee->cost() + 10;
    }
};

int main() {
    Coffee* coffee = new SimpleCoffee();

    coffee = new Milk(coffee);
    coffee = new Sugar(coffee);

    cout << coffee->cost() << endl;  // 80
}