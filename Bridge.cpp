#include <iostream>
#include <string>

//实现
class Device{
public:
    virtual ~Device(){}
    virtual std::string turnOn() const =0;
    virtual std::string turnOff() const = 0;
    virtual std::string mute() const =0;    
};

class TV :public Device{
public:
    ~TV(){}
    std::string turnOn()const override{
        return "TV:开机...\n";
    }
    std::string turnOff()const override{
        return "TV:关机...\n";
    }
    std::string mute()const override{
        return "TV:静音...\n";
    }
};

class Radio :public Device{
public:
    ~Radio(){}
    std::string turnOn()const override{
        return "Radio:开机...\n";
    }
    std::string turnOff()const override{
        return "Radio:关机...\n";
    }
    std::string mute()const override{
        return "Radio:静音...\n";
    }
};

//抽象
class BaseRemoteController{
protected:
    Device* m_implementation;
public:
    ~BaseRemoteController(){};
    BaseRemoteController(Device*implementation):m_implementation(implementation){}

    virtual std::string sendTurnOn() {
       return "基础遥控器发出TurnOn:"+m_implementation->turnOn();
    }
    virtual std::string sendTurnOff(){
        return "基础遥控器发出TurnOff:"+m_implementation->turnOff();
    } 

};

class AdvancedReomteController:public BaseRemoteController{
public:
    ~AdvancedReomteController(){};
    AdvancedReomteController(Device*implementation):BaseRemoteController(implementation){}

    virtual std::string sendTurnOn() {
       return "高级遥控器发出TurnOn:"+m_implementation->turnOn();
    }
    virtual std::string sendTurnOff(){
        return "高级遥控器发出TurnOff:"+m_implementation->turnOff();
    }
    virtual std::string sendMute(){
        return "高级遥控器发出sendMute:"+m_implementation->mute();
    } 
};

int main(){
    Radio radio;
    BaseRemoteController baseRC(&radio);
    std::cout<< baseRC.sendTurnOn();
    std::cout<< baseRC.sendTurnOff();
    std::cout<<"----------------------\n";
    AdvancedReomteController advanceRC(&radio);
    std::cout<<advanceRC.sendTurnOn();
    std::cout<<advanceRC.sendTurnOff();
    std::cout<<advanceRC.sendMute();
    
    std::cout<<"--------------------------\n";
    TV tv;
    BaseRemoteController basetv(&tv);
    std::cout << basetv.sendTurnOn();
    std::cout << basetv.sendTurnOff();
    AdvancedReomteController advancetv(&tv);
    std::cout<<advancetv.sendTurnOn();
    std::cout<<advancetv.sendTurnOff();
    std::cout<<advancetv.sendMute();

}