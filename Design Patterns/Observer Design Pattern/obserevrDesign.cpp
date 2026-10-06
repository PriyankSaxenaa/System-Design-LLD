#include <iostream>
#include <vector>
using namespace std;

// Observer
class Observer {
public:
    virtual void update() = 0;
};

// Concrete Observer
class User : public Observer {
private:
    string name;

public:
    User(string name) {
        this->name = name;
    }

    void update() override {
        cout << name << " got notification!" << endl;
    }
};

// Subject
class YouTubeChannel {
private:
    vector<Observer*> observers;

public:
    void subscribe(Observer* observer) {
        observers.push_back(observer);
    }

    void uploadVideo() {
        cout << "New video uploaded!\n";

        for (Observer* observer : observers) {
            observer->update();
        }
    }
};

int main() {
    YouTubeChannel channel;

    User u1("Priyank");
    User u2("Rahul");

    channel.subscribe(&u1);
    channel.subscribe(&u2);

    channel.uploadVideo();
}