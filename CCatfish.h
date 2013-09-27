/*!
 * \file CCatfish.h
 *
 * \author Nick Saxton
 *
 * \brief Class for a catfish
 * 
 * 
 */

#ifndef CCATFISH_H
#define	CCATFISH_H

#include <string>

#include "CFish.h"

//! Class that implements a fish of type catfish
class CCatfish : public CFish
{
public:
    CCatfish(CAquarium *aquarium);
    
    //! Copy constructor
    CCatfish(const CCatfish& orig) : CFish(orig) {}
    
    virtual ~CCatfish();
    
    virtual wxXmlNode *XmlSave();
    
    virtual CItem *Clone();
        
private:
    //! Default constructor (disabled)
    CCatfish();
};

#endif	/* CCATFISH_H */

