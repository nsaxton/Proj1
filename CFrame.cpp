/*!
 * \file CFrame.cpp
 *
 * \author Nick Saxton
 */

#include <sstream>

#include "CFrame.h"
#include "CFishBeta.h"
#include "CDecorTreasure.h"
#include "CDecorBubbleTreasure.h"
#include "CFishSparty.h"
#include "CCatfish.h"
#include "CCountFishVisitor.h"

using namespace std;

const int FrameDuration = 30; //! Milliseconds
const int ReportInterval = 30000; //! Milliseconds

BEGIN_EVENT_TABLE(CFrame, wxFrame)
EVT_MENU(ID_Exit, CFrame::OnExit)
EVT_MENU(ID_About, CFrame::OnAbout)
EVT_MENU(ID_CountBetas, CFrame::OnCountBetas)
EVT_MENU(ID_AddFishBeta, CFrame::OnAddFishBeta)
EVT_MENU(ID_AddTreasureChest, CFrame::OnAddTreasureChest)
EVT_MENU(ID_AddBubbleTreasureChest, CFrame::OnAddBubbleTreasureChest)
EVT_MENU(ID_AddFishSparty, CFrame::OnAddFishSparty)
EVT_MENU(ID_AddCatfish, CFrame::OnAddCatfish)
EVT_MENU(ID_Trashcan, CFrame::OnToggleTrashcan)
EVT_MENU(ID_SaveAs, CFrame::OnFileSaveAs)
EVT_MENU(ID_FileOpen, CFrame::OnFileOpen)
EVT_MENU(ID_Feed, CFrame::OnFeed)
EVT_MENU(ID_Clean, CFrame::OnClean)
EVT_PAINT(CFrame::OnPaint)
EVT_LEFT_DOWN(CFrame::OnLeftButtonDown)
EVT_MOTION(CFrame::OnMouseMove)
EVT_LEFT_UP(CFrame::OnMouseMove)
EVT_TIMER(ID_Timer, CFrame::OnTimer)
EVT_TIMER(ID_ReportTimer, CFrame::OnReport)
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
                           mTimer(this, ID_Timer), 
                           mReportTimer(this, ID_ReportTimer)
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
    menuDecor->Append(ID_AddBubbleTreasureChest, L"&Bubbling Treasure Chest");
    
    //
    // Care menu
    // 
    wxMenu *menuCare = new wxMenu;
    menuCare->Append(ID_Feed, L"&Feed Fish");
    menuCare->Append(ID_Clean, L"&Clean Tank");

    //
    // Menu bar
    //
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, L"&File");
    menuBar->Append(menuFish, L"&Add Fish");
    menuBar->Append(menuCount, L"&Count Fish");
    menuBar->Append(menuDecor, L"Add &Decor");
    menuBar->Append(menuCare, L"&Care");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText(L"Status");

    SetBackgroundColour(wxColour(0, 0, 0));

    mGrabbedItem = NULL;
    
    mCurrentTime = wxGetLocalTimeMillis().GetValue();
    
    mTimer.Start(FrameDuration);
    
    mReporter = new CReporter(this);
    
    mReportTimer.Start(ReportInterval);
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
    int x, y;
    GetSize(&x, &y);
    mAquarium.FrameHeight(y);
    
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

/*! \brief Add Decor/Treasure Chest menu option handler
 *
 * \param event An object that describes the event.
 */
void CFrame::OnAddBubbleTreasureChest(wxCommandEvent& event)
{
    mAquarium.AddItem(new CDecorBubbleTreasure(&mAquarium));
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
    int x, y;
    GetSize(&x, &y);
    if(event.m_x < HandWidth && event.m_y > y - 104 && event.m_y < y + HandHeight - 104)
    {   
        mAquarium.ToggleHand();
        Refresh();
    }
    
    if(mAquarium.IsNavActive())
    {
        mOrigX = event.m_x;
        mOrigY = event.m_y;
    }
    else
    {
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
}

/*! \brief Mouse move handler
 *
 * This function is called whenever the mouse is
 * moved over the window.
 * \param event The mouse event
 */
void CFrame::OnMouseMove(wxMouseEvent &event)
{
    
    if(mAquarium.IsNavActive())
    {
        
        int x, y;
        if(event.m_leftDown){
            y = event.m_y;
            x = event.m_x;
        
            mAquarium.SetScrollX(-mOrigX + x);
            mAquarium.SetScrollY(-mOrigY + y);
        }
    }
    
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != NULL) {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if (event.m_leftDown) {
            mGrabbedItem->SetLocation(event.m_x - mAquarium.GetScrollX(),
                                      event.m_y - mAquarium.GetScrollY());
        }
        else {
            if(mAquarium.IsOverTrashcan(event.m_x, event.m_y))
            {
                mAquarium.DeleteItem(mGrabbedItem);
            }
            mGrabbedItem = NULL;
        }
    }

    // Force the screen to redraw
    Refresh();
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

/*! \brief Feeds the fish, so they don't die of hunger
 *
 * \param 
 * \returns 
 */
void CFrame::OnFeed(wxCommandEvent& event)
{
    mAquarium.FeedFish();
}

/*! \brief Cleans the tank, to avoid the dirty background images
 *
 * \param 
 * \returns 
 */
void CFrame::OnClean(wxCommandEvent& event)
{
    mAquarium.CleanTank();
}

/*! \brief Generates a report on the state of the aquarium every 30 seconds
 *
 * \param event The timer event
 */
void CFrame::OnReport(wxTimerEvent &event)
{
    // How many fish of each type?
    CCountFishVisitor visitor;
    
    mAquarium.Accept(&visitor);
    
    wstringstream betaStr;
    wstringstream catStr;
    wstringstream spartyStr;
    
    int numBetas = visitor.GetNumBeta();
    int numCatfish = visitor.GetNumCatfish();
    int numSparty = visitor.GetNumSparty();
   
    betaStr << L"Beta Fish: " << numBetas << ends;
    
    mReporter->Report(betaStr.str().c_str());
    
    catStr << L"Catfish: " << numCatfish << ends;
    
    mReporter->Report(catStr.str().c_str());
    
    spartyStr << L"Sparty Fish: " << numSparty << ends;
    
    mReporter->Report(spartyStr.str().c_str());
    
    // How dirty is aquarium?
    double dirtyTime = mAquarium.TimeSinceCleaned();
    
    wstring dirtyStr = L"The tank is: ";
    
    if(dirtyTime < 15)
        dirtyStr += L"Clean";
    else if(dirtyTime < 30)
        dirtyStr += L"Dirty";
    else if(dirtyTime < 60)
        dirtyStr += L"Dirtier";
    else
        dirtyStr += L"Filthy";
    
    mReporter->Report(dirtyStr.c_str());
    
    // How long since fed?
    wstringstream foodStr;
    
    int foodTime = mAquarium.TimeSinceFed();
    
    foodStr << L"Time since last fed: " << foodTime << L" seconds" << ends;
    
    mReporter->Report(foodStr.str().c_str());
    
    mReporter->Report(L"----------------------");
}
