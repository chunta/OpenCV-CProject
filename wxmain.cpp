#include <wx/wx.h>
#include <opencv2/opencv.hpp>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    void OnOpen(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);

private:
    wxDECLARE_EVENT_TABLE();
    wxStaticBitmap* imageDisplay;
};

enum
{
    ID_Open = 1,
    ID_Quit
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Open, MyFrame::OnOpen)
    EVT_MENU(ID_Quit, MyFrame::OnQuit)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("OpenCV and wxWidgets");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Open, "&Open\tCtrl-O", "Open an image");
    menuFile->AppendSeparator();
    menuFile->Append(ID_Quit, "E&xit\tCtrl-X", "Quit the application");

    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");

    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to OpenCV and wxWidgets!");

    imageDisplay = new wxStaticBitmap(this, wxID_ANY, wxBitmap());
}

void MyFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog openFileDialog(this, _("Open image file"), "", "",
        "Image files (*.jpg;*.png;*.bmp)|*.jpg;*.png;*.bmp", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    cv::Mat img = cv::imread(openFileDialog.GetPath().ToStdString());
    if (img.empty())
    {
        wxMessageBox("Cannot open image file", "Error", wxICON_ERROR);
        return;
    }

    cv::cvtColor(img, img, cv::COLOR_BGR2RGB); // Convert BGR to RGB
    wxImage wxImg(img.cols, img.rows, img.data, true);
    imageDisplay->SetBitmap(wxBitmap(wxImg));
    Layout();
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}
