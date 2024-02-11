//责任链模式

#include<iostream>
#include <string>
#include <list>
// class Handler{
// public:
//     virtual Handler* setNext(Handler* handler) =0;
//     virtual std::string handle(std::string request) =0;
// };

class BaseHandler{
private:
    BaseHandler* m_nextHandler;
public:
    BaseHandler* setNext(BaseHandler* handler){
        m_nextHandler = handler;
        return m_nextHandler;
     }
     virtual std::string handle(std::string request){
        if(m_nextHandler){
            return m_nextHandler->handle(request);
        }
        return "";
     }
};

class RobotAI :public BaseHandler{
public:
    std::string handle(std::string request) override{
        if(request=="使用向导"){
            return "RobotAI:我来处理-"+request+"-.\n";
        }
        else{
            return BaseHandler::handle(request);
        }
     }
};
class TelOprator :public BaseHandler{
public:
    std::string handle(std::string request) override{
        if(request=="常见问题"){
            return "TelOprator:我来处理-"+request+"-.\n";
        }
        else{
            return BaseHandler::handle(request);
        }
     }
};

class Export :public BaseHandler{
public:
    std::string handle(std::string request) override{
        if(request=="疑难杂症"){
            return "Export:我来处理-"+request+"-.\n";
        }
        else{
            return BaseHandler::handle(request);
        }
     }
};

void clientCode(BaseHandler& handler){
    std::list<std::string>  programs = {"疑难杂症","常见问题","使用向导","常见问题","扯淡问题"};
    for(const std::string& program : programs){
        std::string result = handler.handle(program);
        std::cout<<"Client:谁来处理"<<result<<std::endl;
        if(result.empty()){
            std::cout<<"处理结果:处理不了，没人处理\n";
        }
        else{
            std::cout<<"处理结果:处理...."<<result<<std::endl;
        }
    }
}

int main(){
    RobotAI robot;
    TelOprator telOptator;
    Export expert;
    robot.setNext(&telOptator)->setNext(&expert);
    std::cout<<"责任链:robot--->话务员-->专家\n";
    clientCode(robot);
}