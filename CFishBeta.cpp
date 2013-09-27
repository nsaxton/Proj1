/*!
 * \file CFishBeta.cpp
 *
 * \author Nick Saxton
 */

#include "CFishBeta.h"
#include "CAquarium.h"

using namespace std;

//! Fish filename
const wstring FishBetaImageName(L"beta.png");

//! Maximum speed in the X direction in
//! pixels per second
const double MaxSpeedX = 60;

//! Minimum speed in the X direction in
//! pixels per second
const double MinSpeedX = 40;

//! Maximum speed in the Y direction in
//! pixels per second
const double MaxSpeedY = 20;

//! Minimum speed in the Y direction in
//! pixels per second
const double MinSpeedY = 10;

/*! Constructor
 */
CFishBeta::CFishBeta(CAquarium *aquarium) : CFish(aquarium, FishBetaImageName)
{
    double x = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);
    double y = MinSpeedY + ((double)rand() / RAND_MAX) * (MaxSpeedY - MinSpeedY);
    SetSpeed(x,y);
}

CFishBeta::~CFishBeta()
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
wxXmlNode *CFishBeta::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CFish::XmlSave();
    
    node->AddAttribute(L"type", L"beta");
    
    return node;
}

/*! \brief Clones this object
 *
 * \returns an allocated copy of this object
 */
CItem *CFishBeta::Clone()
{
    return new CFishBeta(*this);
}