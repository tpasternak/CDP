#include <gtest/gtest.h>
#include <string>
#include <tuple>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using namespace std;

using mapping2dto3d =
    vector<pair<tuple<int, int>, tuple<double, double, double>>>;

mapping2dto3d getMapping(const string &jsonInput) {
  decltype(getMapping("")) answer;
  stringstream ss;
  ptree tree;
  ss << jsonInput;
  read_json(ss, tree);
  for (const auto &mapping : tree.get_child("mapping")) {
    int x2d = mapping.second.get<int>("2d-X");
    int y2d = mapping.second.get<int>("2d-Y");
    int x3d = mapping.second.get<int>("3d-X");
    int y3d = mapping.second.get<int>("3d-Y");
    int z3d = mapping.second.get<int>("3d-Z");
    answer.emplace_back(
        make_pair(make_tuple(x2d, y2d), make_tuple(x3d, y3d, z3d)));
  }

  return answer;
}
TEST(Mapping, EmptyMapping) {
  // Arrange
  const string emptyMappingString = "{  \"mapping\":[] }";

  // Act
  auto mapping = getMapping(emptyMappingString);

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
  stringstream basicMappingSream;
  basicMappingSream << basicMappingString;

  // Act
  const auto mapping = getMapping(basicMappingString);

  // Assert
  ASSERT_EQ(make_tuple(9, 6), mapping[0].first);
  ASSERT_EQ(make_tuple(1.0, 2.0, 3.0), mapping[0].second);
}
