#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "MainWindowBase.h"

class MainFrame : public MainFrameBase {
public:
  MainFrame(wxWindow *parent) : MainFrameBase(parent) {};
};

#endif // MAINFRAME
