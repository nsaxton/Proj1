/*!
 * \file CItemVisitor.h
 *
 * \author Nick Saxton
 *
 * \brief Visitor pattern for items in the aquarium
 * 
 * 
 */

#ifndef CITEMVISITOR_H
#define	CITEMVISITOR_H

// Forward references
class CCatfish;
class CFishBeta;
class CFishSparty;
class CDecorTreasure;

class CItemVisitor
{
public:
    CItemVisitor();
    virtual ~CItemVisitor();
    
    virtual void VisitCatfish(CCatfish *catfish){}
    virtual void VisitBeta(CFishBeta *beta){}
    virtual void VisitSparty(CFishSparty *sparty){}
    virtual void VisitTreasure(CDecorTreasure *treasure){}
    
private:

};

#endif	/* CITEMVISITOR_H */

