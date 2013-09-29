/*!
 * \file CFrame.cpp
 *
 * \author Nick Saxton
 */

#include <sstream>

#include "CFrame.h"
#include "CFishBeta.h"
#include "CDecorTreasure.h"
#include "CFishSparty.h"
#include "CCatfish.h"

using namespace std;

const int FrameDuration = 30; //! Milliseconds

BEGIN_EVENT_TABLE(CFrame, wxFrame)
EVT_MENU(ID_Exit, CFrame::OnExit)
EVT_MENU(ID_About, CFrame::OnAbout)
EVT_MENU(ID_CountBetas, CFrame::OnCountBetas)
EVT_MENU(ID_AddFishBeta, CFrame::OnAddFishBeta)
EVT_MENU(ID_AddTreasureChest, CFrame::OnAddTreasureChest)
EVT_MENU(ID_AddFishSparty, CFrame::OnAddFishSparty)
EVT_MENU(ID_AddCatfish, CFrame::OnAddCatfish)
EVT_MENU(ID_Trashcan, CFrame::OnToggleTrashcan)
EVT_MENU(ID_SaveAs, CFrame::OnFileSaveAs)
EVT_MENU(ID_FileOpen, CFrame::OnFileOpen)
EVT_PAINT(CFrame::OnPaint)
EVT_LEFT_DOWN(CFrame::OnLeftButtonDown)
EVT_MOTION(CFrame::OnMouseMove)
EVT_LEFT_UP(CFrame::OnMouseMove)
EVT_TIMER(ID_Timer, CFrame::OnTimer)
END_EVENT_TABLE()


//! Width of the Hand Icon
const int HandWidth = 68;

//!Height of the Hand Icon
const int HandHeight = 59;

/*! \brief Default constructor
 *
 * Creates the frame and sets its initial size and name
 */
CFrame::CFrame() : wxFrame(NULL, -1, L"wxWidgets Application",
                           wxPoint(20, 20), wxSize(1024, 800)),
                           mTimer(this, ID_Timer)
{
    //
    // File menu
    //

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Trashcan, L"&Trashcan");
    menuFile->Append(ID_About, L"&About");
    menuFile->AppendSeparator();
    wxMenuItem *openItem = menuFile->Append(ID_FileOpen, L"&Open...");
    wxMenuItem *saveItem = menuFile->Append(ID_SaveAs, L"Save &As...");
    wxMenuItem *exitItem = menuFile->Append(ID_Exit, L"E&xit");
    exitItem->SetHelp(L"Exit the program");
    saveItem->SetHelp(L"Save the aquarium's current state");

    //
    // Fish menu
    //
    wxMenu *menuFish = new wxMenu;
    menuFish->Append(ID_AddFishBeta, L"&Beta");
    menuFish->Append(ID_AddFishSparty, L"&Sparty");
    menuFish->Append(ID_AddCatfish, L"&Catfish");
    
    //
    // Count menu
    //
    wxMenu *menuCount = new wxMenu;
    menuCount->Append(ID_CountBetas, L"&Beta");
    
    //
    // Decor menu
    //
    wxMenu *menuDecor = new wxMenu;
    menuDecor->Append(ID_AddTreasureChest, L"&Treasure Chest");

    //
    // Menu bar
    //
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, L"&File");
    menuBar->Append(menuFish, L"&Add Fish");
    menuBar->Append(menuCount, L"&Count Fish");
    menuBar->Append(menuDecor, L"Add &Decor");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText(L"Status");

    SetBackgroundColour(wxColour(0, 0, 0));

    mGrabbedItem = NULL;
    
    mCurrentTime = wxGetLocalTimeMillis().GetValue();
    
    mTimer.Start(FrameDuration);
}

CFrame::CFrame(const CFrame& orig)
{
}

CFrame::~CFrame()
{
}

/*! \brief This function is called when an exit menu item is selected.
 *
 * It closes the main window, which ends the program
 * \param event An object that describes the event
 */
void CFrame::OnExit(wxCommandEvent& event)
{
    Close(TRUE);
}

/*! \brief File/About menu option handler
 * 
 * \param event An object that describes the event.
 */
void CFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"This is a simple wxWidgets application",
                 L"About Step 2",
                 wxOK | wxICON_INFORMATION, this);
}

/*! \brief Function called whenever we need to redraw the window
 *
 * This function is called in response to a drawing message
 * whenever we need to redraw the window on the screen.
 * It is responsible for painting the window.
 * \param event An event associated with the message.
 */
void CFrame::OnPaint(wxPaintEvent &event)
{
    // Handles updates
    long long newTime = wxGetLocalTimeMillis().GetValue();
    double elapsed = (newTime - mCurrentTime) * 0.001;
    mCurrentTime = newTime;
    
    mAquarium.Update(elapsed);
    
    // Create a device context
    wxPaintDC dc(this);

    mAquarium.OnDraw(dc);

    dc.SetPen(wxNullPen);
    dc.SetBrush(wxNullBrush);
    dc.SetFont(wxNullFont);
}

