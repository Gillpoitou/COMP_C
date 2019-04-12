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
      ofstream asmFile(argv[2], std::ofstream::out);
      if (myfile.is_open())
      {
            while (getline(myfile, line))
            {
                  content += line + '\n';
            }
            myfile.close();
            ANTLRInputStream input(content);
            Grammar3Lexer lexer(&input);
            CommonTokenStream tokens(&lexer);
            Grammar3Parser parser(&tokens);
            tree::ParseTree *tree = parser.prog();
            Visitor visitor;
            Function *result = (Function *)visitor.visit(tree);
            cout << "Résultat " << result->toString() << endl;
            result->buildASM(asmFile);
            cout << "build success ASM generated" << endl;
            
      }

      else
            cout << "Unable to open file" << endl;

      return 0;
}
