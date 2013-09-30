/*!
 * \file CDecorBubbleTreasure.cpp
 *
 * \author Nick Saxton
 */

#include "CDecorBubbleTreasure.h"
#include "CAquarium.h"

using namespace std;

//! Fish filename
const wstring DecorBubbleTreasureImageName1(L"chest1.png");
const wstring DecorBubbleTreasureImageName2(L"chest2.png");
const wstring DecorBubbleTreasureImageName3(L"chest3.png");
const wstring DecorBubbleTreasureImageName4(L"chest4.png");
const wstring DecorBubbleTreasureImageName5(L"chest5.png");

/*! Constructor
 */
CDecorBubbleTreasure::CDecorBubbleTreasure(CAquarium *aquarium) : CItem(aquarium, 
                                                      DecorBubbleTreasureImageName1)
{
    mCurTime = 0;
}

CDecorBubbleTreasure::~CDecorBubbleTreasure()
{
    
}

/*! \brief Create an XML node for this item type
 * 
 * Create the XML node using the base class version of
 * this function and add information to it specific to this
 * derived class.
 *
 * \returns The newly created node
 */
wxXmlNode *CDecorBubbleTreasure::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CItem::XmlSave();
    
    node->AddAttribute(L"type", L"treasure-chest");
    
    return node;
}

/*! \brief Clone this object
 *
 * \returns an allocated copy of this object
 */
CItem *CDecorBubbleTreasure::Clone()
{
    return new CDecorBubbleTreasure(*this);
}


void CDecorBubbleTreasure::Update(double elapsed)
{
    /*
    mCurTime += elapsed;
    
    int test = mCurTime % 50000;
    
    if((test > 0 && test < 5000) || (test > 45000))
    {
        
    }*/
        
}