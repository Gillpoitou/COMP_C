#include "SymbolTable.h"
#include "iostream"

SymbolTable::SymbolTable()
{
      Stable *table = new Stable();
      this->symbolTables = new stack<Stable *>();
      this->symbolTables->push(table);
      this->currentTable = table;
}

//Add a var to the current sylbolTable. Return true if the variable has been added. Return false if variable already exists
bool SymbolTable::addVar(string name, Type type)
{
      if (this->currentTable->find(name) != currentTable->end())
      {
            return false;
      }
      else
      {
            this->currentTable->insert(pair<string, Symbol *>(name, new Symbol(name, type)));
            return true;
      }
}

//Add a new function.
//Create a new symbolTable for the function and add in this table all the symbols of the current context (for global var)
bool SymbolTable::addFunction(string name, Type type)
{
      if (this->currentTable->find(name) != currentTable->end())
      {
            return false;
      }
      else
      {
            //Create new context (new symbolTable)
            Stable *table = new Stable();

            //Add the function symbol to current context
            this->currentTable->insert(pair<string, Symbol *>(name, new Symbol(name, type)));

            //Insert all current symbols in the new context
            table->insert(this->currentTable->begin(), this->currentTable->end());

            //Change current context
            this->symbolTables->push(table);
            this->currentTable = table;

            return true;
      }
}

//Function called at the end of a function definition => back to the previous context
void SymbolTable::functionEnd()
{
      this->symbolTables->pop();
      this->currentTable = this->symbolTables->top();
}

//Get a symbol int he current symbolTable. If doesn't exists, return nullptr.
Symbol *SymbolTable::getSymbol(string name)
{
      if (this->currentTable->find(name) == currentTable->end())
      {
            return nullptr;
      }
      else
      {
            return this->currentTable->find(name)->second;
      }
}

//Print the curent table (util for debug)
void SymbolTable::print()
{
      string result = "";

      for (Stable::iterator it = currentTable->begin(); it != currentTable->end(); ++it)
      {
            result += "element : name(" + it->second->name + ")\n";
      }

      cout << result << endl;
}