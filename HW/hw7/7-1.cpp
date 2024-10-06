#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

// This class is quite simple with only some getters and setters.
// Finish the definitions of these functions first.
class Grade {
 public:
  // This constructor initializes the members with the parameters.
  Grade(const std::string &name, int number, double grade):m_name(name),m_number(number),m_grade(grade){};
  std::string getName() const{
    return m_name;
  };
  void setName(const std::string &name){
    m_name=name;
  };
  int getNumber() const{
    return m_number;
  };
  void setNumber(int number){
    m_number=number;
  };
  double getGrade() const{
    return m_grade;
  };
  void setGrade(double grade){
    m_grade=grade;
  };

 private:
  std::string m_name;
  int m_number;
  double m_grade;
};

struct NameComparator {
  bool operator()(const Grade &a, const Grade &b) const{
    return a.getName()<b.getName();
  }; 
}x1;

struct NumberComparator {
  bool operator()(const Grade &a, const Grade &b) const{
    return a.getNumber()<b.getNumber();
  };
}x2;

struct GradeComparator {
  bool operator()(const Grade &a, const Grade &b) const{
    return a.getGrade()>b.getGrade();
  };
}x3;

class Gradesheet {
  friend std::ostream &operator<<(std::ostream &os, const Gradesheet &sheet){
    os<<"/------------------------------\\"<<std::endl;
    os<<"|Name      Number    Grade     |"<<std::endl;
    os<<"|------------------------------|"<<std::endl;
    for(int i=0;i<sheet.m_grades.size();i++){
      os<<"|"<<std::left<<std::setw(10)<<sheet.m_grades[i].getName()
      <<std::left<<std::setw(10)<<sheet.m_grades[i].getNumber()
      <<std::left<<std::setw(10)<<std::setprecision(3)<<sheet.m_grades[i].getGrade()<<"|"<<std::endl;
    }
    os<<"\\------------------------------/"<<std::endl;
    return os;
  };

 public:
  Gradesheet(){};
  ~Gradesheet(){};
  std::size_t size() const{
    return m_grades.size();
  };
  double average() const{
    double sum=0;
    for(int i=0;i<m_grades.size();i++){
      sum+=m_grades[i].getGrade();
    }
    return sum/m_grades.size();
  };
  bool addGrade(const Grade &grade){
    int flag=0;
    for(int i=0;i<m_grades.size();i++){
      if(grade.getName()==m_grades[i].getName()||grade.getNumber()==m_grades[i].getNumber()) flag=1;
    }
    if(flag==0){
      m_grades.push_back(grade);
      return true;
    }
    else return false;
  };
  double findByName(const std::string &name) const{
    int flag=0;
    for(int i=0;i<m_grades.size();i++){
      if(m_grades[i].getName()==name){
        flag=1;
        return m_grades[i].getGrade();
      }
    }
    if(flag==0) return -1;
  };
  double findByNumber(int number) const{
    int flag=0;
    for(int i=0;i<m_grades.size();i++){
      if(m_grades[i].getNumber()==number){
        flag=1;
        return m_grades[i].getGrade();
      }
    }
    if(flag==0) return -1;
  };
  Grade &operator[](std::size_t i){
    return m_grades[i];
  };
  const Grade &operator[](std::size_t i) const{
    return m_grades[i];
  };
  void sortByName(){
    sort(m_grades.begin(),m_grades.end(),x1);
  };
  void sortByNumber(){
    sort(m_grades.begin(),m_grades.end(),x2);
  };
  void sortByGrade(){
    sort(m_grades.begin(),m_grades.end(),x3);
  };

 private:
  std::vector<Grade> m_grades;
};

int main() {
  Gradesheet sheet;
  sheet.addGrade(Grade("Bob", 1, 95));
  sheet.addGrade(Grade("Carl", 2, 1257923));
  sheet.addGrade(Grade("Alex", 3, 90));
  //sheet.sortByGrade();
  //sheet.sortByName();
  sheet.sortByNumber();
  std::cout << "size == " << sheet.size() << "\n" << sheet;
  return 0;
}