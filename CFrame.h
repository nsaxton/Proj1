/*!
 * \file CFrame.h
 *
 * \author Nick Saxton
 *
 * \brief An object of this type is instantiated to represent
 * a window frame on the screen.
 */

#ifndef CFRAME_H
#define	CFRAME_H

#include <wx/wx.h>
#include "CAquarium.h"
#include "CReporter.h"

//! Program main display frame
class CFrame : public wxFrame
{
public:
    CFrame();
    CFrame(const CFrame& orig);
    virtual ~CFrame();
            
    enum Ids {ID_Exit=1, ID_About, ID_AddFishBeta, ID_AddTreasureChest, 
                ID_AddFishSparty, ID_Trashcan, ID_CountBetas, ID_AddCatfish,
                ID_SaveAs, ID_FileOpen, ID_Timer, ID_AddBubbleTreasureChest,
                ID_Feed, ID_Clean};
    
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnCountBetas(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnAddFishBeta(wxCommandEvent& event);
    void OnAddFishSparty(wxCommandEvent& event);
    void OnAddCatfish(wxCommandEvent& event);
    void OnToggleTrashcan(wxCommandEvent& event);
    void OnLeftButtonDown(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnAddTreasureChest(wxCommandEvent& event);
    void OnAddBubbleTreasureChest(wxCommandEvent& event);
    void OnFileSaveAs(wxCommandEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnFeed(wxCommandEvent& event);
    void OnClean(wxCommandEvent& event);
    
    
    DECLARE_EVENT_TABLE()
    
private:
    //! An object that describes our aquarium
    CAquarium   mAquarium;
    
    //! Any item we are currently dragging
    CItem       *mGrabbedItem;
    
    //! A time for animation
    wxTimer mTimer;
    
    //! The current Unix time
    long long mCurrentTime;
    
    int mOrigX;
    int mOrigY;
    
    //! A reporter window
    CReporter *mReporter;
};

#endif	/* CFRAME_H */

