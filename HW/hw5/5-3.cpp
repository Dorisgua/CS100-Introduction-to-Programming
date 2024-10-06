#include <iostream>
#include <string>
#include<cmath>

class Expr_node {
 public:
  Expr_node() = default;
  virtual double eval() const = 0;
  virtual std::string to_string() const = 0;
  virtual ~Expr_node() = default;
  Expr_node(const Expr_node &) = delete;
  Expr_node &operator=(const Expr_node &) = delete;
};


//////////////////////////////////////////////////
class Number_node : public Expr_node {
  friend Number_node *make_number(double);
  double value;
  Number_node(double val) : value(val) {}
  virtual double eval() const override
  {
    return value;
  };
  virtual std::string to_string() const override
  {
    if(value>=0)  return std::to_string(value);
    else  return "("+std::to_string(value)+")";
  };
  ~Number_node(){};
};
inline Number_node *make_number(double value) {
  return new Number_node(value);
}

//////////////////////////////////////////////////
class Negation_node : public Expr_node {
  friend Negation_node *make_negation(Expr_node *operand);
  Expr_node *operand;
  Negation_node(Expr_node *oper):operand(oper){}
  virtual double eval() const override
  {
    return (-1)*operand->eval();
  };
  virtual std::string to_string() const override
  {
    return "(-"+operand->to_string()+")";
  };
  ~Negation_node()
  {
    delete operand;
  }
};
inline Negation_node *make_negation(Expr_node *operand) {
  return new Negation_node(operand);
}

////////////////////////////////////////////////////////
class Sin_node : public Expr_node {
  friend Sin_node *make_sin(Expr_node *operand);
  Expr_node *operand;
  Sin_node(Expr_node *oper):operand(oper){}
  virtual double eval() const override
  {
    return sin(operand->eval());
  };
  virtual std::string to_string() const override
  {
    if(operand->to_string()[0]=='(') return "sin"+operand->to_string();
    else return "sin("+operand->to_string()+")";
  };
  ~Sin_node()
  {
    delete operand;
  }
};
inline Sin_node *make_sin(Expr_node *operand) {
  return new Sin_node(operand);
}

///////////////////////////////////////////////////////
class Cos_node : public Expr_node {
  friend Cos_node *make_cos(Expr_node *operand);
  Expr_node *operand;
  Cos_node(Expr_node *oper):operand(oper){}
  virtual double eval() const override
  {
    return cos(operand->eval());
  };
  virtual std::string to_string() const override
  {
    if(operand->to_string()[0]=='(') return "cos"+operand->to_string();
    else return "cos("+operand->to_string()+")";
  };
  ~Cos_node()
  {
    delete operand;
  }
};
inline Cos_node *make_cos(Expr_node *operand) {
  return new Cos_node(operand);
}

//////////////////////////////////////////////////////
class Tan_node : public Expr_node {
  friend Tan_node *make_tan(Expr_node *operand);
  Expr_node *operand;
  Tan_node(Expr_node *oper):operand(oper){}
  virtual double eval() const override
  {
    return tan(operand->eval());                      
  };
  virtual std::string to_string() const override
  {
    if(operand->to_string()[0]=='(') return "tan"+operand->to_string();
    else return "tan("+operand->to_string()+")";
  };
  ~Tan_node()
  {
    delete operand;
  }
};
inline Tan_node *make_tan(Expr_node *operand) {
  return new Tan_node(operand);
}

////////////////////////////////////////////////////////
class Log_node : public Expr_node {
  friend Log_node *make_log(Expr_node *operand);
  Expr_node *operand;
  Log_node(Expr_node *oper):operand(oper){}
  virtual double eval() const override
  {
    return log(operand->eval());
  };
  virtual std::string to_string() const override
  {
    if(operand->to_string()[0]=='(') return "log"+operand->to_string();
    else return "log("+operand->to_string()+")";
  };
  ~Log_node()
  {
    delete operand;
  }
};
inline Log_node *make_log(Expr_node *operand) {
  return new Log_node(operand);
}

