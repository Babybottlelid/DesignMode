//访问者模式  操作者实际上
#include<iostream>
#include<string>
#include <vector>

class IceCream;
class Popsicle;

class Visitor{
public:
    virtual void visitIcCream(const IceCream* element) const =0;
    virtual void visitPopsicle(const Popsicle* element)const =0;
};

class Component{
public:
    virtual void accept(Visitor* visitor) const =0;
};

class IceCream:public Component{
public:
    virtual void accept(Visitor* visitor) const{
        visitor->visitIcCream(this);
    }
    std::string getIceCream()const{
        return "冰淇凌";
    }
};

class Popsicle:public Component{
public:
    virtual void accept(Visitor* visitor) const{
        visitor->visitPopsicle(this);
    }
    std::string getPopsicle()const{
        return "雪糕";
    }
};

class Frosting:public Visitor{
 public:
    virtual void visitIcCream(const IceCream* element) const {
        std::cout<<element->getIceCream()<<"+糖霜\n";
    }
    virtual void visitPopsicle(const Popsicle* element)const{
        std::cout<<element->getPopsicle()<<"+糖霜\n";
    } 
};

class Chocolate:public Visitor{
 public:
    virtual void visitIcCream(const IceCream* element) const {
        std::cout<<element->getIceCream()<<"+巧克力\n";
    }
    virtual void visitPopsicle(const Popsicle* element)const{
        std::cout<<element->getPopsicle()<<"+巧克力\n";
    } 
};

void clientcode(std::vector<Component*> components,Visitor* visitor){
    for(auto item :components){
        item->accept(visitor);
    }
}
int main(){
    std::vector<Component*> components = {new IceCream,new Popsicle,new Popsicle};
    Frosting frosting;
    clientcode(components,&frosting);
    std::cout<<"------------------------------\n";
    Chocolate chocolate;
    clientcode(components,&chocolate);
    for(auto item :components){
        delete item;
    }

}