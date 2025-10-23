#include "commands.hpp"
#include <string>
#include <fstream>
#include "../common/container.hpp"

void shabalin::printDict(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName;
  in >> dictName;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  auto dictIt = dicts.find(dictName);
  if (dictIt == dicts.end())
  {
    out << "The dictionary with name " << dictName << " doesn't exist.\n";
    return;
  }
  const Dict & dict = dictIt->second;
  if (dict.empty())
  {
    out << dictName << " is empty.\n";
    return;
  }
  for (auto it = dict.cbegin(); it != dict.cend(); ++it)
  {
    out << it->first << " -";
    const Container & translations = it->second;
    for (std::size_t i = 0; i < translations.size(); ++i)
    {
      out << " " << translations[i];
    }
    out << "\n";
  }
}

void shabalin::addWord(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName, word, translation;
  in >> dictName >> word >> translation;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  auto dictIt = dicts.find(dictName);
  if (dictIt == dicts.end())
  {
    out << "The dictionary with name " << dictName << " doesn't exist.\n";
    return;
  }
  Dict & dict = dictIt->second;
  auto wordIt = dict.find(word);
  if (wordIt != dict.end())
  {
    Container & translations = wordIt->second;
    for (std::size_t i = 0; i < translations.size(); ++i)
    {
      if (translations[i] == translation)
      {
        out << "The word " << word << " already exists in " << dictName << "\n";
        return;
      }
    }
    translations.push_back(translation);
    return;
  }
  Container translations;
  translations.push_back(translation);
  dict.insert(word, translations);
}

void shabalin::translateWord(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName, word;
  in >> dictName >> word;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  auto dictIt = dicts.find(dictName);
  if (dictIt == dicts.end())
  {
    out << "The dictionary with name " << dictName << " doesn't exist.\n";
    return;
  }
  const Dict & dict = dictIt->second;
  auto wordIt = dict.find(word);
  if (wordIt == dict.cend())
  {
    out << "The word " << word << " doesn't exist in " << dictName << "\n";
    return;
  }
  const Container & translations = wordIt->second;
  for (std::size_t i = 0; i < translations.size(); ++i)
  {
    out << translations[i];
    if (i + 1 < translations.size())
    {
      out << " ";
    }
  }
  out << "\n";
}

void shabalin::removeWord(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName, word;
  in >> dictName >> word;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  auto dictIt = dicts.find(dictName);
  if (dictIt == dicts.end())
  {
    out << "The dictionary with name " << dictName << " doesn't exist.\n";
    return;
  }
  Dict & dict = dictIt->second;
  auto wordIt = dict.find(word);
  if (wordIt == dict.end())
  {
    out << "The word " << word << " doesn't exist in " << dictName << "\n";
    return;
  }
  dict.erase(wordIt);
  out << "The word " << word << " successfully deleted from " << dictName << "\n";
}

void shabalin::createDict(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string name;
  in >> name;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  if (dicts.find(name) != dicts.end())
  {
    out << "The dictionary with name " << name << " already exists.\n";
    return;
  }
  Dict dict;
  dicts.insert(name, dict);
  out << name << " is successfully created.\n";
}

void shabalin::saveToFile(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName, fileName;
  in >> dictName >> fileName;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  if (fileName.size() < 4 || fileName.substr(fileName.size() - 4) != ".txt")
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  auto dictIt = dicts.find(dictName);
  if (dictIt == dicts.end())
  {
    out << "The dictionary with name " << dictName << " doesn't exist.\n";
    return;
  }
  std::ofstream file(fileName);
  if (!file)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  file << dictName << "\n";
  const Dict & dict = dictIt->second;
  for (auto it = dict.cbegin(); it != dict.cend(); ++it)
  {
    file << it->first << " -";
    const Container & translations = it->second;
    for (std::size_t i = 0; i < translations.size(); ++i)
    {
      file << " " << translations[i];
    }
    file << "\n";
  }
}

