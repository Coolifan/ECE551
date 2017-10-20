#include <string>
#include <sstream>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
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
  ~NumExpression() {}
};
class CalExpression : public Expression {
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
  ~PlusExpression() {}
};
