#include "MainFrame.h"

// WX
#include <wx/wfstream.h>
#include <wx/log.h>
#include <wx/filedlg.h>
#include <string>
#include <memory>
using namespace std;

// OPENCV
#include <opencv2/opencv.hpp>

using cv::Mat;

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

void MainFrame::onMenuSelection(wxCommandEvent &event) {

  wxFileDialog openFileDialog(this, _("Open XYZ file"), _(""), _(""),
                              _("XYZ files (*.wmv)|*.wmv"),
                              wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if (openFileDialog.ShowModal() == wxID_CANCEL)
    return;

  wxFileInputStream input_stream(openFileDialog.GetPath());
  if (!input_stream.IsOk()) {
    return;
  };
  const auto image = getFirstFrame(string(openFileDialog.GetPath().mb_str()));
  this->m_bitmap3->SetBitmap(*image);
  this->m_scrolledWindow2->FitInside();
}
