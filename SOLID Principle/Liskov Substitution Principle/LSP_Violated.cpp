#include <iostream>
using namespace std;

class Bird {
public:
    virtual void fly() {
        cout << "Bird is flying\n";
    }
};

class Sparrow : public Bird {
};

class Penguin : public Bird {
public:
    void fly() override {
        cout << "Penguin cannot fly!\n";
    }
};

int main() {
    Bird* b = new Penguin();
    b->fly();  // Unexpected behavior   //in short there is a property of bird that they can fly but penguine cant so liskov states it should inherit all property of parent
}