//模板方法
#include <iostream>
#include <string>

class DataMiner{
public:
//template method
    void mineData(std::string path) {
        openFile(path);
        exctractData();
        makeReport();
        hook1();
        closeFile();
    }
protected:
    virtual std::string openFile(std::string path)  =0;
    void exctractData() const{
        std::cout<<"DataMiner：从字符串中提取相关数据.\n";
    }
    void makeReport() const{
        std::cout<<"DataMiner：生成数据分析报告.\n";
    }
    virtual void closeFile() const =0;
    virtual void hook1() const {}
protected:
    std::string m_str="";
};

class PDFDataMiner: public DataMiner{
public:
    virtual std::string openFile(std::string path)  override{
        m_str = "PDFDataMiner:openfileto string";
        std::cout<<"PDFDataMiner：打开PDF文件，转换为字符串序列\n";
        return m_str;
    }
    virtual void closeFile() const {
        std::cout<<"PDFDataMiner：关闭PDF文件\n";
    }
};

class WordDataMiner: public DataMiner{
public:
    virtual std::string openFile(std::string path)  override{
        m_str = "WordDataMiner: openfileto string";
        std::cout<<"WordDataMiner：打开PDF文件，转换为字符串序列\n";
        return m_str;

    }
    virtual void closeFile() const {
        std::cout<<"WordDataMiner：关闭Word文件\n";
    }
    virtual void hook1() const {
        std::cout<<"WordDataMiner:给word文件加水印\n";
    }
};

void clientCode(DataMiner* dataMiner,std::string path){
    dataMiner->mineData(path);
}

int main(){
    PDFDataMiner pdfDataMiner;
    clientCode(&pdfDataMiner,"aa.pdf");
    std::cout<<"----------------------------\n";
    WordDataMiner wordDataMiner;
    clientCode(&wordDataMiner,"aa.doc");
}