/*!
 * \file CBubbles.cpp
 *
 * \author Nick Saxton
 */

#include "CBubbles.h"
#include "CAquarium.h"

using namespace std;

//! Fish filename
const wstring DecorBubblesImageName(L"airbubbles.png");

/*! Constructor
 */
CBubbles::CBubbles(CAquarium *aquarium) : CItem(aquarium, 
                                                      DecorBubblesImageName)
{
    
}

CBubbles::~CBubbles()
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
wxXmlNode *CBubbles::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CItem::XmlSave();
    
    node->AddAttribute(L"type", L"bubbles");
    
    return node;
}

/*! \brief Clone this object
 *
 * \returns an allocated copy of this object
 */
CItem *CBubbles::Clone()
{
    return new CBubbles(*this);
}

/*! \brief Accepts an item visitor
 *
 * \param visitor The item visitor to accept
 */
void CBubbles::Accept(CItemVisitor* visitor)
{
}

void CBubbles::Update(double elapsed)
{
    SetLocation(GetX(),
                GetY() + 30 * elapsed);
    if( GetY() < 2)
    {
        SetDeleteBubbles(true);
    }
}