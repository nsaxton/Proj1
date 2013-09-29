/*!
 * \file CCountFishVisitor.h
 *
 * \author Nick Saxton
 *
 * \brief Visitor to count the number of fish of each type
 * 
 * 
 */

#ifndef CCOUNTFISHVISITOR_H
#define	CCOUNTFISHVISITOR_H

#include "CFishVisitor.h"

class CCountFishVisitor : public CFishVisitor
{
public:
    CCountFishVisitor() {mCntCatfish = 0; mCntBeta = 0; mCntSparty = 0;}
    virtual ~CCountFishVisitor();
    
    virtual void VisitCatfish(CCatfish *catfish);
    virtual void VisitBeta(CFishBeta *beta);
    virtual void VisitSparty(CFishSparty *sparty);
    
    int GetNumCatfish() {return mCntCatfish;}
    int GetNumBeta() {return mCntBeta;}
    int GetNumSparty() {return mCntSparty;}
    
private:
    int mCntCatfish;
    int mCntBeta;
    int mCntSparty;
};

#endif	/* CCOUNTFISHVISITOR_H */

