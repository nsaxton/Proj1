/*!
 * \file CItem.h
 *
 * \author Nick Saxton
 *
 * \brief Base class for aquarium items
 * 
 * 
 */

#ifndef CITEM_H
#define	CITEM_H

#include <wx/wx.h>
#include <wx/xml/xml.h>

class CAquarium;

//! Class for an item that appears in our aquarium
class CItem
{
public:
    virtual ~CItem();
    
    virtual CItem *Clone();
    
    //! Get the x location of the item
    //! \returns X location
    double GetX() const {return mX;}
    
    //! Get the y location of the item
    //! \returns Y location
    double GetY() const {return mY;}
    
    //! Set the item location
    //! \param x X location
    //! \param y Y location
    void SetLocation(double x, double y) {mX = x; mY = y;}
    
    //! Draw this item
    //! \param dc Device context to draw on
    void Draw(wxDC &dc);
    
    //! Test to see if we clicked on this item
    //! \param x X location
    //! \param y Y location
    //! \returns true if we clicked on the item
    bool HitTest(int x, int y);
    
    //! Test to see if item is beta fish
    //! \returns true if item is beta fish
    virtual bool IsBetaFish() {return false;}
    
    virtual wxXmlNode *XmlSave();
    virtual void XmlLoad(wxXmlNode *node);
    
    //! \brief Handle updates for animation
    //! \param elapsed The time since the last update
    virtual void Update(double elapsed) {}
    
    //! \brief Get the aquarium this item is in
    //! \returns Aquarium pointer
    CAquarium *GetAquarium() {return mAquarium;}
    
    void Mirror(bool mirror);
        
    int GetWidth() {return mItemBitmap->GetWidth();}
    int GetHeight() {return mItemBitmap->GetHeight();}
    
protected:
    CItem(CAquarium *aquarium, const std::wstring &filename);
    CItem(const CItem &original);
    
private:
    //! Default constructor (disabled)
    CItem();
    
    //! Copy constructor (disabled)
    //CItem(const CItem&);
         
    //! The aquarium this item is contained in
    CAquarium *mAquarium;
    
    //! Item location in the aquarium
    double mX;     //!< X location for the center of the item
    double mY;     //!< Y location for the center of the item
    
    wxImage *mItemImage;        //!< Pointer to the image of the fish
    wxBitmap *mItemBitmap;      //!< Pointer to a bitmap for the fish
    wxImage *mItemImageOrig;    //!< Pointner to the original item image
};

#endif	/* CITEM_H */

