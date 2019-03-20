#include <iostream>
#include "antlr4-runtime.h"
#include "Grammar1Lexer.h"

#include "Grammar1Parser.h"
#include "Grammar1BaseVisitor.h"
#include "Visitor.h"

#include <iostream>
#include <fstream>
using namespace antlr4;
using namespace std;

int main(int argc, char *argv[])
{
      string content = "";
      string line;
      ifstream myfile(argv[1]);
      if (myfile.is_open())
      {
            while (getline(myfile, line))
            {
                  content += line + '\n';
            }
            myfile.close();

            ANTLRInputStream input(content);
            Grammar1Lexer lexer(&input);
            CommonTokenStream tokens(&lexer);
            Grammar1Parser parser(&tokens);
            tree::ParseTree *tree = parser.prog();
            Visitor visitor;
            int resultat = (int)visitor.visit(tree);
            cout << "Résultat " << resultat << endl;
      }

      else
            cout << "Unable to open file" << endl;

      return 0;
}