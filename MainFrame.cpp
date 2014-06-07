#include "MainFrame.h"

#include <wx/wfstream.h>
#include <wx/log.h>
#include <wx/filedlg.h>
#include <string>

using namespace std;

void MainFrame::onMenuSelection(wxCommandEvent &event) {

  wxFileDialog openFileDialog(this, _("Open XYZ file"), _(""), _(""),
                              _("XYZ files (*.xyz)|*.xyz"),
                              wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if (openFileDialog.ShowModal() == wxID_CANCEL)
    return;

  wxFileInputStream input_stream(openFileDialog.GetPath());
  if (!input_stream.IsOk()) {
    return;
  };
}
