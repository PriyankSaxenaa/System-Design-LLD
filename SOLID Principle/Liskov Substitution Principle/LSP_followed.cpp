#include <iostream>
using namespace std;

class Bird {
public:
    virtual void eat() {
        cout << "Bird is eating\n";
    }
};

class Sparrow : public Bird {
};

class Penguin : public Bird {
};

int main() {
    Bird* b1 = new Sparrow();
    Bird* b2 = new Penguin();

    b1->eat();
    b2->eat();
}