#include "../common/container.hpp"
#include "../common/hashTable.hpp"

namespace shabalin
{
  using Dict = HashTable< std::string, Container >;
  using Dicts = HashTable< std::string, Dict >;
}

