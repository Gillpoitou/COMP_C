#include <iostream>
#include "antlr4-runtime.h"
#include "Grammar2Lexer.h"

#include "Grammar2Parser.h"
#include "Grammar2BaseVisitor.h"
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
      ofstream asmFile(argv[2], std::ofstream::out);
      if (myfile.is_open())
      {
            while (getline(myfile, line))
            {
                  content += line + '\n';
            }
            myfile.close();

            //cout << "1" << endl;
            ANTLRInputStream input(content);
            Grammar2Lexer lexer(&input);
            CommonTokenStream tokens(&lexer);
            Grammar2Parser parser(&tokens);
            tree::ParseTree *tree = parser.prog();
            cout << tree->toStringTree() << endl;
            Visitor visitor;
            //cout << "2" << endl;
            Function *result = (Function *)visitor.visit(tree);
            //cout << "3" << endl;
            cout << result->toString() << endl;
            // int resultat = (int)visitor.visit(tree);
            // cout << "Résultat " << resultat << endl;
            result->buildASM(asmFile);
            cout << "build success ASM generated" << endl;
      }

      else
            cout << "Unable to open file" << endl;

      return 0;
}
