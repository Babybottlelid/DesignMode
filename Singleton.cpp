#include <iostream>
#include <thread>
#include <mutex>

class Singleton{
private:
    Singleton(const std::string value):m_value(value){
    }
    ~Singleton(){}
    std::string m_value;
public:
    Singleton(Singleton& other)= delete;
    Singleton(const Singleton& other)= delete;
    void operator=(const Singleton&) = delete;
    std::string value()const {return m_value;}
    static Singleton* GetInstance(const std::string & value);
private:
    static Singleton* m_instance;
    static std::mutex m_mutex;
};

std::mutex Singleton::m_mutex;
Singleton* Singleton::m_instance = nullptr;

Singleton* Singleton::GetInstance(const std::string & value){

    //方法1：多线程解决访问
    // std::lock_guard<std::mutex> lock(m_mutex);
    // if(m_instance == nullptr){
    //     m_instance = new Singleton(value);
    // }
    // return m_instance;
    //方式2：常用多线程开销解决
    static Singleton* instance = new Singleton(value);
    return instance;

}
void Cat(){
    Singleton* singleton = Singleton::GetInstance("Cat");
    std::cout<<singleton->value()<<"\n";
}
void Dog(){
    Singleton* singleton = Singleton::GetInstance("Dog");
    std::cout<<singleton->value()<<"\n";
}
int main(){ 
    std::thread t1(Cat);
   // _sleep(1000);
    std::thread t2(Dog);

    t1.join();
    t2.join();
}