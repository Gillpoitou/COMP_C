#include <iostream>
#include "antlr4-runtime.h"
#include "Grammar3Lexer.h"

#include "Grammar3Parser.h"
#include "Grammar3BaseVisitor.h"
#include "Visitor.h"

// #include "Function.h"

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

            //cout << "1" << endl;
            ANTLRInputStream input(content);
            Grammar3Lexer lexer(&input);
            CommonTokenStream tokens(&lexer);
            Grammar3Parser parser(&tokens);
            tree::ParseTree *tree = parser.prog();
            // cout << tree->toStringTree() << endl;
            Visitor visitor;
            // cout << "2" << endl;
            Function *result = (Function *)visitor.visit(tree);
            //cout << "3" << endl;
            cout << result->toString() << endl;
            // int resultat = (int)visitor.visit(tree);
            // cout << "Résultat " << resultat << endl;
      }

      else
            cout << "Unable to open file" << endl;

      return 0;
}
