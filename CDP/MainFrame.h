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
  virtual void onLoad(wxCommandEvent &event) override;
  virtual void onSave(wxCommandEvent &event) override;
  virtual void onLeftClick(wxMouseEvent &event) override;

private:
  void loadVideo(string const &path);
};

#endif // MAINFRAME
