#include <limits>
#include <iostream>
#include "commands.hpp"
#include "DictionaryCollection.hpp"

int main()
{
  using namespace shabalin;

  DictionaryCollection collection{};
  CommandTable commands;
  getCommands(commands, collection);
  std::string command;
  while (!(std::cin >> command).eof())
  {
    try
    {
      commands.at(command)();
    }
    catch (const std::exception &e)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << "<INVALID COMMAND>\n";
      std::cout << e.what();
    }
  }
}
