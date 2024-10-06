#include <string>
#include<iostream>

class Point {
  double x{0}, y{0};
  std::string label;

 public:
  Point(double x0, double y0, const std::string &l = "")
      : x(x0), y(y0), label(l) {}
  Point() = default;
  double get_x() const {
    return x;
  }
  double get_y() const {
    return y;
  }
  std::string get_label() const {
    return label;
  }
  Point &set_x(double x0) {
    x = x0;
    return *this;
  }
  Point &set_y(double y0) {
    y = y0;
    return *this;
  }
  Point &set_label(const std::string &l) {
    label = l;
    return *this;
  }
};

class Point_counted {
  friend class Point_handle;
public:
  Point p;
  unsigned cnt;

  Point_counted(const Point &other):p(other.get_x(),other.get_y(),other.get_label()),cnt(1){};
  Point_counted(double x0, double y0, const std::string &l = ""):p(x0,y0,l),cnt(1){};

};

class Point_handle {
public:
  
  Point_counted *ptr;
  Point_handle(){
    Point p;
    ptr=new Point_counted(p);
    ptr->cnt=1;
  }
  Point_handle(const Point &other):ptr(new Point_counted(other)){}
  Point_handle(double x0, double y0, const std::string &l = ""):ptr(new Point_counted(x0,y0,l)){}
  Point_handle(const Point_handle &other){
    ptr=other.ptr;
    ptr->cnt++;
  }
  ~Point_handle(){    
     if(ptr->cnt==1) delete ptr;
     else ptr->cnt--;
  }
  unsigned ref_count() const{
    return ptr->cnt;
  }
  double get_x() const{
    return ptr->p.get_x();
  }
  double get_y() const{
    return ptr->p.get_y();
  }
  std::string get_label() const{
    return ptr->p.get_label();
  }
  Point_handle &set_x(double x0){
    if(ptr->cnt==1){
      ptr->p.set_x(x0);
      return *this;
    }
    else{
      ptr->cnt--;
      Point p1(x0,ptr->p.get_y(),ptr->p.get_label());
      ptr=new Point_counted(p1);    
      return *this;  
    }
  }
  Point_handle &set_y(double y0){
    if(ptr->cnt==1){
      ptr->p.set_y(y0);
      return *this;
    }
    else{
      ptr->cnt--;
      Point p1(ptr->p.get_x(),y0,ptr->p.get_label());
      ptr=new Point_counted(p1); 
      return *this;     
    }
  }
  Point_handle &set_label(const std::string &l){
    if(ptr->cnt==1){
      ptr->p.set_label(l);
      return *this;
    }
    else{
      ptr->cnt--;
      Point p1(ptr->p.get_x(),ptr->p.get_y(),l);
      ptr=new Point_counted(p1);  
      return *this;    
    }
  }
  Point_handle& operator=(const Point_handle &other){
    if(ptr==other.ptr) return *this;  
    else{  
      this->ptr->cnt--;     
      if(this->ptr->cnt==0) delete this->ptr;
      this->ptr=other.ptr;
      other.ptr->cnt++;
      return *this;
    }
  }
};

int main(){
  // Point_handle ph2(1,2,"name");
  // Point_handle ph1 = ph2;
  // std::cout<<ph1.ptr->p.get_x()<<std::endl;
  // std::cout<<ph1.ptr->p.get_y()<<std::endl;
  // std::cout<<ph1.ptr->p.get_label()<<std::endl;


  Point_handle ph1(5, 6, "A");
  Point_handle ph2(ph1);
  ph2.set_label("B");
  std::cout << ph1.get_x() << std::endl;
  std::cout << ph1.get_y() << std::endl;
  std::cout << ph1.get_label() << std::endl;

  std::cout << ph2.get_x() << std::endl;
  std::cout << ph2.get_y() << std::endl;
  std::cout << ph2.get_label() << std::endl;

// Point_handle ph1(5, 6, "A"), ph2 = ph1;
// ph2.set_x(7);
// std::cout << ph1.ref_count() << ", " << ph2.ref_count() << std::endl;



}