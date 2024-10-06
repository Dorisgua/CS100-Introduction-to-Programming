#include <cstddef>
#include <iostream>

class Matrix {
public:
    typedef double Scalar;
    typedef std::size_t Index;

    explicit Matrix(Index rows, Index cols){
        m_row=rows;
        m_col=cols;
        m_matrix=new double*[m_row];
        for(int i=0;i<m_row;i++){
            m_matrix[i]=new double[m_col];
        }
        for(int i=0;i<m_row;i++){
            for(int j=0;j<m_col;j++){
                m_matrix[i][j]=0;
            }
        }
    };
    Matrix(const Matrix &other){
        m_row=other.m_row;
        m_col=other.m_col;
        m_matrix=new double*[m_row];
        for(int i=0;i<m_row;i++){
            m_matrix[i]=new double[m_col];
        }
        for(int i=0;i<m_row;i++){
            for(int j=0;j<m_col;j++){
                m_matrix[i][j]=other.m_matrix[i][j];
            }
        }
    };
    Matrix& operator=(const Matrix &other){
        if(this==&other) return *this;
        else{
            for(int i=0;i<this->m_row;i++){
                delete []this->m_matrix[i];
            }
            delete []this->m_matrix;
            this->m_row=other.m_row;
            this->m_col=other.m_col;
            this->m_matrix=new double*[this->m_row];
            for(int i=0;i<this->m_row;i++){
                this->m_matrix[i]=new double[this->m_col];
            }
            for(int i=0;i<m_row;i++){
                for(int j=0;j<m_col;j++){
                    this->m_matrix[i][j]=other.m_matrix[i][j];
                }
            }
            return *this;   
        }
    };
    ~Matrix(){
        for(int i=0;i<m_row;i++){
            delete []m_matrix[i];
        }
        delete []m_matrix;
    };
    Index rows() const{
        return m_row;
    }
    Index cols() const{
        return m_col;
    };
    Scalar& at(Index r, Index c){
        return m_matrix[r][c];
    };
    const Scalar& at(Index r, Index c) const{
        return m_matrix[r][c];
    };
    Matrix operator+(const Matrix &other) const{
        Matrix a(this->m_row,this->m_col);
        a.m_row=this->m_row;
        a.m_col=this->m_col;
        for(int i=0;i<this->m_row;i++){
            for(int j=0;j<this->m_col;j++){
                a.m_matrix[i][j]=this->m_matrix[i][j]+other.m_matrix[i][j];
            }
        }
        return a;
    };
    Matrix operator-(const Matrix &other) const{
        Matrix a(m_row,m_col);
        for(int i=0;i<m_row;i++){
            for(int j=0;j<m_col;j++){
                a.m_matrix[i][j]=this->m_matrix[i][j]-other.m_matrix[i][j];
            }
        }
        return a;
    };
    Matrix operator*(const Matrix &other) const{
        Matrix a(this->m_row,other.m_col);
        for(int i=0;i<this->m_row;i++){
            for(int j=0;j<other.m_col;j++){
                for(int k=0;k<other.m_row;k++){
                    a.m_matrix[i][j]+=this->m_matrix[i][k]*other.m_matrix[k][j];
                }
            }
        }
        return a;
    };
    Matrix transpose() const{
        Matrix a(m_col,m_row);
        for(int i=0;i<m_row;i++){
            for(int j=0;j<m_col;j++){
                a.m_matrix[j][i]=this->m_matrix[i][j];
            }
        }    
        return a;
    };
    Matrix block(Index r, Index c, Index p, Index q) const{
        Matrix a(p,q);
        for(int i=0;i<p;i++){
            for(int j=0;j<q;j++){
                a.m_matrix[i][j]=this->m_matrix[r+i][c+j];
            }
        }
        return a;
    };
    Scalar trace() const{
        Scalar sum=0;
        for(int i=0;i<m_row;i++){
            for(int j=0;j<m_col;j++){
                if(i==j) sum+=m_matrix[i][j];
            }
        }
        return sum;
    };
    Scalar det(double **m_matrix,Index n) const //输入代表矩阵的二维数组、矩阵阶数，返回矩阵的行列式
    {
        Scalar d=0;
        if(n==1) d=m_matrix[0][0];
        if(n==2) d=m_matrix[0][0]*m_matrix[1][1]-m_matrix[0][1]*m_matrix[1][0];
        else{
        for(int k=0;k<n;k++){
            // 为代数余子式申请内存
            Scalar **M;
            M=(Scalar**)malloc((n-1)*sizeof(Scalar*));
            for(int i=0;i<n-1;i++)
                M[i]=(Scalar*)malloc((n-1)*sizeof(Scalar));			
            // 为代数余子式赋值
            for(int i=0;i<n-1;i++)
                for(int j=0;j<n-1;j++)
                    M[i][j]=m_matrix[i+1][j<k?j:j+1];				
            // 按第一行展开，递归计算行列式，注意元素0则不展开可以加快计算速度
            if(m_matrix[0][k])
                d+=m_matrix[0][k]*det(M,n-1)*(((2+k)%2)?-1:1);		
            // 释放内存
            for(int i=0;i<n-1;i++)free(M[i]);
            free(M);
            }
        }
        return d;                   
    }
    Scalar determinant() const{
        return det(this->m_matrix,this->m_row);
    };

//private:
    std::size_t m_row;
    std::size_t m_col;
    double** m_matrix;

};

int main(){
    Matrix a(2,2);
    a.m_matrix[0][0]=1;
    a.m_matrix[0][1]=2;
    a.m_matrix[1][0]=3;
    a.m_matrix[1][1]=4;

    Matrix b(2,2);
    b.m_matrix[0][0]=2;
    b.m_matrix[0][1]=4;
    b.m_matrix[1][0]=6;
    b.m_matrix[1][1]=8;

    Matrix c(2,3);
    c.m_matrix[0][0]=1;
    c.m_matrix[0][1]=2;
    c.m_matrix[0][2]=3;
    c.m_matrix[1][0]=4;
    c.m_matrix[1][1]=5;
    c.m_matrix[1][2]=6;
    // c.m_matrix[2][0]=7;
    // c.m_matrix[2][1]=8;
    // c.m_matrix[2][2]=9;

    Matrix d(2,3);
    d.m_matrix[0][0]=1;
    d.m_matrix[0][1]=2;
    d.m_matrix[0][2]=3;
    d.m_matrix[1][0]=4;
    d.m_matrix[1][1]=5;
    d.m_matrix[1][2]=4;
    // d.m_matrix[2][0]=3;
    // d.m_matrix[2][1]=2;
    // d.m_matrix[2][2]=1;



    Matrix e(2,3);

    e=d;

    std::cout<<e.m_matrix[0][0]<<std::endl;
    std::cout<<e.m_matrix[0][1]<<std::endl;
    std::cout<<e.m_matrix[0][2]<<std::endl;
    std::cout<<e.m_matrix[1][0]<<std::endl;
    std::cout<<e.m_matrix[1][1]<<std::endl;
    std::cout<<e.m_matrix[1][2]<<std::endl;
    // std::cout<<e.m_matrix[2][0]<<std::endl;
    // std::cout<<e.m_matrix[2][1]<<std::endl;
    // std::cout<<e.m_matrix[2][2]<<std::endl;


    //std::cout<<c.trace()<<std::endl;






}