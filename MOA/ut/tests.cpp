#include <gtest/gtest.h>
#include <string>
#include <tuple>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using namespace std;

using mapping2dto3dEntry = pair<tuple<int, int>, tuple<double, double, double>>;

using mapping2dto3d = vector<mapping2dto3dEntry>;

tuple<int, int> get2dCoordinates(ptree::value_type const &entry) {
  int x2d = entry.second.get<int>("2d-X");
  int y2d = entry.second.get<int>("2d-Y");
  return make_tuple(x2d, y2d);
}

mapping2dto3d getMapping(istream &jsonInput);
mapping2dto3d getMapping(istream &jsonInput) {
  mapping2dto3d answer;
  ptree tree;
  read_json(jsonInput, tree);
  for (const auto &mapping : tree.get_child("mapping")) {
    auto coordinates2d = get2dCoordinates(mapping);
    int x3d = mapping.second.get<int>("3d-X");
    int y3d = mapping.second.get<int>("3d-Y");
    int z3d = mapping.second.get<int>("3d-Z");
    get2dCoordinates(mapping);
    answer.emplace_back(make_pair(coordinates2d, make_tuple(x3d, y3d, z3d)));
  }
  return answer;
}
TEST(Mapping, EmptyMapping) {
  // Arrange
  const string emptyMappingString = "{  \"mapping\":[] }";
  stringstream emptyMappingStream;
  emptyMappingStream << emptyMappingString;

  // Act
  auto mapping = getMapping(emptyMappingStream);

  // Assert
  ASSERT_EQ(0, mapping.size());
}

TEST(Mapping, BasicMapping) {
  // Arrange
  const string basicMappingString =
      string("{                                        ") +
      "           \"mapping\":                         "
      "           [                                    "
      "               {                                "
      "                   \"2d-X\": \"9\",             "
      "                   \"2d-Y\": \"6\",             "
      "                   \"3d-X\": \"1\",             "
      "                   \"3d-Y\": \"2\",             "
      "                   \"3d-Z\": \"3\"              "
      "               }                                "
      "           ]                                    "
      "       }                                        ";
  stringstream basicMappingStream;
  basicMappingStream << basicMappingString;

  // Act
  const auto mapping = getMapping(basicMappingStream);

  // Assert
  ASSERT_EQ(make_tuple(9, 6), mapping[0].first);
  ASSERT_EQ(make_tuple(1.0, 2.0, 3.0), mapping[0].second);
}
