#include "Statement.h"
#include "Expression.h"

string Statement::toString()
{
      return "Statement = { right : " + right->toString() + ", left : " + left->toString() + "\n";
}

string StatementReturn::toString()
{
      return "Return = { value : " + value->toString() + " }\n";
}