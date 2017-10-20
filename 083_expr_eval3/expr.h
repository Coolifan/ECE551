#include <string>
#include <sstream>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual long evaluate() const = 0;
};

class NumExpression : public Expression {
  long num;
 public:
 NumExpression(long n) : num(n) {} 
  std::string toString() const {
    std::stringstream s;
    s << num;
    std::string str;
    s >> str;
    return str;
  }
  long evaluate() const {return num;}
  ~NumExpression() {}
};

class CalExpression : public Expression {
 protected:
  char op;
  Expression* lhs;
  Expression* rhs;
 public:
 CalExpression(char ope, Expression* ls, Expression* rs) : op(ope), lhs(ls), rhs(rs) {}
  virtual std::string toString() const {
    std::stringstream s;
    s << "(" << lhs->toString() << " " << op << " " << rhs->toString() << ")";
    std::string str = s.str(); 
    return str;
  }
  virtual long evaluate() const = 0;
  virtual ~CalExpression() {
    delete lhs;
    delete rhs;
  }
};
class PlusExpression : public CalExpression {
 public:
 PlusExpression(Expression *ls, Expression *rs) : CalExpression('+',ls,rs) {}
  std::string toString() {
    return CalExpression::toString();
  }
  long evaluate() const {return lhs->evaluate() + rhs->evaluate();}
  ~PlusExpression() {}
};

class MinusExpression : public CalExpression {
 public:
 MinusExpression(Expression *ls, Expression *rs) : CalExpression('-',ls,rs) {}
  std::string toString() {
    return CalExpression::toString();
  }
    long evaluate() const {return lhs->evaluate() - rhs->evaluate();}
  ~MinusExpression() {}
};

class TimesExpression : public CalExpression {
 public:
 TimesExpression(Expression *ls, Expression *rs) : CalExpression('*',ls,rs) {}
  std::string toString() {
    return CalExpression::toString();
  }
    long evaluate() const {return lhs->evaluate() * rhs->evaluate();}
  ~TimesExpression() {}
};

class DivExpression : public CalExpression {
 public:
 DivExpression(Expression *ls, Expression *rs) : CalExpression('/',ls,rs) {}
  std::string toString() {
    return CalExpression::toString();
  }
    long evaluate() const {return lhs->evaluate() / rhs->evaluate();}
  ~DivExpression() {}
};
