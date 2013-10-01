/*!
 * \file CAquarium.cpp
 *
 * \author Nick Saxton
 */

#include <wx-2.9/wx/dc.h>
#include <sstream>

#include "CFishBeta.h"
#include "CFishSparty.h"
#include "CDecorTreasure.h"
#include "CDecorBubbleTreasure.h"
#include "CCatfish.h"
#include "CAquarium.h"
#include "CFish.h"
#include "CCountFishVisitor.h"

using namespace std;

//! Path to the images directory
const wstring DirectoryContainingImages(L"images/");

//! Width of the trash can
const int TrashCanWidth = 51;

//! Height of the trash can
const int TrashCanHeight = 70;

/*! \brief Default constructor
 *
 * Creates the aquarium object and loads the background image
 */
CAquarium::CAquarium()
{
    if(!mBackground.LoadFile(L"images/backgroundW.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image backgroundW.png");
        
    if(!mBackgroundDirty1.LoadFile(L"images/backgroundW1.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image backgroundW1.png");
    
    if(!mBackgroundDirty2.LoadFile(L"images/backgroundW2.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image backgroundW2.png");
    
    if(!mBackgroundDirty3.LoadFile(L"images/backgroundW3.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image backgroundW3.png");
    
    if(!mTrashcan.LoadFile(L"images/trashcan.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image trashcan.png");
    
    if(!mNormNav.LoadFile(L"images/nav1.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image nav1.png");
    
    if(!mScrollNav.LoadFile(L"images/nav2.png", wxBITMAP_TYPE_PNG))
        wxMessageBox(L"Failed to open image nav2.png");
    
    mNavActive = false;
    mTrashCanActive = false;
    mWindowX = 0;
    mWindowY = 0;
}

/*! \brief Copy constructor 
 */
CAquarium::CAquarium(const CAquarium& orig)
{
}

/*! \brief Destructor
 */
CAquarium::~CAquarium()
{
    Clear();
}

/*! \brief Draw the aquarium
 *
 * \param dc The device context to draw onto
 */
void CAquarium::OnDraw(wxDC& dc)
{
    // Create a font
    wxFont font(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL, false);
    dc.SetFont(font);
    dc.SetTextForeground(wxColour(255, 255, 255));
    if(mWindowX < -1535)
    {
        mWindowX = -1535;
    }
    else if(mWindowX > 0)
    {
        mWindowX =0;
    }
    
    if(mWindowY > 0)
    {
        mWindowY =0;
    }
    else if(mWindowY < -50)
    {
        mWindowY = -50;
    }
    
    // Determine which background to load
    if(mCleanTimer < 15)
     {
        dc.DrawBitmap(mBackground, mWindowX, mWindowY, true);
     }
     else if(mCleanTimer < 30)
     {
        dc.DrawBitmap(mBackgroundDirty1, mWindowX, mWindowY, true);
     }
     else if (mCleanTimer < 45)
     {
        dc.DrawBitmap(mBackgroundDirty2,  mWindowX, mWindowY, true);
     }
     else
     {
        dc.DrawBitmap(mBackgroundDirty3, mWindowX, mWindowY, true);
     }
    dc.DrawText(L"Under the Sea!", 2, 2);
    dc.DrawText(L"Team Ladyfish!", 350,2);
    
    if(mTrashCanActive)
        dc.DrawBitmap(mTrashcan, 0, 0);
    
    
    if(mNavActive)
        dc.DrawBitmap(mScrollNav,0,mFrameHeight-104);
    else
        dc.DrawBitmap(mNormNav,0,mFrameHeight-104);
    
    if(mFeedTimer > 30)       // Fish are dead, clear them out
     {
        while(!mItems.empty())
        {
            delete mItems.front();
            mItems.pop_front();
        }
        mFeedTimer = 0;
     }
     else        // All the fish (and all other items) are good, draw all
     {
         for(list<CItem *>::iterator t=mItems.begin(); t!=mItems.end(); t++)
         {
             CItem *item = *t;
             item->SetXOffset(mWindowX);
             item->SetYOffset(mWindowY);
             item->Draw(dc);
         }
     }
}

/*! \brief Get an image from the image cache
 *
 * Given a base name for an image file, determine if
 * we already loaded it. If we have, return a pointer
 * to the wxBitmap object in the cache. If we have not
 * previously loaded it, load it into the cache and then
 * return a pointer to the image.
 * \param name The base name of the image file. We put images/ onto
 * the front of this because that is where the file is located.
 * \returns Pointer to cached image object or NULL if file not found.
 */
wxImage *CAquarium::GetCachedImage(const std::wstring name)
{
    // See if the name exists in the cache already
    map<wstring, wxImage>::iterator i = mImageCache.find(name);
    if(i != mImageCache.end())
    {
        // If we got here, it does exist and i->second is a
        // reference to the bitmap object.
        return &i->second;
    }
    
    // We'll add the path to the name of the file here.
    wstring realname = DirectoryContainingImages + name;
    
    // Create a bitmap image and load the file into it.
    wxImage bitmap;
    if(!bitmap.LoadFile(realname.c_str()))
    {
        wstring msg = wstring(L"Unable to open image ") + realname;
        wxMessageBox(msg.c_str());
        return NULL;
    }
    
    // Add it to the cache and return it.
    mImageCache[name] = bitmap;
    return &mImageCache[name];
}

/*! \brief Add an item to the aquarium
 * 
 * This automatically centers the new item in the background image
 *
 * \param item New item to add
 */
void CAquarium::AddItem(CItem *item)
{
    item->SetLocation(mBackground.GetWidth()/2, mBackground.GetHeight()/2);
    mItems.push_back(item);
}

/*! \brief Test an x,y click location to see if it clicked
 * on some item in the aquarium
 *
 * \param x X location
 * \param y Y location
 * \returns Pointer item we clicked on or null if none
 */
CItem *CAquarium::HitTest(int x, int y)
{
    for(list<CItem *>::reverse_iterator i=mItems.rbegin();
            i != mItems.rend(); i++)
    {
        if((*i)->HitTest(x, y))
        {
            return *i;
        }
    }
    return NULL;
}

/*! \brief Moves the given item to the front of the aquarium
 *
 * \param item The item to be moved to the front.
 */
void CAquarium::MoveToFront(CItem *item)
{
    mItems.remove(item);
    mItems.push_back(item);
}

/*! \brief Toggles the trashcan
 *
 * If the trashcan is already visible it is hidden, if it is not already
 * visible it draws it.
 */
void CAquarium::ToggleTrashcan()
{
    mTrashCanActive = !mTrashCanActive;
}


/*! \brief Toggles the hand icon
 *
 * toggles the hand icon between normal and scroll modes
 *
 */
void CAquarium::ToggleHand()
{
    mNavActive = !mNavActive;
}


/*! \brief Detects whether the current item is over the trashcan
 *
 * \param x X coordinate
 * \param y Y coordinate
 * \returns true if over the trashcan
 */
bool CAquarium::IsOverTrashcan(int x, int y)
{
    if(!mTrashCanActive)
    {
        return false;
    }
    
    return x < TrashCanWidth && y < TrashCanHeight;
}

/*! \brief Deletes the given item
 *
 * \param item The item to delete
 */
void CAquarium::DeleteItem(CItem *item)
{
    mItems.remove(item);
    delete item;
}

/*! \brief Counts the number of beta fish currently in the aquarium
 *
 * \returns the number of beta fish
 */
int CAquarium::CountBetas()
{
    // Create the visitor object
    CCountFishVisitor visitor;
    
    // Call accept for the aquarium
    Accept(&visitor);
    
    // Get the number of beta fish
    return visitor.GetNumBeta();
}

/*! \brief Save the aquarium as a .aqua XML file.
 * 
 * Open an XML file and stream the aquarium data to it.
 *
 * \param filename - The filename of the file to save the aquarium to
 */
void CAquarium::Save(const std::wstring &filename)
{
    // Create an empty XML document
    wxXmlDocument xmlDoc;
    
    // Create a root node
    wxXmlNode *root = new wxXmlNode(wxXML_ELEMENT_NODE, L"aqua");
    xmlDoc.SetRoot(root);
    
    // This variable keeps track of the last child node we
    // added. There is not yet, so it is initially NULL.
    wxXmlNode *lastChild = NULL;
    
    // Iterate over all of the aquarium items so we can save each to the
    // XML document.
    for(list<CItem *>::const_iterator t=mItems.begin(); t!=mItems.end(); t++)
    {
        // And the tile to create a node for itself
        wxXmlNode *node = (*t)->XmlSave();
        
        // If we have a previous child, add this node after
        // the child.
        if(lastChild == NULL)
        {
            root->AddChild(node);
        }
        else
        {
            lastChild->SetNext(node);
        }
        
        lastChild = node;
    }
    
    // And save the file to disk
    xmlDoc.Save(filename.c_str());
}

/*! \brief Load the aquarium from a .aqua XML file
 * 
 * Opens the XML file and reads the nodes, creating items as appropriate
 *
 * \param filename The filename of the file to load the aquarium from.
 */
void CAquarium::Load(const std::wstring &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename.c_str()))
    {
        wstringstream str;
        str << L"Unable to open file " << filename << ends;
        wxMessageBox(str.str().c_str(),
                     L"Error",
                     wxOK | wxICON_ERROR);
        return;
    }
    
    // Clear our existing aquarium data
    Clear();
    
    wxXmlNode *root = xmlDoc.GetRoot();
    wxXmlNode *child = root->GetChildren();
    while(child != NULL)
    {
        // This is the item we will create
        CItem *item = NULL;
        
        // We have an item. What type?
        wxString type = child->GetAttribute(L"type", L"");
        if(type == L"beta")
        {
            item = new CFishBeta(this);
        }
        else if(type == L"treasure-chest")
        {
            item = new CDecorTreasure(this);
        }
        else if(type == L"catfish")
        {
            item = new CCatfish(this);
        }
        else if(type == L"sparty-fish")
        {
            item = new CFishSparty(this);
        }
        else if(type == L"bubble-treasure-chest")
        {
            item = new CDecorBubbleTreasure(this);
        }
        
        if(item != NULL)
        {
            item->XmlLoad(child);
            mItems.push_back(item);
        }
        
        // Move to the next child
        child = child->GetNext();
    }
}

/*! \brief Clear the aquarium data.
 * 
 * Deletes all known items in the aquarium
 */
void CAquarium::Clear()
{
    while(!mItems.empty())
    {
        delete mItems.front();
        mItems.pop_front();
    }
}

/*! \brief Handle updates for animation
 *
 * \param elapsed The time since the last update
 */
void CAquarium::Update(double elapsed)
{
    for(list<CItem *>::iterator i=mItems.begin();
            i != mItems.end(); i++)
    {
        CItem *item = *i;
        item->SetXOffset(mWindowX);
        item->SetYOffset(mWindowY);
        item->Update(elapsed);
    }
    mFeedTimer = mFeedTimer + elapsed;
    mCleanTimer = mCleanTimer + elapsed;
}

/*! \brief Action for feeding fish
 * 
 * \param
 * \returns
 */
void CAquarium::FeedFish()
{
    mFeedTimer = 0;
}

/*! \brief Action for cleaning tank
 * 
 * \param
 * \returns
 */
void CAquarium::CleanTank()
{
    mCleanTimer = 0;
}

/*! \brief Accept an item visitor
 *
 * \param visitor The item visitor to accept
 */
void CAquarium::Accept(CItemVisitor *visitor)
{
    for(list<CItem *>::iterator i=mItems.begin(); i != mItems.end(); i++)
    {
        CItem *item = *i;
        item->Accept(visitor);
    }
}
