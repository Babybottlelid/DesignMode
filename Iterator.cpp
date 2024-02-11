//迭代器模式
#include <iostream>
#include <string>
#include <list>

template <class T,class U>
class Iterator{
public:
    typedef typename std::list<T>::iterator Pointer;
    Iterator(U* p_container,bool reverse = false):m_pContainer(p_container){

    }
    void First(){
        m_iter = m_pContainer->m_data.begin();
    }
    void next(){
        m_iter++;
    }
    bool isDone(){
        return (m_iter == m_pContainer->m_data.end());
    }
    Pointer current(){
        return m_iter;
    }
private:
    U* m_pContainer;
    Pointer m_iter;
};

template<class T>
class Container{
    friend class Iterator<T,Container>;
public:
    Iterator<T,Container>* createIterator(){
        return new Iterator<T,Container>(this);
    }
    void add (T data){
        m_data.push_back(data);
    }
private:
    std::list<T> m_data;
};

class MenuItem{
public:
    ~MenuItem(){}
    virtual void setData(std::string data1,std::string data2="") = 0;
    virtual std::string data() const =0;
};

class Beverage: public MenuItem{
public:
    ~Beverage(){}
    Beverage(std::string data1,std::string data2):m_data1(data1),m_data2(data2){

    }
    virtual void setData(std::string data1,std::string data2) override{
        m_data1 = data1;
        m_data2 = data2;
    }
    virtual std::string data() const override{
        return m_data1+"_"+m_data2;
    }
private:
    std::string m_data1;
    std::string m_data2;
};

class Pizza: public MenuItem{
public:
    ~Pizza(){}
    Pizza(std::string data):m_data(data){
    }
    virtual void setData(std::string data,std::string data2="") override{
        m_data = data;
    }
    virtual std::string data() const{
        return m_data;
    }
private:
    std::string m_data;
};
template<class T> 
void clientcode(T* iter){
    for(iter->First();!iter->isDone();iter->next()){
        std::cout<<iter->current()->data()<<std::endl;
    }
}

int main(){
    Container<Beverage> beverageMenu;
    Beverage coffee("咖啡","奶茶"),coffee2("珍珠","奶茶");
    beverageMenu.add(coffee2);
    beverageMenu.add(coffee);

    Container<Pizza> pizzaMenu;
    Pizza pizza1("意大利烤肠"),pizza2("意大利风味烤肉");
    pizzaMenu.add(pizza1);
    pizzaMenu.add(pizza2);

    //遍历菜单
    std::cout<<"Iterator用于遍历Beverage菜单\n";

    auto iter = beverageMenu.createIterator();
    clientcode(iter);

    std::cout<<"Iterator用于遍历Pizza菜单\n";
    auto iter2 = pizzaMenu.createIterator();
    clientcode(iter2);
}