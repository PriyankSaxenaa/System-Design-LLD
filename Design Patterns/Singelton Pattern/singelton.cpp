#include<bits/stdc++.h>
using namespace std;
class Student{
    private:
    static Student* student1;
    Student(){
        cout<<"constructor initiazed";
    }
    public:
    static Student* getinstance(){
        if(student1!=nullptr)
        return student1;
        student1=new Student();
        return student1;
    }
};
Student* Student::student1=nullptr;
int main(){
    Student* a=Student::getinstance();
    Student* b=Student::getinstance();
    if(a==b)
    cout<<1;
    else
    cout<<3;
}