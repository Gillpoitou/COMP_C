#include <iostream>
#include "antlr4-runtime.h"
#include "Grammar4Lexer.h"

#include "Grammar4Parser.h"
#include "Grammar4BaseVisitor.h"
#include "Visitor.h"
#include "Prog.h"

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
            Grammar4Lexer lexer(&input);
            CommonTokenStream tokens(&lexer);
            Grammar4Parser parser(&tokens);
            tree::ParseTree *tree = parser.prog();
            Visitor visitor;
            Prog* result = (Prog *)visitor.visit(tree);
            cout << "Résultat " << result->toString() << endl;
            result->build_ASM(asmFile);
            cout << "build success ASM generated" << endl;
      }

      else
            cout << "Unable to open file" << endl;

      return 0;
}
