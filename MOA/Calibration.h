#include <vector>
#include <tuple>
#include <memory>
#include <opencv2/opencv.hpp>

class IImageSource;
std::vector<cv::Point3f> getPatternPoints(cv::Mat pattern,
                                          cv::Size patternSize);
std::vector<cv::Point2f> getImageCornerPoints(cv::Mat image,
                                              cv::Size patternSize);

std::tuple<cv::Mat, cv::Mat>
getCalibParams(const std::vector<std::vector<cv::Point2f> > &imagePoints,
               cv::Mat pattern, cv::Size patternSize, cv::Size imageSize);

void saveParams(std::tuple<cv::Mat, cv::Mat> params,
                const cv::string &fileName);

std::vector<decltype(getImageCornerPoints(cv::Mat(), cv::Size(1, 1)))>
getPointsToCalibration(const std::unique_ptr<IImageSource> &source,
                       unsigned maxSize);
std::tuple<cv::Mat, cv::Mat>
getCalibParams(const std::unique_ptr<IImageSource> &source, cv::Mat pattern);
std::tuple<cv::Mat, cv::Mat> readCalibParams(const std::string &fileName);
