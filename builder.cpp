#include <iostream>
#include <string>
#include <vector>\

void test(){
    std::cout<<"this is a test!"<<std::endl;
}

//产品1
class SimpleHouse{
public:
    std::vector<std::string> m_parts;

    void printParts() {
        std::cout<<"SimpHouse 包括: \n";
        for(uint32_t i=0;i<m_parts.size();++i){
            std::cout<<m_parts[i]<<std::endl;
        }
        std::cout<<"-------------------\n";
    }
};

class Builder{
public:
    virtual ~Builder(){}
    virtual void reset()=0;
    virtual void makeBaseHouse()=0;
    virtual void makeGarage()=0;
    virtual void makePool() =0;
};

//施工队1
class SimpleHouseBuilder : public Builder{
public:
    SimpleHouseBuilder(){
         reset();
    }
    virtual void makeBaseHouse() override{
        m_simplehouse->m_parts.push_back("BaseHouse");
    }
    virtual void makeGarage() override{
        m_simplehouse->m_parts.push_back("Garage");
    }
    virtual void makePool() override{
        m_simplehouse->m_parts.push_back("Pool");
    };

    ~SimpleHouseBuilder(){delete  m_simplehouse;}

    void reset()    override  {
         m_simplehouse =  new SimpleHouse();
    }

    SimpleHouse* getResult(){
        SimpleHouse *result = m_simplehouse;
        reset();
        return result;
    }
private:
    SimpleHouse* m_simplehouse;
};

//主管：负责流程
class Director{
private:
    Builder *m_builder;
public:
    void setBuiler(Builder* builder){
        m_builder = builder;
    }
    void  makeSimpleHouse(){
        m_builder->makeBaseHouse();
        m_builder->makeGarage();
    }
    void makeFullFuncHouse(){
        m_builder->makeBaseHouse();
        m_builder->makeGarage();
        m_builder->makePool();
    }

};

void client(Director* director){
    std::cout<<"客户自己设计流程--------------------\n";
    SimpleHouseBuilder* builder = new SimpleHouseBuilder();
    builder->makeBaseHouse();
    builder->makeGarage();
    SimpleHouse *simpleHouse =builder->getResult();
    simpleHouse->printParts();
    delete  simpleHouse;
    std::cout<<"主管设计流程--------------------\n";
    director->setBuiler(builder);
    director->makeFullFuncHouse();
    simpleHouse =builder->getResult();
    simpleHouse->printParts();

    delete builder;
    delete  simpleHouse;
}

int main()
{
    Director director;
    client(&director);
}