#include <iostream>
#include "antlr4-runtime.h"
#include "Sprint1Lexer.h"

#include "Sprint1Parser.h"
#include "Sprint1BaseVisitor.h"
#include "Visitor.h"

#include <iostream>
#include <fstream>
using namespace antlr4;
using namespace std;

int main(int, const char **)
{
      ANTLRInputStream input("int main() {return 43;}");
      Sprint1Lexer lexer(&input);
      CommonTokenStream tokens(&lexer);
      Sprint1Parser parser(&tokens);
      tree::ParseTree *tree = parser.prog();
      Visitor visitor;
      int resultat = (int)visitor.visit(tree);
      cout << "Résultat " << resultat << endl;
      return 0;
}