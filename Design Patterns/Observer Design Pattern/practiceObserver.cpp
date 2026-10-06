#include<bits/stdc++.h>
using namespace std;
class observer{
    public:
    virtual void notify()=0;
};
class user : public observer{
    private:
    string name;
    public:
    user(string name){
        this->name=name;
    }
    void notify() override{
        cout<<this->name<<" user has been notified";
    }
};
class Youtubechannel{
    private:
    vector<observer*> observers;
    public:
    void subscribe(observer* a){
        observers.push_back(a);
    }
    void notify(){
        cout<<"New update\n";
        for(int i=0;i<observers.size();i++){
            observers[i]->notify();
            cout<<endl;
        }
    }
};
int main(){
    user* us1 =new user("ram");
    user* us2 =new user("shyam");
    user* us3 =new user("dhanram");

    Youtubechannel* priyank=new Youtubechannel();
    priyank->subscribe(us2);
    priyank->subscribe(us3);

    priyank->notify();
}