void shabalin::combineDicts(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string newName, dict1Name, dict2Name;
  in >> newName >> dict1Name >> dict2Name;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  if (dicts.find(newName) != dicts.end())
  {
    out << "The dictionary with name " << newName << " already exists.\n";
    return;
  }
  auto it1 = dicts.find(dict1Name);
  auto it2 = dicts.find(dict2Name);
  if (it1 == dicts.end() || it2 == dicts.end())
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  const Dict & dict1 = it1->second;
  const Dict & dict2 = it2->second;
  Dict result;
  for (auto it = dict1.cbegin(); it != dict1.cend(); ++it)
  {
    result.insert(it->first, it->second);
  }
  for (auto it = dict2.cbegin(); it != dict2.cend(); ++it)
  {
    auto resIt = result.find(it->first);
    if (resIt == result.end())
    {
      result.insert(it->first, it->second);
    }
    else
    {
      Container merged = resIt->second;
      const Container & addTr = it->second;
      for (std::size_t i = 0; i < addTr.size(); ++i)
      {
        bool found = false;
        for (std::size_t j = 0; j < merged.size(); ++j)
        {
          if (merged[j] == addTr[i])
          {
            found = true;
            break;
          }
        }
        if (!found)
        {
          merged.push_back(addTr[i]);
        }
      }
      result.erase(resIt);
      result.insert(it->first, merged);
    }
  }
  dicts.insert(newName, result);
  out << "Dictionary " << newName << " is successfully created\n";
}

void shabalin::deleteWord(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName;
  in >> dictName;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  auto it = dicts.find(dictName);
  if (it == dicts.end())
  {
    out << "The dictionary with name " << dictName << " doesn't exist.\n";
    return;
  }
  dicts.erase(it);
}

void shabalin::editTranslation(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string dictName, word, newTranslation;
  in >> dictName >> word >> newTranslation;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  auto dictIt = dicts.find(dictName);
  if (dictIt == dicts.end())
  {
    out << "The dictionary with name " << dictName << " doesn't exist.\n";
    return;
  }
  Dict & dict = dictIt->second;
  auto wordIt = dict.find(word);
  if (wordIt == dict.end())
  {
    out << "The word " << word << " doesn't exist in " << dictName << "\n";
    return;
  }
  wordIt->second.clear();
  wordIt->second.push_back(newTranslation);
}

void shabalin::renameDict(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string oldName, newName;
  in >> oldName >> newName;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  auto oldIt = dicts.find(oldName);
  if (oldIt == dicts.end())
  {
    out << "The dictionary with name " << oldName << " doesn't exist.\n";
    return;
  }
  if (dicts.find(newName) != dicts.end())
  {
    out << "The dictionary with name " << newName << " already exists.\n";
    return;
  }
  Dict dictCopy = oldIt->second;
  dicts.erase(oldIt);
  dicts.insert(newName, dictCopy);
}

void shabalin::moveCommand(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string fromDict, toDict, word;
  in >> fromDict >> toDict >> word;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  auto fromIt = dicts.find(fromDict);
  if (fromIt == dicts.end())
  {
    out << "The dictionary with name " << fromDict << " doesn't exist.\n";
    return;
  }
  auto toIt = dicts.find(toDict);
  if (toIt == dicts.end())
  {
    out << "The dictionary with name " << toDict << " doesn't exist.\n";
    return;
  }
  Dict & from = fromIt->second;
  Dict & to = toIt->second;
  auto wordIt = from.find(word);
  if (wordIt == from.end())
  {
    out << "The word " << word << " doesn't exist in " << fromDict << "\n";
    return;
  }
  if (to.find(word) != to.end())
  {
    out << "The word " << word << " already exists in " << toDict << "\n";
    return;
  }
  Container copyArr = wordIt->second;
  to.insert(word, copyArr);
  from.erase(wordIt);
  out << "The word " << word << " moved from " << fromDict << " to " << toDict << "\n";
}

void shabalin::copyCommand(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string fromDict, toDict, word;
  in >> fromDict >> toDict >> word;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  auto fromIt = dicts.find(fromDict);
  if (fromIt == dicts.end())
  {
    out << "The dictionary with name " << fromDict << " doesn't exist.\n";
    return;
  }
  auto toIt = dicts.find(toDict);
  if (toIt == dicts.end())
  {
    out << "The dictionary with name " << toDict << " doesn't exist.\n";
    return;
  }
  const Dict & from = fromIt->second;
  Dict & to = toIt->second;
  auto wordIt = from.find(word);
  if (wordIt == from.cend())
  {
    out << "The word " << word << " doesn't exist in " << fromDict << "\n";
    return;
  }
  if (to.find(word) != to.end())
  {
    out << "The word " << word << " already exists in " << toDict << "\n";
    return;
  }
  Container copyCon = wordIt->second;
  to.insert(word, copyCon);
  out << "The word " << word << " copied from " << fromDict << " to " << toDict << "\n";
}

