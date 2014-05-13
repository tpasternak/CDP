#include <wx/app.h>
#include "MainFrame.h"
#include "memory"
using namespace std;

class MyApp : public wxApp {
public:
  unique_ptr<MainFrame> frame;
  virtual bool OnInit() {
    frame = make_unique<MainFrame>(nullptr);
    frame->Show(true);
    return true;
  };
};

IMPLEMENT_APP(MyApp)
