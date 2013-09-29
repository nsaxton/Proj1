/*!
 * \file CCountFishVisitor.cpp
 *
 * \author Nick Saxton
 */

#include "CCountFishVisitor.h"

/*! \brief Destructor 
 */
CCountFishVisitor::~CCountFishVisitor()
{
}

/*! \brief Visits a beta fish object and increments number of beta fish
 *
 * \param beta The beta fish object to visit
 */
void CCountFishVisitor::VisitBeta(CFishBeta* beta)
{
    mCntBeta++;
}

/*! \brief Visits a catfish object and increments number of catfish
 *
 * \param catfish The catfish object to visit
 */
void CCountFishVisitor::VisitCatfish(CCatfish* catfish)
{
    mCntCatfish++;
}

/*! \brief Visits a sparty fish object and increments number of sparty fish
 *
 * \param sparty The sparty fish object to visit
 */
void CCountFishVisitor::VisitSparty(CFishSparty* sparty)
{
    mCntSparty++;
}