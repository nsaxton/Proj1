/*!
 * \file CDecorTreasure.h
 *
 * \author Nick Saxton
 *
 * \brief Class for a treasure chest decor item
 * 
 * 
 */

#ifndef CDECORTREASURE_H
#define	CDECORTREASURE_H

#include <string>

#include "CItem.h"

//! Class that implements a treasure chest decor item
class CDecorTreasure : public CItem
{
public:
    CDecorTreasure(CAquarium *aquarium);
        
    //! Copy constructor
    CDecorTreasure(const CDecorTreasure& orig) : CItem(orig) {}
    
    virtual ~CDecorTreasure();
    
    virtual wxXmlNode *XmlSave();
    
    virtual CItem *Clone();
    
    virtual void Accept(CItemVisitor *visitor);

        
private:
    //! Default constructor (disabled)
    CDecorTreasure();
};

#endif	/* CDECORTREASURE_H */

