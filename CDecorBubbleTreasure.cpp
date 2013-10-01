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
    
    node->AddAttribute(L"type", L"bubble-treasure-chest");
    
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
    
    mCurTime = mCurTime + elapsed;
    int test = int(mCurTime) % 50;
    if(test == 1 || test == 46)
    {
        UpdateChest(1);
    }
    else if(test == 6 || test == 41 )
    {
        UpdateChest(2);
    }
    else if((test == 11) || test == 36)
    {
        UpdateChest(3);
    }
    else if((test == 16) || test == 31)
    {
        UpdateChest(4);
    }
    else if(test == 21)
    {
        UpdateChest(5);
    }
    
}

/*! \brief Accepts an item visitor
 *
 * \param visitor The item visitor to accept
 */
void CDecorBubbleTreasure::Accept(CItemVisitor* visitor)
{
}
