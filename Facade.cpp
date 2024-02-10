//外观模式
#include <iostream>
#include <string>

//子系统1
class VideoStstem{
public:
    std::string initial() const{
        return "视频系统:Ready!\n";
    }
    std::string play() const{
        return "视频系统:Go!\n";
    }
    //......
    std::string operationX() const{
        return "视频系统:不常用的骚操作!\n";
    }
};

//子系统2
class RadioStstem{
public:
    std::string init() const{
        return "音频系统:就绪!\n";
    }
    std::string play() const{
        return "音频系统:播放!\n";
    }
    //......
    std::string operationX() const{
        return "音频系统:不常用的骚操作!\n";
    }
    std::string mute() const{
        return "音频系统:静音!\n";
    }
};
//外观
class Controller{
protected:
    VideoStstem * m_vidio;
    RadioStstem * m_radio;
public:
    ~Controller(){ 
         delete m_vidio;
         delete m_radio;      
    }
    Controller(VideoStstem* vidio = nullptr,RadioStstem* radio = nullptr){
        if(!vidio)  m_vidio = vidio;
        else new VideoStstem;
        m_radio = radio ? radio : new RadioStstem;
    }
    std::string start(){
        std::string string = "控制器启动系统:\n";
        string+= m_vidio->initial();
        string+=m_radio->init();
        string+="控制器播放:\n";
        string+=m_vidio->play();
        string+=m_radio->play();
        return string;
    }
    std::string mute(){
        return m_radio->mute();
    }
};

int main(){
    VideoStstem *vidio = new VideoStstem;
    RadioStstem* radio = new RadioStstem;
    Controller controller(vidio,radio);//外观对象，负责回收子系统
    std::cout<<controller.start();
}