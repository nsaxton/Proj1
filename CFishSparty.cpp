/*!
 * \file CFishSparty.cpp
 *
 * \author Nick Saxton
 */

#include "CFishSparty.h"
#include "CAquarium.h"

using namespace std;

//! Fish filename
const wstring FishSpartyImageName(L"sparty-fish.png");

//! Maximum speed in the X direction in
//! pixels per second
const double MaxSpeedX = 25;

//! Minimum speed in the X direction in
//! pixels per second
const double MinSpeedX = 15;

//! Maximum speed in the Y direction in
//! pixels per second
const double MaxSpeedY = 30;

//! Minimum speed in the Y direction in
//! pixels per second
const double MinSpeedY = 15;

/*! Constructor
 */
CFishSparty::CFishSparty(CAquarium *aquarium) : CFish(aquarium, 
                                                      FishSpartyImageName)
{
    double x = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);
    double y = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);
    y = -y;
    SetSpeed(x,y);
}

CFishSparty::~CFishSparty()
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
wxXmlNode *CFishSparty::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CFish::XmlSave();
    
    node->AddAttribute(L"type", L"sparty-fish");
    
    return node;
}

/*! \brief Clones this object
 *
 * \returns an allocated copy of this object
 */
CItem *CFishSparty::Clone()
{
    return new CFishSparty(*this);
}