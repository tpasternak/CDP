#pragma once

#include <vector>
#include <istream>
namespace moa {
namespace mappings {

using mapping2dto3dEntry =
    std::pair<std::tuple<int, int>, std::tuple<double, double, double>>;
using mapping2dto3d = std::vector<mapping2dto3dEntry>;

mapping2dto3d getMapping(std::istream &jsonInput);
}
}
