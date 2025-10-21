#include "dictionary.hpp"
#include <ostream>
#include <stdexcept>

shabalin::Dictionary::Dictionary():
  dict_(HashTable< std::string, std::string >{})
{}

shabalin::Dictionary::Dictionary(const Dictionary &dict):
  dict_(HashTable< std::string, std::string >(dict.dict_))
{}

shabalin::Dictionary &shabalin::Dictionary::operator=(const Dictionary &dict)
{
  if (this != std::addressof(dict))
  {
    Dictionary tmp(dict);
    swap(tmp);
  }
  return *this;
}

void shabalin::Dictionary::addWord(const std::string &word, const std::string &trans)
{
  dict_.insert(word, trans);
}

void shabalin::Dictionary::deleteWord(const std::string &word)
{
  if (!dict_.erase(word))
  {
    throw std::logic_error("There is no such word\n");
  }
}

void shabalin::Dictionary::print(std::ostream &out) const noexcept
{
  for (auto it = dict_.cbegin(); it != dict_.cend(); ++it)
  {
    out << it->first << " : " << it->second << "\n";
  }
}

shabalin::Dictionary shabalin::Dictionary::setWithDict(const Dictionary &dict) const
{
  Dictionary res{};
  for (auto it = dict_.cbegin(); it != dict_.cend(); ++it)
  {
    if (dict.dict_.cfind(it->first) == dict.dict_.cend())
    {
      res.dict_.insert(it->first, it->second);
    }
  }
  for (auto it = dict.dict_.cbegin(); it != dict.dict_.cend(); ++it)
  {
    if (dict_.cfind(it->first) == dict_.cend())
    {
      res.dict_.insert(it->first, it->second);
    }
  }
  return res;
}

shabalin::Dictionary shabalin::Dictionary::intersectWithDict(const Dictionary &dict) const
{
  Dictionary res{};
  for (auto it = dict_.cbegin(); it != dict_.cend(); ++it)
  {
    if (dict.dict_.cfind(it->first) != dict.dict_.cend())
    {
      res.dict_.insert(it->first, it->second);
    }
  }
  return res;
}

shabalin::Dictionary shabalin::Dictionary::unionWithDict(const Dictionary &dict) const
{
  Dictionary res(*this);
  for (auto it = dict.dict_.cbegin(); it != dict.dict_.cend(); ++it)
  {
    if (res.dict_.find(it->first) == res.dict_.end())
    {
      res.dict_.insert(it->first, it->second);
    }
  }
  return res;
}

shabalin::Dictionary shabalin::Dictionary::diffDict(const Dictionary &dict) const
{
  Dictionary res{};
  for (auto it = dict_.cbegin(); it != dict_.cend(); ++it)
  {
    if (dict.dict_.cfind(it->first) == dict.dict_.cend())
    {
      res.dict_.insert(it->first, it->second);
    }
  }
  return res;
}

shabalin::Dictionary shabalin::Dictionary::mergeDict(const Dictionary &dict) const
{
  Dictionary res(*this);
  for (auto it = dict.dict_.cbegin(); it != dict.dict_.cend(); ++it)
  {
    if (res.dict_.find(it->first) == res.dict_.end())
    {
      res.dict_.insert(it->first, it->second);
    }
  }
  return res;
}

bool shabalin::Dictionary::empty() const noexcept
{
  return dict_.empty();
}

void shabalin::Dictionary::swap(Dictionary &dict) noexcept
{
  std::swap(dict_, dict.dict_);
}
