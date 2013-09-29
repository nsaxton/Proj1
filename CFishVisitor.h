/*!
 * \file CFishVisitor.h
 *
 * \author Nick Saxton
 *
 * \brief Visitor pattern for fish in the aquarium
 * 
 * 
 */

#ifndef CFISHVISITOR_H
#define	CFISHVISITOR_H

#include "CItemVisitor.h"

class CFishVisitor : public CItemVisitor
{
public:
    CFishVisitor();
    virtual ~CFishVisitor();
    
    virtual void VisitCatfish(CCatfish *catfish){}
    virtual void VisitBeta(CFishBeta *beta){}
    virtual void VisitSparty(CFishSparty *sparty){}
};

#endif	/* CFISHVISITOR_H */

