/*!
 * \file CAquarium.h
 *
 * \author Nick Saxton
 *
 * \brief Instantiates an aquarium object.
 * 
 * 
 */

#ifndef CAQUARIUM_H
#define	CAQUARIUM_H

#include <wx/wx.h>
#include <map>
#include <string>
#include <list>
#include <wx/xml/xml.h>

#include "CItem.h"
#include "CItemVisitor.h"

//! Class describing the aquarium
class CAquarium
{
public:
    CAquarium();
    CAquarium(const CAquarium& orig);
    virtual ~CAquarium();
    
    void OnDraw(wxDC &dc);
    wxImage *GetCachedImage(const std::wstring name);
    void AddItem(CItem *item);
    CItem *HitTest(int x, int y);
    void MoveToFront(CItem *item);
    void ToggleTrashcan();
    void ToggleHand();
    bool IsOverTrashcan(int x, int y);
    void DeleteItem(CItem *item);
    int CountBetas();
    void Save(const std::wstring &filename);
    void Load(const std::wstring &filename);
    void Clear();
    void Update(double elapsed);
    bool IsNavActive(){return mNavActive;}
    void SetScrollX(int x){mWindowX += x;}
    void SetScrollY(int y){mWindowY += y;}
    int GetScrollX(){return mWindowX;}
    int GetScrollY(){return mWindowY;}
    
    void FrameHeight(int y){mFrameHeight = y;}
    
    
    //! \brief Get the width of the aquarium
    //! \returns Aquarium width
    int GetWidth() const {return mBackground.GetWidth();}
   
    //! \brief Get the height of the aquarium
    //! \returns Aquarium height
    int GetHeight() const {return mBackground.GetHeight();}
    
    /*! \brief Feeding the fish, resetting hunger timer
     */
    void FeedFish();
    
    /*! \brief Feeding the fish, resetting hunger timer
     */
    void CleanTank();
    
    void Accept(CItemVisitor *visitor);
    
    /*! \brief Get the time since the fish were fed
     * \returns Time since last fed
     */
    double TimeSinceFed() {return mFeedTimer;}
    
    /*! \brief Get the time since the aquarium was cleaned
     * \returns Time since last cleaned
     */
    double TimeSinceCleaned() {return mCleanTimer;}
    
private:
    wxBitmap mBackground;       //!< Background image to use
    wxBitmap mTrashcan;         //!< Trash can image to use
    wxBitmap mNormNav;         //!< normal navigation image to use
    wxBitmap mScrollNav;         //!< scrolling hand image to use
    
    //! State of the trashcan
    bool mTrashCanActive;
    
    wxBitmap    mBackgroundDirty1;      //!< 1st (partly) dirty background
    wxBitmap    mBackgroundDirty2;      //!< 2nd (more) dirty background
    wxBitmap    mBackgroundDirty3;      //!< 3rd (most) dirty background
    
    double mFeedTimer;                   //!< Time since last fed
    double mCleanTimer;                  //!< Time since last cleaned
   
    //! bool for navigation setting
    bool mNavActive;
    int mFrameHeight;
    int mWindowX;
    
    int mWindowY;
    
    //! The image cache
    std::map<std::wstring, wxImage> mImageCache;
    
    //! All of the items that populate our aquarium
    std::list<CItem *> mItems;
};

#endif	/* CAQUARIUM_H */

