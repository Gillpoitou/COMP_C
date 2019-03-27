#include "Statement.h"
#include "Expression.h"

string StatementReturn::toString(){
            	return "Return = { value : " + value->toString() + " }\n";
}