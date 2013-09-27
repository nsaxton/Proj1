/*!
 * \file CFish.h
 *
 * \author Nick Saxton
 *
 * \brief Base class describing a fish
 * 
 * 
 */

#ifndef CFISH_H
#define	CFISH_H

#include <string>

#include "CItem.h"
#include "CAquarium.h"

/*! \brief Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class CFish : public CItem
{
public:
    virtual ~CFish();
    CFish(const CFish &original);
    
    void Update(double elapsed);
    
    virtual wxXmlNode *XmlSave(); 
    virtual void XmlLoad(wxXmlNode *node);
    
    void SetSpeed(double x, double y);
        
protected:
    CFish(CAquarium *aquarium, const std::wstring &filename);
    
private:
    //! Default constructor (disabled))
    CFish();
    
    //! Fish speed in the X direction
    double mSpeedX;
    
    //! Fish speed in the Y direction
    double mSpeedY;
};

#endif	/* CFISH_H */

