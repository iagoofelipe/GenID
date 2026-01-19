#include "app.h"
#include "mainwindow.h"

bool genid::Application::OnInit() {
    MainWindow* win = new MainWindow;
    return win->Show();
}