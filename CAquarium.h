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
    bool IsOverTrashcan(int x, int y);
    void DeleteItem(CItem *item);
    int CountBetas();
    void Save(const std::wstring &filename);
    void Load(const std::wstring &filename);
    void Clear();
    void Update(double elapsed);
    
    //! \brief Get the width of the aquarium
    //! \returns Aquarium width
    int GetWidth() const {return mBackground.GetWidth();}
   
    //! \brief Get the height of the aquarium
    //! \returns Aquarium height
    int GetHeight() const {return mBackground.GetHeight();}
    
private:
    wxBitmap mBackground;       //!< Background image to use
    wxBitmap mTrashcan;         //!< Trash can image to use
    
    //! State of the trashcan
    bool mTrashCanActive;
    
    //! The image cache
    std::map<std::wstring, wxImage> mImageCache;
    
    //! All of the items that populate our aquarium
    std::list<CItem *> mItems;
};

#endif	/* CAQUARIUM_H */