/*! \brief Add Fish/Beta menu option handler
 *
 * \param event An object that describes the event.
 */
void CFrame::OnAddFishBeta(wxCommandEvent& event)
{
    mAquarium.AddItem(new CFishBeta(&mAquarium));
    Refresh();
}

/*! \brief Add Fish/Catfish menu option handler
 *
 * \param event An object that describes the event.
 */
void CFrame::OnAddCatfish(wxCommandEvent& event)
{
    mAquarium.AddItem(new CCatfish(&mAquarium));
    Refresh();
}

/*! \brief Add Decor/Treasure Chest menu option handler
 *
 * \param event An object that describes the event.
 */
void CFrame::OnAddTreasureChest(wxCommandEvent& event)
{
    mAquarium.AddItem(new CDecorTreasure(&mAquarium));
    Refresh();
}

/*! \brief Add Fish/Sparty menu option handler
 *
 * \param event An object that describes the event.
 */
void CFrame::OnAddFishSparty(wxCommandEvent& event)
{
    mAquarium.AddItem(new CFishSparty(&mAquarium));
    Refresh();
}

/*! \brief Toggle trashcan
 *
 * \param event An object that describes the event.
 */
void CFrame::OnToggleTrashcan(wxCommandEvent& event)
{
    mAquarium.ToggleTrashcan();
    Refresh();
}

/*! \brief Left mouse button handler
 * 
 * This function is called when the left mouse button is clicked
 * on the window.
 * \param event An event describing the mouse click
 */
void CFrame::OnLeftButtonDown(wxMouseEvent &event)
{
    if(event.m_x < HandWidth && event.m_y < 250 + HandHeight/2 && event.m_y > 250 - HandHeight/2)
    {   mAquarium.ToggleHand();}
    
    mGrabbedItem = mAquarium.HitTest(event.m_x, event.m_y);
    if (mGrabbedItem != NULL) {
        mAquarium.MoveToFront(mGrabbedItem);
    }
    
    if(event.m_shiftDown)
    {
        CItem *copy = mGrabbedItem->Clone();
        mAquarium.AddItem(copy);
        copy->SetLocation(event.m_x, event.m_y);
    }
}

/*! \brief Mouse move handler
 *
 * This function is called whenever the mouse is
 * moved over the window.
 * \param event The mouse event
 */
void CFrame::OnMouseMove(wxMouseEvent &event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != NULL) {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.m_leftDown) {
            mGrabbedItem->SetLocation(event.m_x, event.m_y);
        }
        else {
            if(mAquarium.IsOverTrashcan(event.m_x, event.m_y))
            {
                mAquarium.DeleteItem(mGrabbedItem);
            }
            mGrabbedItem = NULL;
        }

        // Force the screen to redraw
        Refresh();
    }
}

/*! \brief Counts the number of beta fish in the aquarium
 *
 * \param event An object that describes the event
 */
void CFrame::OnCountBetas(wxCommandEvent &event)
{
    wstringstream str;
    int count = mAquarium.CountBetas();
    str << L"There are currently " << count << L" beta fish." << ends;
    
    wxMessageBox(str.str().c_str(),
                 L"Number of beta fish",
                 wxOK | wxICON_INFORMATION, this);
}

/*! \brief Opens a file dialog to save the current state of the aquarium
 *
 * \param event An object describing the event
 */
void CFrame::OnFileSaveAs(wxCommandEvent &event)
{
    wxFileDialog dlg(this, L"Save File", L"", L"",
                     L"Aquarium Files (*.aqua)|*.aqua",
                     wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if(dlg.ShowModal() != wxID_OK)
        return;
    
    // Get the filename into a local string
    wstring filename = dlg.GetPath().wc_str();
    
    // If no suffix is supplied for the file, supply it here
    wstring suffix(L".aqua");
    if(!equal(suffix.rbegin(), suffix.rend(), filename.rbegin()))
    {
        filename += suffix;
    }
    
    mAquarium.Save(filename);
}

/*! \brief Opens a file dialog to open a saved aquarium file
 *
 * \param 
 * \returns 
 */
void CFrame::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog dlg(this, L"Open File", L"", L"",
                     L"Aquarium Files (*.aqua)|*.aqua",
                     wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if(dlg.ShowModal() != wxID_OK)
        return;
    
    wstring filename = dlg.GetPath().wc_str();
    
    mAquarium.Load(filename);
    Refresh();
}

/*! \brief Timer handler function
 * 
 * This function is called on a regular basis to invalidate
 * the window, allowing for animation.
 *
 * \param event The timer event
 */
void CFrame::OnTimer(wxTimerEvent &event)
{
    Refresh();
}