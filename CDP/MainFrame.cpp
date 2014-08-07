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
#include <boost/algorithm/string.hpp>

using boost::property_tree::ptree;
using boost::property_tree::write_json;

using cv::Mat;
using cv::Mat_;

ptree getMappingJsonSerialized(const wxGrid &grid);
int firstFreeRow(const wxGrid &grid);
void writeJsonToFile(const ptree &ptree_, const string &path);

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

void MainFrame::onSave(wxCommandEvent &) {
  wxFileDialog saveFileDialog(this, _("Open JSON file"), _(""), _(""),
                              _("json files (*.json)|*.json"), wxFD_SAVE);
  if (saveFileDialog.ShowModal() == wxID_CANCEL) {
    return;
  }
  wxFileOutputStream input_stream(saveFileDialog.GetPath());
  if (!input_stream.IsOk()) {
    return;
  };
  const string path = string(saveFileDialog.GetPath().mb_str());
  fstream f(path);
  const auto tree = getMappingJsonSerialized(*m_grid2);
  writeJsonToFile(tree, path);
}

ptree getMappingJsonSerialized(const wxGrid &grid) {
  ptree root;
  ptree mappingArray;
  const int size = firstFreeRow(grid);
  for (int i = 0; i < size; ++i) {
    ptree child;
    std::vector<std::string> strings2d;
    std::vector<std::string> strings3d;
    string cellValue2d = string(grid.GetCellValue(i, 0));
    string cellValue3d = string(grid.GetCellValue(i, 1));
    boost::split(strings2d, cellValue2d, boost::is_any_of(";"));
    boost::split(strings3d, cellValue3d, boost::is_any_of(";"));
    child.put("2d-X", strings2d[0]);
    child.put("2d-Y", strings2d[1]);
    child.put("3d-X", strings3d[0]);
    child.put("3d-Y", strings3d[1]);
    child.put("3d-Z", strings3d[2]);
    mappingarray.push_back(make_pair("", child));
  }
  root.add_child("mapping", mappingArray);
  return root;
}

void writeJsonToFile(const ptree &ptree_, const string &path) {
  std::fstream file(path);
  write_json(file, ptree_, true);
  file.close();
}

/**
 * @brief Returns 0-based index of the first free row in the grid
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
