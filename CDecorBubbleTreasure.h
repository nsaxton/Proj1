/*!
 * \file CDecorBubbleTreasure.h
 *
 * \author Nick Saxton
 *
 * \brief Class for a treasure chest decor item
 * 
 * 
 */

#ifndef CDECORBUBBLETREASURE_H
#define	CDECORBUBBLETREASURE_H

#include <string>

#include "CItem.h"
#include "CAquarium.h"

//! Class that implements an opening treasure chest decor item
class CDecorBubbleTreasure : public CItem
{
public:
    CDecorBubbleTreasure(CAquarium *aquarium);
        
    //! Copy constructor
    CDecorBubbleTreasure(const CDecorBubbleTreasure& orig) : CItem(orig) {}
    
    virtual ~CDecorBubbleTreasure();
    
    virtual wxXmlNode *XmlSave();
    
    virtual CItem *Clone();
    void Update(double elapsed);
    
    virtual void Accept(CItemVisitor *visitor);
        
private:
    //! Default constructor (disabled)
    CDecorBubbleTreasure();
    
    //! Current Time
    double mCurTime;
};

#endif	/* CDECORBUBBLETREASURE_H */

