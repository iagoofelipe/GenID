#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>

namespace genid
{

    class MainWindow : public wxFrame {
    public:
        MainWindow();

    private:
        const int SPACE = 6;
        const int MARGIN = 10;
        
        wxPanel* panel;
        wxBoxSizer* panelSizer;
        wxSpinCtrl* spNumIds;
        wxTextCtrl* tcListIds;
        wxCheckBox* cbCopyAfter;

        void generateContent();
        void on_btnCopy_clicked(wxCommandEvent& event);
        void on_btnGen_clicked(wxCommandEvent& event);
        void on_btnClear_clicked(wxCommandEvent& event);
    };

    static wxWindow* setFontPointSize(wxWindow* win, int pointSize = 11);

}