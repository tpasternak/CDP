#include <algorithm>
#include <fstream>
#include <iterator>

#include "Mapping.h"
#include "Calibration.h"
#include "FileVideo.h"
#include "Vienna.h"

#include <boost/program_options.hpp>

using namespace moa::mappings;
using namespace std;
using namespace cv;

tuple<Mat, Mat> extrinisicParams(tuple<Mat, Mat> const &calibParams,
                                 mapping2dto3d const &mapping) {
  vector<Point2f> points2d;
  transform(
      begin(mapping), end(mapping), back_inserter(points2d),
      [](remove_reference<decltype(mapping)>::type::value_type const &elem)
          -> Point2f {
        return {static_cast<float>(get<0>(elem.first)),
                static_cast<float>(get<1>(elem.first))};
      });
  vector<Point3f> points3d;
  transform(
      begin(mapping), end(mapping), back_inserter(points3d),
      [](remove_reference<decltype(mapping)>::type::value_type const &elem)
          -> Point3f {
        return {static_cast<float>(get<0>(elem.second)),
                static_cast<float>(get<1>(elem.second)),
                static_cast<float>(get<2>(elem.second))

        };
      });
  Mat rvec, tvec;
  solvePnP(points3d, points2d, get<0>(calibParams), get<1>(calibParams), rvec,
           tvec, false, CV_ITERATIVE);
  return make_tuple(rvec, tvec);
}

namespace po = boost::program_options;
po::variables_map setupOptions(int ac, char **av) {
  po::options_description desc("OPTIONS:");
  po::positional_options_description pod;
  pod.add("mapping", 1);
  pod.add("video", 2);
  pod.add("background", 3);
  pod.add("calibration", 4);

  desc.add_options()("help,h", "Print this message")(
      "video,v", po::value<string>(), "Video File (.wmv)")(
      "mapping,m", po::value<string>(), "Mapping JSON file")(
      "background,b", po::value<string>(),
      "Background image file")("calibration,c", po::value<string>(),
                               "Intrinisic calibration parameters file");

  po::variables_map vm;
  po::store(po::command_line_parser(ac, av).options(desc).positional(pod).run(),
            vm);
  po::notify(vm);
  if (vm.count("help")) {
    std::cout << "OVERVIEW: Morphological Operations App" << endl << endl;
    std::cout
        << "USAGE: moa [options] <mapping> <video> <background> <calibration>"
        << std::endl << endl;
    cout << desc << "\n";
  }
  return vm;
}

int main(int ac, char **argv) {
  auto vm = setupOptions(ac, argv);
  std::fstream mappingFile;


  cout << "Video File       : " << vm["video"].as<string>() << endl;
  cout << "Mapping File     : " << vm["mapping"].as<string>() << endl;
  cout << "Background File  : " << vm["background"].as<string>() << endl;
  cout << "Calibration File : " << vm["calibration"].as<string>() << endl;

  FileVideo fv(vm["video"].as<string>());
  fv.Start();
  auto file = fv.Get();

  mappingFile.open(vm["mapping"].as<string>());
  auto mapping = getMapping(mappingFile);
  //  auto calibParams = readCalibParams("CalibrationParams.yml");
  //  auto extParams = extrinisicParams(calibParams, mapping);
  
  imshow( "Display window", file);
  fun(file);
  waitKey(0); 

}
