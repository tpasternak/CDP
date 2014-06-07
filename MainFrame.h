#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "MainWindowBase.h"
#include <wx/wfstream.h>
#include <wx/log.h>
#include <wx/filedlg.h>
#include <string>
using namespace std;

class MainFrame : public MainFrameBase {
public:
  MainFrame(wxWindow *parent) : MainFrameBase(parent){};
  virtual void onMenuSelection(wxCommandEvent &event) override;
};

#endif // MAINFRAME
