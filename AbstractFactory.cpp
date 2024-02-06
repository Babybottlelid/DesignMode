#include <iostream>
using namespace std;
//产品A
class Chair{
public:
    virtual ~Chair(){}
    virtual void sitOn()const =0;
};
//具体产品A1
class modernChair:public Chair{
public:
    virtual ~modernChair(){}
    virtual void sitOn() const override{
        std::cout<<"可以被坐下的modern chair\n";
    }
};
//具体产品A2
class chieseChair:public Chair{
public:
    virtual ~chieseChair(){}
    virtual void sitOn() const override{
        std::cout<<"中国风的chinese chair\n";
    }
};

//产品B
class Table{
public:
    virtual ~Table(){}
    virtual void putOn()const =0;
};
//具体产品B1
class modernTable:public Table{
public:
    virtual ~modernTable(){}
    virtual void putOn() const override{
        std::cout<<"modernTable\n";
    }
};
//具体产品B2
class chieseTable:public Table{
public:
    virtual ~chieseTable(){}
    virtual void putOn() const override{
        std::cout<<"中国风的chieseTable\n";
    }
};
//抽象工厂
class FurnitureFactory{
public:
    virtual Chair* creatChair()const=0;
    virtual Table* creatTable()const=0;
};
//具体工厂1
class modernStyleFactory:public FurnitureFactory{
public:
    virtual Chair * creatChair() const override{
        return new modernChair();
    }
    virtual Table * creatTable() const override{
        return new modernTable();
    }
};
//具体工厂2
class chineseStyleFactory:public FurnitureFactory{
public:
    virtual Chair * creatChair() const override{
        return new chieseChair();
    }
    virtual Table * creatTable() const override{
        return new chieseTable();
    }
};
//组装族
class Client{
public:
    Client( FurnitureFactory* factory){
        setFactory(factory);
    }
    void buyFurniture(){
        Chair* chair =m_factory->creatChair();
        Table* table =m_factory->creatTable();
        chair->sitOn();
        table->putOn();
        delete  chair;
        delete  table;
    }

    void setFactory(FurnitureFactory* factory){
        m_factory = factory;
    }

private:
    FurnitureFactory* m_factory;
};
 int main()
{
    modernStyleFactory modernFactory;
    Client client(&modernFactory);
    client.buyFurniture();

    chineseStyleFactory chineseFactory;
    client.setFactory(&chineseFactory);
    client.buyFurniture();
    return 0;
}
