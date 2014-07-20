#include "code.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;

using namespace std;

namespace moa {
namespace mappings {

constexpr tuple<int, int> get2dCoordinates(ptree::value_type const &entry) {
  const int x = entry.second.get<int>("2d-X");
  const int y = entry.second.get<int>("2d-Y");
  return make_tuple(x, y);
}

constexpr tuple<int, int, int>
get3dCoordinates(ptree::value_type const &entry) {
  const int x = entry.second.get<int>("3d-X");
  const int y = entry.second.get<int>("3d-Y");
  const int z = entry.second.get<int>("3d-Z");
  return make_tuple(x, y, z);
}

mapping2dto3d getMapping(istream &jsonInput) {
  mapping2dto3d answer;
  ptree tree;
  read_json(jsonInput, tree);
  for (const auto &mapping : tree.get_child("mapping")) {
    const auto coordinates2d = get2dCoordinates(mapping);
    const auto coordinates3d = get3dCoordinates(mapping);
    answer.emplace_back(coordinates2d, coordinates3d);
  }
  return answer;
}
}
}
