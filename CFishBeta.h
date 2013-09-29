/*!
 * \file CFishBeta.h
 *
 * \author Nick Saxton
 *
 * \brief Class for a Beta fish
 * 
 * 
 */

#ifndef CFISHBETA_H
#define	CFISHBETA_H

#include <string>

#include "CFish.h"
#include "CFishVisitor.h"

//! Class that implements a fish of type Beta
class CFishBeta : public CFish
{
public:
    CFishBeta(CAquarium *aquarium);
    
    virtual ~CFishBeta();
        
    //! Copy constructor
    CFishBeta(const CFishBeta& orig) : CFish(orig) {}
    
    virtual bool IsBetaFish() {return true;}
    
    virtual wxXmlNode *XmlSave();
    
    virtual CItem *Clone();
    
    /*! \brief Accepts a fish visitor
     *
     * \param visitor The fish visitor to accept
     */
    virtual void Accept(CItemVisitor *visitor) {visitor->VisitBeta(this);}
    
private:
    //! Default constructor (disabled)
    CFishBeta();
};

#endif	/* CFISHBETA_H */

