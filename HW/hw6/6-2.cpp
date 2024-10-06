#include <iostream>
#include <string>
#include <vector>

class Alarm;

class AlarmClock {
public:
  // Your constructors and destructor.
  AlarmClock(){
    m_h=0;
    m_m=0;
    m_t=60*m_m+m_h;
  }
  void AddAlarm(Alarm* alarm);
  void Input();
  void TimeElapse();

  ~AlarmClock(){
    for(int i=0;i<m_alarms.size();i++){
      delete m_alarms[i];
    }    
    // for (std::vector<Alarm*>::iterator it = m_alarms.begin(); it != m_alarms.end(); it++){
    //     delete *it;
    //     m_alarms.erase(it);
    //   }
  }

private:
  std::vector<Alarm*> m_alarms;
  int m_h,m_m,m_t;//小时和分钟和总分钟
};

class Alarm {
public:
  // Your constructors and destructor.
  Alarm(char type,std::string name,int hour,int min){
    m_type=type;
    m_name=name;
    m_time=60*hour+min;
    m_hour=hour;
    m_min=min;
    m_flag=1;
  }
  virtual void Trigger() = 0;


//protected:
  char m_type;
  std::string m_name;
  int m_time,m_hour,m_min,m_flag;
};

class RepeatableAlarm:public Alarm{
public:
  RepeatableAlarm(char type,std::string name,int hour,int min):Alarm(type,name,hour,min){}
  void Trigger(){
    int a=m_hour/10;
    int b=m_min/10;
    if(a>0&&b>0) std::cout<<"Alarm "<<m_name<<" has triggered at "<<m_hour<<":"<<m_min<<"."<<std::endl;
    else if(a==0&&b>0) std::cout<<"Alarm "<<m_name<<" has triggered at 0"<<m_hour<<":"<<m_min<<"."<<std::endl;
    else if(a>0&&b==0) std::cout<<"Alarm "<<m_name<<" has triggered at "<<m_hour<<":0"<<m_min<<"."<<std::endl;
    else std::cout<<"Alarm "<<m_name<<" has triggered at 0"<<m_hour<<":0"<<m_min<<"."<<std::endl;
  }
};

class SnoozeableAlarm:public Alarm{
public:  
  SnoozeableAlarm(char type,std::string name,int hour,int min):Alarm(type,name,hour,min){}
  void Trigger(){
      int a=m_hour/10;
      int b=m_min/10;
      if(a>0&&b>0) std::cout<<"Alarm "<<m_name<<" has triggered at "<<m_hour<<":"<<m_min<<". Snooze? (Y/N)"<<std::endl;
      else if(a==0&&b>0) std::cout<<"Alarm "<<m_name<<" has triggered at 0"<<m_hour<<":"<<m_min<<". Snooze? (Y/N)"<<std::endl;
      else if(a>0&&b==0) std::cout<<"Alarm "<<m_name<<" has triggered at "<<m_hour<<":0"<<m_min<<". Snooze? (Y/N)"<<std::endl;
      else std::cout<<"Alarm "<<m_name<<" has triggered at 0"<<m_hour<<":0"<<m_min<<". Snooze? (Y/N)"<<std::endl;
      char ans;
      std::cin>>ans;
      if(ans=='Y'){
        if(m_min<50&&m_hour<=23){
          m_min+=10;
          m_time+=10;
        }
        else if(m_min>=50&&m_hour<23){
          m_min-=50;
          m_hour+=1;
          m_time+=10;
        } 
        else if(m_min>=50&&m_hour==23){
          m_min-=50;
          m_hour-=23;
          m_time-=1430;
        }
        m_flag=1;
      }
      else m_flag=0;    
    }
};

/**************** Implementations ******************/
void AlarmClock::AddAlarm(Alarm* alarm) {
  m_alarms.push_back(alarm);
}
void AlarmClock::Input() {
  int num;
  char type;
  char m=':';
  std::string name;
  int hour,min;
  std::cin>>num;
  for(int i=0;i<num;i++){
    std::cin>>type;
    std::cin>>hour;
    std::cin>>m;
    std::cin>>min;
    std::cin>>name;
    if(type=='R') AddAlarm(new RepeatableAlarm(type,name,hour,min));
    else  AddAlarm(new SnoozeableAlarm(type,name,hour,min));
  }
}

void AlarmClock::TimeElapse() {
  int size=m_alarms.size();
  for(int i=0;i<size;i++){
    if(m_alarms[i]->m_time==m_t){
      if(m_alarms[i]->m_type=='R'){
        m_alarms[i]->Trigger();
      }
      if(m_alarms[i]->m_type=='S'){
        if(m_alarms[i]->m_flag==1) m_alarms[i]->Trigger();
      }
    }
  }
  if(m_t<1440) m_t++;
  else m_t-=1440;
  //std::cout<<m_t<<std::endl;

}

int main() {
  AlarmClock clock;
  for (int days = 0; days < 3; days++) {
    std::cout << "Do you want to add any alarms?" << std::endl;
    clock.Input();
    for (int minute = 0; minute < 24 * 60; minute++) {
      clock.TimeElapse();
    }
    std::cout << "A day has elapsed." << std::endl;
  }
}