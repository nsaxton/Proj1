/*!
 * \file CFish.cpp
 *
 * \author Nick Saxton
 */

#include <sstream>

#include "CFish.h"
#include "CApp.h"

//! Maximum spped in the X direction in
//! pixels per second
const double MaxSpeedX = 50;

//! Maximum speed in the Y direction in
//! pixels per second
const double MaxSpeedY = 20;

using namespace std;

CFish::~CFish()
{
}

/*! \brief Copy constructor
 *
 * \param original The original fish object to be copied
 */
CFish::CFish(const CFish &original) : CItem(original)
{
    mSpeedX = original.mSpeedX;
    mSpeedY = original.mSpeedY;
}

/*! \brief Constructor
 *
 * \param aquarium The aquarium we are in
 * \param filename Filename for the image we use
 */
CFish::CFish(CAquarium *aquarium, const std::wstring &filename) :
         CItem(aquarium, filename)
{
    mSpeedX = ((double)rand() / RAND_MAX) * MaxSpeedX;
    mSpeedY = ((double)rand() / RAND_MAX) * MaxSpeedY;
}

/*! \brief Handle updates in time of our fish
 * 
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 *
 * \param elapsed Time elapsed since the class call
 */
void CFish::Update(double elapsed)
{
    SetLocation(GetX() + mSpeedX * elapsed,
                GetY() + mSpeedY * elapsed);
    
    if(mSpeedX > 0 && GetX() >= (GetAquarium()->GetWidth()-50-GetWidth()/2))
    {
        mSpeedX = -mSpeedX;
    }
    if(mSpeedX < 0 && GetX() <= 50+GetWidth()/2)
    {
        mSpeedX = -mSpeedX;
    }
    
    if(mSpeedY > 0 && GetY() >= (GetAquarium()->GetHeight()-100-GetHeight()/2))
    {
        mSpeedY = -mSpeedY;
    }
    if(mSpeedY < 0 && GetY() <= 50+GetHeight()/2)
    {
        mSpeedY = -mSpeedY;
    }
    
    Mirror(mSpeedX < 0);
}

/*! \brief Create an XML node for this item type
 * 
 * Create the XML node using the base class version of
 * this function and add information to it specific to this
 * derived class.
 *
 * \returns The newly created node
 */
wxXmlNode *CFish::XmlSave()
{
    // Use the version in the base class to create the node
    // and include common information
    wxXmlNode *node = CItem::XmlSave();
   
    node->AddAttribute(L"speedX", wxString::Format(L"%f", (double)mSpeedX));
    node->AddAttribute(L"speedY", wxString::Format(L"%f", (double)mSpeedY));
    
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
void CFish::XmlLoad(wxXmlNode *node)
{
    mSpeedX = wcstod(node->GetAttribute(L"speedX", L"5.0"), NULL);
    mSpeedY = wcstod(node->GetAttribute(L"speedY", L"5.0"), NULL);
    
    CItem::XmlLoad(node);
}

/*! \brief Sets the speed of the fish
 *
 * \param x X direction speed
 * \param y Y direction speed
 */
void CFish::SetSpeed(double x, double y)
{
    mSpeedX = x;
    mSpeedY = y;
}