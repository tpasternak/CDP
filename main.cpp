#include <wx/app.h>
#include "MainWindow.h"
class MyApp : public wxApp {
public:
  virtual bool OnInit() {

    MyFrame2 *frame = new MyFrame2(NULL);
    frame->Show(true);
    return true;
  };
};

IMPLEMENT_APP(MyApp)
