/*!
 * \file CFishSparty.h
 *
 * \author Nick Saxton
 *
 * \brief Class for a Sparty fish
 * 
 * 
 */

#ifndef CFISHSPARTY_H
#define	CFISHSPARTY_H

#include <string>

#include "CFish.h"
#include "CFishVisitor.h"

//! Class that implements a fish of type Sparty
class CFishSparty : public CFish
{
public:
    CFishSparty(CAquarium *aquarium);  
    
    //! Copy constructor
    CFishSparty(const CFishSparty& orig) : CFish(orig) {}
    
    virtual ~CFishSparty();
    
    virtual wxXmlNode *XmlSave();
    
    virtual CItem *Clone();
    
    /*! \brief Accepts a fish visitor
     *
     * \param visitor The fish visitor to accept
     */
    virtual void Accept(CItemVisitor *visitor) {visitor->VisitSparty(this);}
        
private:
    //! Default constructor (disabled)
    CFishSparty();
};

#endif	/* CFISHSPARTY_H */

