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

            ANTLRInputStream input(content);
            Grammar2Lexer lexer(&input);
            CommonTokenStream tokens(&lexer);
            Grammar2Parser parser(&tokens);
            tree::ParseTree *tree = parser.prog();
            cout << tree->toStringTree() << endl;
            Visitor visitor;
            Function *result = (Function *)visitor.visit(tree);
            cout << result->toString() << endl;
            result->buildASM(asmFile);
            cout << "build success ASM generated" << endl;
      }

      else
            cout << "Unable to open file" << endl;

      return 0;
}
