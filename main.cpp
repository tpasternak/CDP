#include <wx/app.h>
#include <memory>
#include "MainFrame.h"

using namespace std;

/**
 * @brief A function
 * @param [in] x
 */
int function_a(int x) { return x; }

/**
 * @brief B function
 */
int function_b() { return 1; }

class MyApp : public wxApp {
public:
  MainFrame *frame;
  virtual bool OnInit() override {
    frame = new MainFrame(nullptr);
    frame->Show(true);
    return true;
  };
};

IMPLEMENT_APP(MyApp)
