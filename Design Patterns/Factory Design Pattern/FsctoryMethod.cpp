#include <iostream>
using namespace std;

/*
=========================================================
                FACTORY METHOD PATTERN
=========================================================


                    <<abstract>>
                       Burger
                    -------------
                    + prepare()
                         △
                         │
          ┌──────────────┼──────────────┐
          │              │              │
          │              │              │
   BasicBurger    StandardBurger   BasicWheatBurger
   ------------   --------------   ----------------
   + prepare()    + prepare()      + prepare()
          │              │              │
          │              │              │
          │              │              │
          │              │       StandardWheatBurger
          │              │       --------------------
          │              │       + prepare()
          │              │
          │              │
          └──────────────┘


                    <<abstract>>
                   BurgerFactory
                  ----------------
                  + createBurger()
                         △
                         │
              ┌──────────┴──────────┐
              │                     │
              │                     │
        SinghBurger             KingBurger
        ------------             ----------
        + createBurger()         + createBurger()
              │                     │
              │ creates             │ creates
              ▼                     ▼
        ┌──────────────┐      ┌────────────────────┐
        │ BasicBurger  │      │ BasicWheatBurger   │
        │ StandardBurger│     │ StandardWheatBurger│
        └──────────────┘      └────────────────────┘


Relationship:

SinghBurger ─────creates─────> BasicBurger
SinghBurger ─────creates─────> StandardBurger

KingBurger ──────creates─────> BasicWheatBurger
KingBurger ──────creates─────> StandardWheatBurger

=========================================================
*/


// ================= PRODUCT =================

class Burger {
public:
    virtual void prepare() = 0;

    virtual ~Burger() {}
};


// ================= SINGH BURGER PRODUCTS =================

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Burger\n";
    }
};

class StandardBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Burger\n";
    }
};


// ================= KING BURGER PRODUCTS =================

class BasicWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Wheat Burger\n";
    }
};

class StandardWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Wheat Burger\n";
    }
};


// ================= FACTORY =================

class BurgerFactory {
public:
    virtual Burger* createBurger(string type) = 0;

    virtual ~BurgerFactory() {}
};


// ================= SINGH FACTORY =================

class SinghBurger : public BurgerFactory {
public:

    Burger* createBurger(string type) override {

        if (type == "basic")
            return new BasicBurger();

        if (type == "standard")
            return new StandardBurger();

        return nullptr;
    }
};


// ================= KING FACTORY =================

class KingBurger : public BurgerFactory {
public:

    Burger* createBurger(string type) override {

        if (type == "basic")
            return new BasicWheatBurger();

        if (type == "standard")
            return new StandardWheatBurger();

        return nullptr;
    }
};


// ================= CLIENT =================

int main() {

    string type = "basic";

    // Client chooses factory
    BurgerFactory* factory = new SinghBurger();

    // Factory creates the required product
    Burger* burger = factory->createBurger(type);

    // Runtime polymorphism
    if (burger)
        burger->prepare();

    delete burger;
    delete factory;

    return 0;
}