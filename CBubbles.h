/*!
 * \file CBubbles.h
 *
 * \author Nick Saxton
 *
 * \brief Class for bubbles
 * 
 * 
 */

#ifndef CBUBBLES_H
#define	CBUBBLES_H

#include <string>

#include "CItem.h"

//! Class that implements a treasure chest decor item
class CBubbles : public CItem
{
public:
    CBubbles(CAquarium *aquarium);
        
    //! Copy constructor
    CBubbles(const CBubbles& orig) : CItem(orig) {}
    
    virtual ~CBubbles();
    
    virtual wxXmlNode *XmlSave();
    
    virtual CItem *Clone();
    
    virtual void Accept(CItemVisitor *visitor);
    
    void Update(double elapsed);

        
private:
    //! Default constructor (disabled)
    CBubbles();
};

#endif	/* CBUBBLES_H */

