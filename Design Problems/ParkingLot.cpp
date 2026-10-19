#include<bits/stdc++.h>
using namespace std;
enum spottype{
    carspot,bikespot
};
enum vehicletype{
    car,bike
};
class Spot{
    public:
    // int number;
    spottype s;
    int id;
    bool isOccupied;
    Spot(int id,spottype s){
        this->id=id;
        this->s=s;
        isOccupied=false;
    }
};
class Floor{
    public:
    int fno;
    vector<Spot*> spots;
    Floor(int fno,vector<Spot*> spots){
        this->fno=fno;
        this->spots=spots;
    }
};
class Vehicle{
    public:
    string rn;
    vehicletype type;

    Vehicle(string rn,vehicletype type){
        this->rn=rn;
        this->type=type;
    }
};
class ParkingLot{
    public:
    int id;
    vector<Floor*> floors;
    ParkingLot(int id,vector<Floor*> floors){
        this->id=id;
        this->floors=floors;
    }
};
class Ticket{
    public:
    int id;
    string rn;
    Spot* spot;
    time_t entrytime;
    Ticket(int id,string rn,Spot* spot){
        this->id=id;
        this->rn=rn;
        this->spot=spot;
        entrytime=time(0);
    }

};
class Pricing{
    public:
    virtual int getprice(time_t entrytime,time_t exittime)=0;
};
class generalprice: public Pricing{
    public:
    int getprice(time_t entrytime,time_t exittime){
        return (exittime-entrytime)/3600*60;
    }
};
class seatAvailabilty{
    public:
    virtual Spot* findseat(spottype c,ParkingLot* P)=0;
};
class findfirstfit: public seatAvailabilty{
    public:
    Spot* findseat(spottype c,ParkingLot* P){
        vector<Floor*>& totalfloor=P->floors;
        for(int i=0;i<totalfloor.size();i++){
            Floor* f=totalfloor[i];
            vector<Spot*> spotss=f->spots;
            for(int j=0;j<spotss.size();j++){
                Spot* sp=spotss[j];
                if(sp->isOccupied)
                continue;
                else if(sp->s==c)
                return sp;
            } 
        }
        return nullptr;
    }
};

class Service{
    public:
    ParkingLot* P;
    Pricing* pr;
    seatAvailabilty* s;
    int id=0;
    Service(ParkingLot* p,Pricing* pr,seatAvailabilty* s){
        this->P=p;
        this->pr=pr;
        this->s=s;
    }
    //entry
    Ticket* getentry(vehicletype v,string rn){
        Vehicle* v1=new Vehicle(rn,v);
        spottype st;
        if(v==car)
        st=carspot;
        else
        st=bikespot;
        Spot* location=s->findseat(st,P);

        if(location==nullptr){
            cout<<"Parking is Full";
            return nullptr;
        }
        id++;
        Ticket* t=new Ticket(id,rn,location);
        location->isOccupied=true;
        return t;
    }
    void exit(Ticket* t,time_t exittime){
        int charges=pr->getprice(t->entrytime,exittime);
        cout<<"Charges are: "<<charges<<endl;
        Spot* s=t->spot;
        s->isOccupied=false;
    }
};
int main(){
    
    vector<Spot*> spots;
    int id=1;
    spots.push_back(new Spot(id,bikespot));
    id++;
    spots.push_back(new Spot(id,bikespot));
    id++;
    spots.push_back(new Spot(id,carspot));
    id++;
    Floor* f1=new Floor(1,spots);
    vector<Floor*> floors;
    floors.push_back(f1);
    ParkingLot* P=new ParkingLot(1,floors);

    Service* S=new Service(P,new generalprice(),new findfirstfit());


    //creating vehicle

    string number,number2,n3;
    cout<<"Number: ";
    cin>>number;
    vehicletype v=car;
    Ticket* t=S->getentry(v,number);
    cout<<t->id;
    cout<<"Number: ";
    cin>>number2;
    Ticket* t2=S->getentry(v,number);

    cout<<"Number: ";
    cin>>n3;
    Ticket* t3=S->getentry(v,number);
    time_t exittime=time(0)+3600;
    S->exit(t,exittime);

}