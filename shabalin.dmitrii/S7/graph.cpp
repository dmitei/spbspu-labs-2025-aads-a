#include "graph.hpp"
#include <algorithm>

void shabalin::Graph::addVertex(const Vertex& v)
{
  vertices.insert(std::make_pair(v, true));
}

void shabalin::Graph::addEdge(const Vertex& from, const Vertex& to, Weight weight)
{
  addVertex(from);
  addVertex(to);
  Edge edge = std::make_pair(from, to);
  auto it = edges.find(edge);
  if (it != edges.end())
  {
    it->second.push_back(weight);
  }
  else
  {
    WeightsList weights;
    weights.push_back(weight);
    edges.insert(std::make_pair(edge, weights));
  }
}

bool shabalin::Graph::hasVertex(const Vertex& v) const
{
  return vertices.find(v) != vertices.cend();
}

bool shabalin::Graph::hasEdge(const Vertex& from, const Vertex& to, Weight weight) const
{
  Edge edge = std::make_pair(from, to);
  auto it = edges.find(edge);
  if (it != edges.cend())
  {
    for (auto wit = it->second.cbegin(); wit != it->second.cend(); ++wit)
    {
      if (*wit == weight)
      {
        return true;
      }
    }
  }
  return false;
}

void shabalin::Graph::removeEdge(const Vertex& from, const Vertex& to, Weight weight)
{
  Edge edge = std::make_pair(from, to);
  auto it = edges.find(edge);
  if (it != edges.end())
  {
    it->second.remove(weight);
    if (it->second.empty())
    {
      edges.erase(edge);
    }
  }
}

shabalin::Tree< std::string, shabalin::Graph::WeightsList, std::less< std::string > > shabalin::Graph::getOutbound(const Vertex& from) const
{
  Tree< Vertex, WeightsList, std::less< std::string > > result;
  for (auto eit = edges.cbegin(); eit != edges.cend(); ++eit)
  {
    if (eit->first.first == from)
    {
      WeightsList sorted = eit->second;
      result.insert(std::make_pair(eit->first.second, sorted));
    }
  }
  return result;
}

shabalin::Tree< std::string, shabalin::Graph::WeightsList, std::less< std::string > > shabalin::Graph::getInbound(const Vertex& to) const
{
  Tree< Vertex, WeightsList, std::less< std::string > > result;
  for (auto eit = edges.cbegin(); eit != edges.cend(); ++eit)
  {
    if (eit->first.second == to)
    {
      WeightsList sorted = eit->second;
      result.insert(std::make_pair(eit->first.first, sorted));
    }
  }
  return result;
}

shabalin::List< shabalin::Graph::Vertex > shabalin::Graph::getVertices() const
{
  List< Vertex > result;
  for (auto vit = vertices.cbegin(); vit != vertices.cend(); ++vit)
  {
    result.push_back(vit->first);
  }
  return result;
}

size_t shabalin::Graph::vertexCount() const
{
  return vertices.size();
}

const shabalin::HashTable< shabalin::Graph::Edge, shabalin::Graph::WeightsList, shabalin::EdgeHash >& shabalin::Graph::getAllEdges() const
{
  return edges;
}

