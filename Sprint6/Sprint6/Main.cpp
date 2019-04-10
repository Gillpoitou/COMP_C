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

typedef enum
{
      COMPILO,
      OPT,
      STATIC_ANALYSE,
      ASM,
      AST
} options;

string optionsNames[] = {"Sprint6/compilo", "-o", "-a", "-c", "-s"};

string printUsage()
{
      string result = "\nusage: ";
      result += "compilo <source_filename> ";
      result += "[OPTIONS] \n\n";

      result += " OPTIONS : \n";
      result += "           -a : Make a static analyse of the prog \n";
      result += "           -o : Use optimization for the analyse  \n";
      result += "           -c <output_filename> : Generate assembler code in the output_filename \n";
      result += "           -s : Print the AST result (debug) \n";

      return result;
}

string getExtension(string file)
{
      string ext = " ";
      if (file.find_last_of(".") != string::npos)
      {
            ext = file.substr(file.find_last_of("."), string::npos);
      }
      return ext;
}

int main(int argc, char *argv[])
{
      bool optionsValues[5] = {false};
      string inputFilename;
      string outputFilename;

      if (argc < 2)
      {
            cerr << printUsage() << endl;
            exit(1);
      }
      else
      {
            for (int i = 0; i < argc; i++)
            {
                  if (optionsNames[COMPILO].compare(argv[i]) == 0)
                  {
                        if (i + 1 < argc && (getExtension(argv[i + 1]).compare(".c") == 0 || getExtension(argv[i + 1]).compare(".txt") == 0))
                        {
                              optionsValues[COMPILO] = true;
                              inputFilename = argv[++i];
                              // cout << "input filename : " << inputFilename << endl;
                        }
                        else
                        {
                              cerr << "Source file extension must be .c or .txt" << endl;
                              exit(1);
                        }
                  }
                  else if (optionsNames[ASM].compare(argv[i]) == 0)
                  {
                        if (i + 1 < argc && (getExtension(argv[i + 1]).compare(".asm") == 0 || getExtension(argv[i + 1]).compare(".s") == 0))
                        {
                              optionsValues[ASM] = true;
                              outputFilename = argv[++i];
                              // cout << "output filename : " << outputFilename << endl;
                        }
                        else
                        {
                              cerr << "Output file extension must be .asm or .s" << endl;
                              exit(1);
                        }
                  }
                  else if (optionsNames[OPT].compare(argv[i]) == 0)
                  {
                        optionsValues[OPT] = true;
                        // cout << "OPT" << endl;
                        cout << "Optimization is not implemented : ignored" << endl;
                  }
                  else if (optionsNames[STATIC_ANALYSE].compare(argv[i]) == 0)
                  {
                        optionsValues[STATIC_ANALYSE] = true;
                        // cout << "STATIC" << endl;
                  }
                  else if (optionsNames[AST].compare(argv[i]) == 0)
                  {
                        optionsValues[AST] = true;
                        // cout << "AST" << endl;
                  }
            }
      }

      // Reading source file
      ifstream myfile(inputFilename);

      string content = "";
      string line;

      if (myfile.is_open())
      {
            while (getline(myfile, line))
            {
                  content += line + '\n';
            }
            myfile.close();
      }
      else
      {
            cout << "Unable to open source file " << inputFilename << endl;
            exit(1);
      }

      //Lexical analyse
      ANTLRInputStream input(content);
      Grammar4Lexer lexer(&input);
      CommonTokenStream tokens(&lexer);
      Grammar4Parser parser(&tokens);
      tree::ParseTree *tree = parser.prog();

      //Visitor & AST
      Visitor visitor(optionsValues[STATIC_ANALYSE]);
      Prog *result = (Prog *)visitor.visit(tree);

      // Print AST
      if(optionsValues[AST]){
            cout << "Result : \n" << result->toString() << endl;
      }

      // Generate ASM
      if(optionsValues[ASM]){
            ofstream asmFile(outputFilename, std::ofstream::out);
            result->build_ASM(asmFile);
            cout << "Build success : ASM generated" << endl;
      }

      return 0;
}