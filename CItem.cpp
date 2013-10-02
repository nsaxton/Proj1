/*!
 * \file CItem.cpp
 *
 * \author Nick Saxton
 */

#include "CItem.h"
#include "CAquarium.h"
using namespace std;

const wstring DecorBubbleTreasureImageName1(L"chest1.png");
const wstring DecorBubbleTreasureImageName2(L"chest2.png");
const wstring DecorBubbleTreasureImageName3(L"chest3.png");
const wstring DecorBubbleTreasureImageName4(L"chest4.png");
const wstring DecorBubbleTreasureImageName5(L"chest5.png");

/*! \brief Constructor
 *
 * \param aquarium The aquarium this item is a member of
 */
CItem::CItem(CAquarium *aquarium, const std::wstring &filename) : mAquarium(aquarium), mX(0), mY(0)
{
    mItemImageOrig = aquarium->GetCachedImage(filename);
    mItemImage = new wxImage(*mItemImageOrig);
    mItemBitmap = new wxBitmap(*mItemImage);
}

/*! \brief Copy constructor
 *
 * \param original The original item object to be copied
 */
CItem::CItem(const CItem &original)
{
    mItemImageOrig = original.mItemImageOrig;
    mItemImage = new wxImage(*mItemImageOrig);
    mItemBitmap = new wxBitmap(*mItemImage);
    mAquarium = original.mAquarium;
    mX = original.mX;
    mY = original.mY;
}

//! Destructor
CItem::~CItem()
{
    delete mItemImage;
    delete mItemBitmap;
}

/*! \brief Test to see if we hit this object with a mouse.
 *
 * \param x X position to test
 * \param y Y position to test
 * \returns true if hit.
 */
bool CItem::HitTest(int x, int y)
{
    int wid = mItemImage->GetWidth();
    int hit = mItemImage->GetHeight();
    
    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the center of the image.
    // Adding half the size makes x, y relative to the top corner of the image
    x = x - (int)GetX() + wid/2 - mXOffset;
    y = y - (int)GetY() + hit/2 - mYOffset;
    
    // Test to see if x, y are in the image
    if(x < 0 || y < 0 || x >= wid || y >= hit)
    {
        // We are outside the image
        return false;
    }
    
    // Test to see if x, y are in the drawn part of the image
    return !mItemImage->HasAlpha() || mItemImage->GetAlpha(x, y) > 0;
}

/*! \brief Draw our item
 *
 * \param dc A device context to draw the item on
 */
void CItem::Draw(wxDC &dc)
{
    int wid = mItemBitmap->GetWidth();
    int hit = mItemBitmap->GetHeight();
    dc.DrawBitmap(*mItemBitmap, int(GetX() - wid/2)+mXOffset, int(GetY() - hit/2)+mYOffset, true);
}

/*! \brief XML function to save an aquarium item
 *
 * This is the base class version that does the
 * work of creating the node. Derived classes
 * will override this function to add attributes
 * to the node.
 * \returns The created XML node object
 */
wxXmlNode *CItem::XmlSave()
{
    // Create a new node for the item
    wxXmlNode *node = new wxXmlNode(wxXML_ELEMENT_NODE, L"item");
    
    
    node->AddAttribute(L"x", wxString::Format(L"%d", (int)mX));
    node->AddAttribute(L"y", wxString::Format(L"%d", (int)mY));
    
    return node;
}

/*! \brief Load the attributes for an item node.
 *
 * This is the base class version that load the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 * 
 * \param node The Xml node we are loading the item from
 */
void CItem::XmlLoad(wxXmlNode *node)
{
    mX = wcstol(node->GetAttribute(L"x", L"0"), NULL, 10);
    mY = wcstol(node->GetAttribute(L"y", L"0"), NULL, 10);
}

/*! \brief Optionally mirror the item image
 * 
 * If mirror is true, a copy of the original image
 * will be made that is mirrored and it will be made the 
 * current image. If false, an unmirrored copy is made 
 * instead. 
 * \param mirror true if mirroring is wanted.
 */
void CItem::Mirror(bool mirror)
{
    // Delete the existing image and bitmap
    delete mItemImage;
    delete mItemBitmap;
    
    if(mirror)
    {
        mItemImage = new wxImage(mItemImageOrig->Mirror(true));
        mItemBitmap = new wxBitmap(*mItemImage); 
    } 
    else
    {
        mItemImage = new wxImage(*mItemImageOrig);
        mItemBitmap = new wxBitmap(*mItemImage);
    }
}

/*! \brief Clones this object
 *
 * \returns an allocated copy of this object
 */
CItem *CItem::Clone()
{
    
}


void CItem::UpdateChest(int i)
{
        // Delete the existing image and bitmap
    delete mItemImage;
    delete mItemBitmap;
    
    switch (i) {
    case 1:
        mItemImageOrig = mAquarium->GetCachedImage(DecorBubbleTreasureImageName1);
        mItemImage = new wxImage(*mItemImageOrig);
        mItemBitmap = new wxBitmap(*mItemImage);
        break;
    case 2:
        mItemImageOrig = mAquarium->GetCachedImage(DecorBubbleTreasureImageName2);
        mItemImage = new wxImage(*mItemImageOrig);
        mItemBitmap = new wxBitmap(*mItemImage);
        break;
    case 3:
        mItemImageOrig = mAquarium->GetCachedImage(DecorBubbleTreasureImageName3);
        mItemImage = new wxImage(*mItemImageOrig);
        mItemBitmap = new wxBitmap(*mItemImage);    
        break;
    case 4:
        mItemImageOrig = mAquarium->GetCachedImage(DecorBubbleTreasureImageName4);
        mItemImage = new wxImage(*mItemImageOrig);
        mItemBitmap = new wxBitmap(*mItemImage);
        break;
    case 5:
        mItemImageOrig = mAquarium->GetCachedImage(DecorBubbleTreasureImageName5);
        mItemImage = new wxImage(*mItemImageOrig);
        mItemBitmap = new wxBitmap(*mItemImage);  
        break;
    }
}

void CItem::SetBubbles(double x, double y)
{
    mAquarium->SetBubbleActive(true);
    mAquarium->SetBubbleX(x);
    mAquarium->SetBubbleY(y-100);
}
