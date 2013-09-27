/*!
 * \file CCatfish.cpp
 *
 * \author Nick Saxton
 */

#include "CCatfish.h"
#include "CAquarium.h"

using namespace std;

//! Fish filename
const wstring CatfishImageName(L"catfish.png");

//! Maximum speed in the X direction in
//! pixels per second
const double MaxSpeedX = 30;

//! Minimum speed in the X direction in
//! pixels per second
const double MinSpeedX = 10;

//! Maximum speed in the Y direction in
//! pixels per second
const double MaxSpeedY = 10;

//! Minimum speed in the Y direction in
//! pixels per second
const double MinSpeedY = 2;

/*! Constructor
 */
CCatfish::CCatfish(CAquarium *aquarium) : CFish(aquarium, 
                                                      CatfishImageName)
{
    double x = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);
    double y = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);
    SetSpeed(x,y);
}

CCatfish::~CCatfish()
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
wxXmlNode *CCatfish::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CFish::XmlSave();
    
    node->AddAttribute(L"type", L"catfish");
    
    return node;
}

/*! \brief Clone this object
 *
 * \returns an allocated copy of this object
 */
CItem *CCatfish::Clone()
{
    return new CCatfish(*this);
}