/*!
 * \file CDecorTreasure.cpp
 *
 * \author Nick Saxton
 */

#include "CDecorTreasure.h"
#include "CAquarium.h"

using namespace std;

//! Fish filename
const wstring DecorTreasureImageName(L"treasure-chest.png");

/*! Constructor
 */
CDecorTreasure::CDecorTreasure(CAquarium *aquarium) : CItem(aquarium, 
                                                      DecorTreasureImageName)
{
    
}

CDecorTreasure::~CDecorTreasure()
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
wxXmlNode *CDecorTreasure::XmlSave()
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
CItem *CDecorTreasure::Clone()
{
    return new CDecorTreasure(*this);
}

/*! \brief Accepts an item visitor
 *
 * \param visitor The item visitor to accept
 */
void CDecorTreasure::Accept(CItemVisitor* visitor)
{
}