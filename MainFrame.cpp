#include "MainFrame.h"

#include <string>
#include <algorithm>
#include <memory>
using namespace std;

// WX
#include <wx/wfstream.h>
#include <wx/log.h>
#include <wx/filedlg.h>
#include <wx/dcclient.h>

// OPENCV
#include <opencv2/opencv.hpp>

// BOOST
#include <boost/iterator/counting_iterator.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

using cv::Mat;
using cv::Mat_;

inline Mat getImage(cv::VideoCapture &capture) {
  Mat mat;
  capture >> mat;
  return mat;
}

inline wxImage *getFirstFrame(string const &path) {
  cv::VideoCapture videoCapture(path);
  cv::Mat firstFrame = getImage(videoCapture);
  void *memory = ::operator new(firstFrame.cols * firstFrame.rows * 3);
  cv::Mat rgbMat(firstFrame.rows, firstFrame.cols, CV_8UC(3), memory);
  cv::cvtColor(firstFrame, rgbMat, CV_BGR2RGB);
  auto test = new wxImage(rgbMat.cols, rgbMat.rows, rgbMat.data, false);
  return test;
}

void MainFrame::onLoad(wxCommandEvent &) {

  wxFileDialog openFileDialog(this, _("Open XYZ file"), _(""), _(""),
                              _("WMV files (*.wmv)|*.wmv"),
                              wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if (openFileDialog.ShowModal() == wxID_CANCEL) {
    return;
  }
  wxFileInputStream input_stream(openFileDialog.GetPath());
  if (!input_stream.IsOk()) {
    return;
  };
  const string path = string(openFileDialog.GetPath().mb_str());
  loadVideo(path);
}

void MainFrame::loadVideo(string const &path) {
  const auto image = getFirstFrame(path);
  m_bitmap3->SetBitmap(*image);
  m_scrolledWindow2->FitInside();
}
#include <boost/algorithm/string.hpp>
void MainFrame::onSave(wxCommandEvent &) {
  wxFileDialog saveFileDialog(this, _("Open YML file"), _(""), _(""),
                              _("YML files (*.yml)|*.yml"), wxFD_SAVE);
  if (saveFileDialog.ShowModal() == wxID_CANCEL) {
    return;
  }
  wxFileInputStream input_stream(saveFileDialog.GetPath());
  if (!input_stream.IsOk()) {
    return;
  };
  const string path = string(saveFileDialog.GetPath().mb_str());
  const int size = m_grid2->GetNumberRows();

  std::ostringstream buf;
  ptree array, array_upper;
  ptree child1, child2;

  std::vector<std::string> strings2d;
  std::vector<std::string> strings3d;
  string cellValue2d = string(m_grid2->GetCellValue(0, 0));
  string cellValue3d = string(m_grid2->GetCellValue(0, 1));
  boost::split(strings2d, cellValue2d, boost::is_any_of(";"));
  boost::split(strings3d, cellValue3d, boost::is_any_of(";"));
  child1.put("2d-X", strings2d[0]);
  child1.put("2d-Y", strings2d[1]);
  child1.put("3d-X", strings3d[0]);
  child1.put("3d-Y", strings3d[1]);
  child1.put("3d-Z", strings3d[2]);
  array.push_back(make_pair("", child1));
  array.push_back(make_pair("", child2));
  array_upper.add_child("abc", array);
  write_json(buf, array_upper, true);
  std::string json = buf.str();
  std::cout << json << std::endl;
}

/**
 * @brief Returns 0-based index of the first free row in a grid
 */
int firstFreeRow(const wxGrid &grid) {
  using cit = boost::counting_iterator<int>;
  const auto size = grid.GetNumberRows();
  const auto row = find_if(cit(0), cit(size), [&grid](int x) {
    return "" == grid.GetCellValue(x, 0) && "" == grid.GetCellValue(x, 1);
  });
  return *row;
}

void MainFrame::onLeftClick(wxMouseEvent &event) {
  const auto row = firstFreeRow(*this->m_grid2);
  const auto pointCoordinates = event.GetLogicalPosition(wxClientDC(m_bitmap3));
  m_grid2->SetCellValue(row, 0, to_string(pointCoordinates.x) + ";" +
                                    to_string(pointCoordinates.y));
}
