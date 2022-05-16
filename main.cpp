#include <vector>
#include <thread>

#include "SettingsStore.h"
#include "Graphic.h"

#include <wx/wxprec.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
// settings
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


class MyFrame : public wxFrame
{
public:
    MyFrame();
private:
    enum
    {
        ID_Start = 1,
        ID_Pause,
        ID_Generate,
        ID_Clear,
        ID_Time,
    };

    wxPanel *MainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    wxGridSizer *VFrameMain = new wxGridSizer(10, 2, 30, 30);

    wxStaticText *timeToUpdate = new wxStaticText(MainPanel, wxID_ANY, "time to update frame: ");

    wxSpinCtrl *randomProbSpin = new wxSpinCtrl(MainPanel);
    wxSpinCtrl *timeToUpdateSpin = new wxSpinCtrl(MainPanel);

    wxButton *startBtn = new wxButton(MainPanel, ID_Start, _T("start"));
    wxButton *pauseBtn = new wxButton(MainPanel, ID_Pause, _T("pause"));
    wxButton *generateRandomBtn = new wxButton(MainPanel, ID_Generate, _T("generate field"));
    wxButton *clearBtn = new wxButton(MainPanel, ID_Clear, _T("clear field"));

    void OnGenerateBtn(wxCommandEvent& event);
    void OnStartBtn(wxCommandEvent& event);
    void OnPauseBtn(wxCommandEvent& event);
    void OnClearBtn(wxCommandEvent& event);
    void OnTimeToUpdateSpin(wxCommandEvent& event);
};

wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, ss.title)
{
    MainPanel->SetSizer( VFrameMain ); //Устанавливаем сайзер верхнего уровня
    VFrameMain->Add(startBtn);
    VFrameMain->Add(pauseBtn);

    VFrameMain->Add(generateRandomBtn);
    VFrameMain->Add(randomProbSpin);

    VFrameMain->Add(timeToUpdate);
    VFrameMain->Add(timeToUpdateSpin);
    timeToUpdateSpin->SetRange(100, 1'000'000);
    timeToUpdateSpin->SetValue(100'000);

    VFrameMain->Add(clearBtn);

    VFrameMain->SetSizeHints(this); //Фиксируем минимальный размер окна по данной компоновке.
    MainPanel->Layout();


    Bind(wxEVT_BUTTON, &MyFrame::OnStartBtn, this, ID_Start);
    Bind(wxEVT_BUTTON, &MyFrame::OnPauseBtn, this, ID_Pause);
    Bind(wxEVT_BUTTON, &MyFrame::OnGenerateBtn, this, ID_Generate);
    Bind(wxEVT_BUTTON, &MyFrame::OnClearBtn, this, ID_Clear);
    Bind(wxEVT_SPIN_UP, &MyFrame::OnTimeToUpdateSpin, this, ID_Time);

    std::thread grLoop(loop);
    grLoop.detach();
}


void MyFrame::OnGenerateBtn(wxCommandEvent& event)
{
    ss.setProbability(randomProbSpin->GetValue());
    field.randomFillField();
    updateDisplay();
}


void MyFrame::OnPauseBtn(wxCommandEvent &event){
    ss.setPause(true);
}


void MyFrame::OnStartBtn(wxCommandEvent &event){
    ss.setPause(false);
}

void MyFrame::OnClearBtn(wxCommandEvent &event){
    field.clearField();
    updateDisplay();
}

void MyFrame::OnTimeToUpdateSpin(wxCommandEvent &event){
    std::cout << timeToUpdateSpin->GetValue() << std::endl;
    ss.setTick(timeToUpdateSpin->GetValue());
}
