
// DO NOT MODIFY THE CODE BELOW
#include <cstddef>
#include<cstdio>
#include<iostream>

class Array {
public:
    Array();
    explicit Array(std::size_t n);
    explicit Array(int *begin, int *end);
    Array(const Array &other);
    Array &operator=(const Array &other);
    ~Array();
    int &at(std::size_t n);
    const int &at(std::size_t n) const;
    std::size_t size() const;
    bool empty() const;
    void clear();
    Array slice(std::size_t l, std::size_t r, std::size_t s = 1) const;
private:
    std::size_t m_size;
    int *m_data;
};

// YOUR CODE STARTS HERE
Array::Array():m_data(nullptr),m_size(0){}
Array::Array(std::size_t n)
{
    m_size=n;
    m_data=new int[n]{};
}
Array::Array(int *begin, int *end)
{
    m_size=end-begin;
    m_data=new int[end-begin];
    for(int i=0;i<m_size;i++)
    {
        m_data[i]=begin[i];
    }
}
Array::Array(const Array &other)
{
    m_size=other.m_size;
    m_data=new int[m_size];
    for(int i=0;i<m_size;i++){
        m_data[i]=other.m_data[i];
    }    
}
Array &Array::operator=(const Array &other)
{
    if(this==&other) return *this;
    else
    {
        m_size=other.m_size;
        delete[] m_data;
        m_data=new int[m_size];
        for(int i=0;i<m_size;i++){
            m_data[i]=other.m_data[i];
        }
        return *this;
    }
}
Array::~Array()
{
    delete[] m_data;
    m_data=nullptr;
}
int &Array::at(std::size_t n)
{
    return m_data[n];
}
const int &Array::at(std::size_t n) const
{
    return m_data[n];
}
std::size_t Array:: size() const
{
    return m_size;
}
bool Array::empty() const
{
    if(m_size==0) return true;
    else return false;
}
void Array::clear()
{
    m_size=0;
}
Array Array::slice(std::size_t l, std::size_t r, std::size_t s) const
{
    if(l<r&&l>=0&&r>0&&s>0)
    {
        Array arr((r-l-1)/s+1);
        for(int i=0;i<(r-l-1)/s+1;i++)
        {
            arr.m_data[i]=m_data[l+i*s];
        }
        arr.m_size=(r-l-1)/s+1;
        return arr;
    }
    else{
        Array arr;
        return arr;
    }
}


// YOUR CODE ENDS HERE

int main() {
    // You can test your implementation here, but we will replace the main function on OJ.
     int a[10]= {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    const Array array(a, a + 10);
     Array(a,a+10);
     for(int i=0;i<3;i++)
     {
        std::cout<<array.at(i);
     }
     //std::cout<<array.slice(1,6,2).size();
    
     Array arr2(a,a+3);
     Array arr(arr2);
     for(int i=0;i<3;i++)
     {
        std::cout<<arr.at(i);
     }

     
     //Array array;
     //array=array;
    //  Array array2(array);
    //  std::cout<<array2.size();
    //  std::cout<<array2.at(5);
    
    
    
    // Array a;
    // int b=a.size();
    
    // std::cout<<a.empty();


    return 0;
}