#include <iostream>

using namespace std;
//产品的接口
class Transport{
public:
    virtual ~Transport(){}
    virtual void deliver() const=0;
};
//产品A
class Truck: public Transport{
public:
    void deliver()const override{
        std::cout<<"卡车运输货物中"<<endl;
    }
};
//产品B
class Ship: public Transport{
public:
    void deliver() const override{
        std::cout<<"轮船运输货物中"<<endl;
    }
};

//创造者
class Logistics{
public:
    virtual ~Logistics(){}
    //工厂方法核心
    virtual Transport* factoryMethod() const =0;
    void doSomething() const{
        Transport * transport =factoryMethod();
        transport->deliver();
        delete  transport;
    }
};

//具体创造者A
class TruckLogistis:public Logistics{
public:
    virtual Transport* factoryMethod()const override{
        return  new Truck();
    }
    virtual ~TruckLogistis(){}
};
//具体创造者B
class ShipLogistis:public Logistics{
public:
    virtual Transport* factoryMethod()const override{
        return  new Ship();
    }
    virtual ~ShipLogistis(){}
};

int main()
{
    Logistics* truckLogistic = new TruckLogistis();
    truckLogistic->doSomething();
    delete truckLogistic;

    Logistics* shipLogistic = new ShipLogistis();
    shipLogistic->doSomething();
    delete shipLogistic;
    return 0;
}
