//命令模式
#include <iostream>
#include <string>
#include <vector>
//Receiver

class Kitchen{
private:
    Kitchen(){}
public:
    static Kitchen* getInstance(){
        static Kitchen* instance = new Kitchen();
        return instance;
    }

    void prepareFood(const std::string &food){
        std::cout<<"厨房：正在准备("<<food<<".)\n";
    }
};

class Command{
public:
    virtual ~Command(){}
    virtual void execute() const =0;
};

//ConcreteComand1
class Order :public Command{
private:
    Kitchen* m_kitchen;//reveiver
    std::vector<std::string> m_foods;//params
public:
    virtual ~Order(){}
    Order(Kitchen* kitchen,std::vector<std::string> foods):m_kitchen(kitchen),m_foods(foods){}
    virtual void execute() const override{
        std::cout<<"订单：需要送往厨房进行处理\n";
        for(const std::string & item : m_foods){
             m_kitchen->prepareFood(item);
        }
    }
};

//Invoker
class Waitress{
private:
    Command* m_command;
public:
    ~Waitress(){ delete m_command;}
    void orderUP(Command* command){
        std::cout<<"服务员：提交订单...\n";
        m_command = command;
        m_command ->execute();
    }
};

class Client{
public:
    void orderFood(Waitress& waitress ,std::vector<std::string> foods){
        waitress.orderUP(new Order(Kitchen::getInstance(),foods));
    }
};
int main(){
    Client test;
    Waitress waitress;//Invoker
    test.orderFood(waitress,{"apple","nudoole","dranck","koffee"});
}