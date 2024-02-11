//代理模式
#include <iostream>
#include <string>

//接口:真实数据库和代理数据库都依赖这个接口
class DataBase{
public:
    virtual void request() const =0;
};

class RealDataBase :public  DataBase {
public:
    void request() const override{
        std::cout<< "真实数据库：处理业务请求。\n";
    }
};

class ProxyDataBase :public DataBase{
private:
    RealDataBase* m_realDataBase;

    bool checkAccess() const{
        std::cout<<"ProxyDataBase:在发出请求之前，检查一下。\n";
        return true;
    }
    void log() const{
        std::cout<<"ProxyDataBase:处理日志\n";
    }
public:
    ProxyDataBase(RealDataBase* realDataBase):m_realDataBase(realDataBase){}
    void request() const override{
        if(checkAccess()){
            std::cout<< "Proxy数据库，通过代理处理数据库请求。\n";
            m_realDataBase->request();
            log();
        }else{
            std::cout<<"ProxyDataBase：数据库访问请求被驳回\n";
        }
    }
};

void clientcode(const DataBase& dataBase){
    dataBase.request();
}

int main(){
    std::cout<<"Client:直接使用数据库处理请求\n";
    RealDataBase realDataBase;
    clientcode(realDataBase);
    std::cout<<"Client:使用代理数据库处理请求\n";
    ProxyDataBase proxy(&realDataBase);
    clientcode(proxy);
}
