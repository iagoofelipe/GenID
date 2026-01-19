#include "mainwindow.h"
#include "utils.h"

#include <wx/grid.h>
#include <sstream>
#include <string>

namespace genid
{
    static wxWindow*
        setFontPointSize(wxWindow* win, int pointSize)
    {
        wxFont font = win->GetFont();
        font.SetPointSize(pointSize);
        win->SetFont(font);
        return win;
    }

    MainWindow::MainWindow()
        : wxFrame(NULL, wxID_ANY, "ID Generator")
    {
        panel = new wxPanel(this, wxID_ANY);
        panelSizer = new wxBoxSizer(wxVERTICAL);

        generateContent();
        panel->SetSizer(panelSizer);

        wxBoxSizer* winSizer = new wxBoxSizer(wxVERTICAL);
        winSizer->Add(panel, 1, wxEXPAND | wxALL, MARGIN);
        SetSizer(winSizer);

        SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));
        SetClientSize(500, 600);
        Center();
    }

    void MainWindow::generateContent()
    {
        panelSizer->Add(setFontPointSize(new wxStaticText(panel, wxID_ANY, "ID Generator", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL), 13), 0, wxEXPAND);
        panelSizer->Add(setFontPointSize(cbCopyAfter = new wxCheckBox(panel, wxID_ANY, "Copy to clipboard after generate")), 0, wxEXPAND | wxTOP, SPACE);
        cbCopyAfter->SetValue(true);

        wxFlexGridSizer* numIdsSizer = new wxFlexGridSizer(3, SPACE, SPACE);
        numIdsSizer->AddGrowableCol(1, 1);
        numIdsSizer->Add(setFontPointSize(new wxStaticText(panel, wxID_ANY, "Quantity")), 0, wxALIGN_CENTER_VERTICAL);
        
        spNumIds = new wxSpinCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, 1);
        numIdsSizer->Add(setFontPointSize(spNumIds), 0, wxEXPAND);

        wxButton* btnGen = new wxButton(panel, wxID_ANY, "generate");
        numIdsSizer->Add(setFontPointSize(btnGen));

        panelSizer->Add(numIdsSizer, 0, wxEXPAND | wxTOP, SPACE);

        tcListIds = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH2);
        panelSizer->Add(setFontPointSize(tcListIds), 1, wxEXPAND | wxTOP, SPACE);
    
        // Buttons
        wxButton* btnCopy = new wxButton(panel, wxID_ANY, "copy to clipboard");
        wxButton* btnClear = new wxButton(panel, wxID_ANY, "clear");

        wxBoxSizer* btnsSizer = new wxBoxSizer(wxHORIZONTAL);
        btnsSizer->AddStretchSpacer();
        btnsSizer->Add(setFontPointSize(btnCopy));
        btnsSizer->Add(setFontPointSize(btnClear), 0, wxLEFT, SPACE);

        panelSizer->Add(btnsSizer, 0, wxEXPAND | wxTOP, SPACE);

        // Binding events
        btnCopy->Bind(wxEVT_BUTTON, &MainWindow::on_btnCopy_clicked, this);
        btnGen->Bind(wxEVT_BUTTON, &MainWindow::on_btnGen_clicked, this);
        btnClear->Bind(wxEVT_BUTTON, &MainWindow::on_btnClear_clicked, this);
        spNumIds->Bind(wxEVT_TEXT_ENTER, &MainWindow::on_spNumIds_returnPressed, this);
    }

    void MainWindow::on_btnCopy_clicked(wxCommandEvent& event)
    {
        copy_to_clipboard(tcListIds->GetValue().ToStdString());
    }

    void MainWindow::on_btnGen_clicked(wxCommandEvent& event)
    {
        int numIds = spNumIds->GetValue();
        std::stringstream stream;
        std::string ids;

        for (int i = 0; i < numIds; i++)
            stream << make_time_random_id() << ((numIds == i + 1) ? "" : "\n");

        tcListIds->SetValue(ids = stream.str());
        if (cbCopyAfter->IsChecked())
            copy_to_clipboard(ids);
    }

    void MainWindow::on_btnClear_clicked(wxCommandEvent& event)
    {
        spNumIds->SetValue(1);
        tcListIds->Clear();
    }

    void MainWindow::on_spNumIds_returnPressed(wxCommandEvent& event)
    {
		on_btnGen_clicked(event);
    }
}
