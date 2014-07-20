#include <gtest/gtest.h>
#include <tuple>
#include "code.h"

using namespace std;
using namespace moa::mappings;
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