//////////////////////////////////////////////////////
class Exp_node : public Expr_node {
  friend Exp_node *make_exp(Expr_node *operand);
  Expr_node *operand;
  Exp_node(Expr_node *oper):operand(oper){}
  virtual double eval() const override
  {
    return exp(operand->eval());
  };
  virtual std::string to_string() const override
  {
    if(operand->to_string()[0]=='(') return "exp"+operand->to_string();
    else return "exp("+operand->to_string()+")";
  };
  ~Exp_node()
  {
    delete operand;
  }
};
inline Exp_node *make_exp(Expr_node *operand) {
  return new Exp_node(operand);
}

//////////////////////////////////////////////////////
class Binary_node : public Expr_node {
protected:
  Expr_node *lhs;
  Expr_node *rhs;
  Binary_node(Expr_node *left,Expr_node *right):lhs(left),rhs(right){}
  ~Binary_node()
  {
    delete lhs;
    delete rhs;
  }
};
//////////////////////////////////////////////////////////
class Plus_node : public Binary_node {
  friend Plus_node *make_plus(Expr_node *, Expr_node *);
  Plus_node(Expr_node *left,Expr_node *right):Binary_node(left,right){}
  virtual double eval() const override
  {
    return lhs->eval()+rhs->eval();
  };
  virtual std::string to_string() const override
  {
    return "("+lhs->to_string()+" + "+rhs->to_string()+")";
  };
  ~Plus_node(){}
};
inline Plus_node *make_plus(Expr_node *l, Expr_node *r) {
  return new Plus_node(l,r);
}
////////////////////////////////////////////////////////////
class Minus_node : public Binary_node {
  friend Minus_node  *make_minus(Expr_node *, Expr_node *);
  Minus_node(Expr_node *left,Expr_node *right):Binary_node(left,right){}
  virtual double eval() const override
  {
    return lhs->eval()-rhs->eval();
  };
  virtual std::string to_string() const override
  {
    return "("+lhs->to_string()+" - "+rhs->to_string()+")";
  };
};
inline Minus_node  *make_minus(Expr_node *l, Expr_node *r) {
  return new Minus_node(l,r);
}
/////////////////////////////////////////////////////////////
class Multiply_node : public Binary_node {
  friend Multiply_node *make_multiply(Expr_node *, Expr_node *);
  Multiply_node(Expr_node *left,Expr_node *right):Binary_node(left,right){}
  virtual double eval() const override
  {
    return lhs->eval()*rhs->eval();
  };
  virtual std::string to_string() const override
  {
    return "("+lhs->to_string()+" * "+rhs->to_string()+")";
  };
};
inline Multiply_node *make_multiply(Expr_node *l, Expr_node *r) {
  return new Multiply_node(l,r);
}
///////////////////////////////////////////////////////////////
class Divide_node : public Binary_node {
  friend Divide_node *make_divide(Expr_node *, Expr_node *);
  Divide_node(Expr_node *left,Expr_node *right):Binary_node(left,right){}
  virtual double eval() const override
  {
    return lhs->eval()/rhs->eval();
  };
  virtual std::string to_string() const override
  {
    return "("+lhs->to_string()+" / "+rhs->to_string()+")";
  };
};
inline Divide_node *make_divide(Expr_node *l, Expr_node *r) {
  return new Divide_node(l,r);
}



int main() {
  //Expr_node *expr_tree =make_plus(make_number(4), make_number(5));
  //Expr_node *expr_tree = make_divide(make_plus(make_number(3), make_multiply(make_number(4), make_number(5))),make_number(6));
  // Expr_node *expr_tree = make_multiply(make_divide(make_number(-3), make_negation(make_multiply(make_number(4), make_number(5)))),make_number(6));
  // std::cout << expr_tree->eval() << std::endl;
  // std::cout << expr_tree->to_string() << std::endl;
  // delete expr_tree;
  //Expr_node *bonus_tree =make_sin(make_exp(make_sin(make_plus(make_number(3),make_number(-2)))));
  //Expr_node *bonus_tree =make_plus(make_exp(make_sin(make_number(3))), make_number(1));
  Expr_node *bonus_tree =make_exp(make_cos(make_plus(make_number(3),make_negation(make_number(6)))));
  std::cout << bonus_tree->eval() << std::endl;
  std::cout << bonus_tree->to_string() << std::endl;
  delete bonus_tree;
  return 0;
}