void shabalin::common(Dicts & dicts, std::istream & in, std::ostream & out)
{
  std::string newName, dict1Name, dict2Name;
  in >> newName >> dict1Name >> dict2Name;
  if (!in)
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  if (dicts.find(newName) != dicts.end())
  {
    out << "The dictionary with name " << newName << " already exists.\n";
    return;
  }
  auto it1 = dicts.find(dict1Name);
  auto it2 = dicts.find(dict2Name);
  if (it1 == dicts.end() || it2 == dicts.end())
  {
    out << "<WRONG COMMAND>\n";
    return;
  }
  const Dict & dict1 = it1->second;
  const Dict & dict2 = it2->second;
  Dict result;
  for (auto wit = dict1.cbegin(); wit != dict1.cend(); ++wit)
  {
    if (dict2.find(wit->first) != dict2.cend())
    {
      result.insert(wit->first, wit->second);
    }
  }
  dicts.insert(newName, result);
  out << "Dictionary " << newName << " is successfully created\n";
}

void shabalin::importDictfromFile(Dicts & dicts, const std::string & filename)
{
  std::ifstream file(filename);
  if (!file)
  {
    throw std::runtime_error("Cannot open file\n");
  }
  std::string line;
  std::string dictName;
  Dict dict;
  bool hasDict = false;
  while (std::getline(file, line))
  {
    if (line.empty())
    {
      continue;
    }
    if (line.find(" - ") == std::string::npos)
    {
      if (hasDict)
      {
        dicts.insert(dictName, dict);
        dict = Dict();
      }
      dictName = line;
      hasDict = true;
    }
    else
    {
      std::size_t dashPos = line.find(" - ");
      if (dashPos == std::string::npos)
      {
        continue;
      }
      std::string word = line.substr(0, dashPos);
      std::string translationsStr = line.substr(dashPos + 3);
      Container translations;
      std::size_t start = 0;
      std::size_t end = translationsStr.find(' ');
      while (end != std::string::npos)
      {
        std::string translation = translationsStr.substr(start, end - start);
        if (!translation.empty())
        {
          translations.push_back(translation);
        }
        start = end + 1;
        end = translationsStr.find(' ', start);
      }
      std::string lastTranslation = translationsStr.substr(start);
      if (!lastTranslation.empty())
      {
        translations.push_back(lastTranslation);
      }
      dict.insert(word, translations);
    }
  }
  if (hasDict)
  {
    dicts.insert(dictName, dict);
  }
}

void shabalin::listDicts(Dicts & dicts, std::istream &, std::ostream & out)
{
  if (dicts.empty())
  {
    out << "No dictionaries available.\n";
    return;
  }
  out << "Available dictionaries:\n";
  for (auto it = dicts.cbegin(); it != dicts.cend(); ++it)
  {
    out << "- " << it->first << "\n";
  }
}

void shabalin::printHelp(std::ostream & out)
{
  out << "Commands list:\n";
  out << "1) create <dict> - Create a new dictionary\n";
  out << "2) add <dict> <key> <translation> - Add a word/translation to dictionary\n";
  out << "3) translate <dict> <key> - Output all translations for a word\n";
  out << "4) remove <dict> <key> - Delete a word from the dictionary\n";
  out << "5) print <dict> - Show all words and translations from a dictionary\n";
  out << "6) save <dict> <filename> - Save dictionary to file\n";
  out << "7) combine <newdict> <dict1> <dict2> - Merge two dictionaries into a new one\n";
  out << "8) delete <dict> - Delete a dictionary\n";
  out << "9) edit <dict> <key> <translation> - Edit translations for a word\n";
  out << "10) rename <dict> <newname> - Rename a dictionary\n";
  out << "11) move <from> <to> <key> - Move word (with translations) to another dictionary\n";
  out << "12) copy <from> <to> <key> - Copy word (with translations) to another dictionary\n";
  out << "13) common <newdict> <dict1> <dict2> - Add common words of both to a new dictionary\n";
  out << "14) list - show list of available dictionaries\n";
  out << "\n";
}
