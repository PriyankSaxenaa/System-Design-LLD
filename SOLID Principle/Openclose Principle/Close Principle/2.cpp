#include<bits/stdc++.h>
using namespace std;
class Animal{
    public:
    string name="Pitaji";
    void sound(){
        cout<<"bhaoo bhaoo";
    }
    virtual void test(){
        cout<<"Testing";
    }
    Animal* findanimal(Animal* animal){
        cout<<"animal print";
        return animal;
    }
    protected:
    string name2="hello";
};
class Dog : public Animal{
    public:
    void printname(){
        cout<<name2;
    }
    Dog* findanimal(Dog* kutta){
        cout<<"Kuuta print";
        return kutta;
    }
    // void test() {
    //     cout<<"Kuutttaaa";
    // }
};
int main(){
    Animal* a=new Dog();
    Dog* b=new Dog();
    Animal* b2=a->findanimal(a);
    Dog* b3=b->findanimal(b);
    // a->sound();
    // cout<<endl;
    // a->test();
    // cout<<endl;
    // b->sound();
    // cout<<endl;
    // b->test();
    // cout<<endl;
    // cout<<b->name;
    // cout<<endl;
    // b->printname();
    
}