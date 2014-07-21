#include "Calibration.h"
#include "IImageSource.h"
#include <functional>

using namespace std::placeholders;
using namespace cv;
using namespace std;

vector<Point3f> getPatternPoints(Mat pattern, Size patternSize) {
  vector<Point2f> points2f;
  findChessboardCorners(pattern, patternSize, points2f);
  vector<Point3f> answer;
  transform(points2f.begin(), points2f.end(), back_inserter(answer),
            [](Point2f point2f) { return Point3f(point2f); });
  return answer;
}

vector<Point2f> getImageCornerPoints(Mat image, Size patternSize) {
  vector<Point2f> imagePoints;
  findChessboardCorners(image, patternSize, imagePoints);
  return imagePoints;
}

tuple<Mat, Mat> getCalibParams(const vector<vector<Point2f> > &imagePoints,
                               Mat pattern, Size patternSize, Size imageSize) {
  const vector<vector<Point3f> > patternPoints(
      imagePoints.size(), getPatternPoints(pattern, patternSize));

  Mat cameraMatrix, distCoeffs;
  calibrateCamera(patternPoints, imagePoints, imageSize, cameraMatrix,
                  distCoeffs, noArray(), noArray(),
                  CALIB_FIX_K4 | CALIB_FIX_K5);
  return make_tuple(cameraMatrix, distCoeffs);
}

void saveParams(tuple<Mat, Mat> params, const string &fileName) {
  FileStorage fs(fileName, FileStorage::WRITE);
  fs << "radial" << get<0>(params);
  fs << "tangential" << get<1>(params);
}

vector<decltype(getImageCornerPoints(Mat(), Size(1, 1)))>
getPointsToCalibration(const unique_ptr<IImageSource> &source,
                       unsigned maxSize) {
  vector<decltype(getImageCornerPoints(Mat(), Size(1, 1)))> ans;
  source->Start();
  for (Mat im = source->Get(); !im.empty() && maxSize; im = source->Get()) {
    cvNamedWindow("Video1", 0);
    const auto size = Size(6, 8);
    const auto corners = getImageCornerPoints(im, size);
    if (static_cast<int>(corners.size()) == size.height * size.width) {
      --maxSize;
      ans.push_back(corners);
      cout << "FOUND POINTS: " << ans.size() << endl;
    }
    for (const auto &item : corners)
      circle(im, item, 10, Scalar(255, 0, 0), -1);
    imshow("Video1", im);
    cv::waitKey(2);
  }
  source->Stop();
  return ans;
}

tuple<Mat, Mat> getCalibParams(const unique_ptr<IImageSource> &source,
                               Mat pattern) {
  source->Start();
  auto imSize = source->Get().size();
  source->Stop();

  vector<decltype(getImageCornerPoints(Mat(), Size(1, 1)))> calibrationSets =
      getPointsToCalibration(source, 50);
  return getCalibParams(calibrationSets, pattern, Size(6, 8), imSize);
}

std::tuple<cv::Mat, cv::Mat> readCalibParams(const std::string &fileName) {
  FileStorage fs(fileName, FileStorage::READ);
  Mat radial, tangential;
  fs["radial"] >> radial;
  fs["tangential"] >> tangential;
  return make_tuple(radial, tangential);
}
