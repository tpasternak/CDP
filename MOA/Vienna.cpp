#include <viennacl/matrix.hpp>
#include <viennacl/ocl/context.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using cv::Mat;

class TimeCount {
  using hrc = std::chrono::high_resolution_clock;
  using time = decltype(hrc::now());
  time begin = hrc::now();

public:
  ~TimeCount() {
    auto end = hrc::now();
    std::cout << "================" << endl << (end - begin).count() << endl
              << "================" << std::endl;
  }
};

int fun(Mat &mat) {
  {
    TimeCount{};
    viennacl::matrix<float> m(10000, 1);
    for (int x = 0; x < 10000; ++x) {
      m(x, 0) = 22.0;
    }
  }
  {
    TimeCount{};
    std::vector<float> v(10000);
    for (int x = 0; x < 10000; ++x) {
      v[x] = 22.0;
    }
  }

  auto ctx = viennacl::ocl::current_context();
  return 0;
}
