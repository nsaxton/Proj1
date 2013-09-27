/*!
 * \file CApp.h
 *
 * \author Nick Saxton
 *
 * \brief A single object of this type is instantiated to represent
 * the application.
 */

#ifndef CAPP_H
#define	CAPP_H

#include <wx/wx.h>

//! Application main class
class CApp : public wxApp
{
public:
    CApp();
    CApp(const CApp& orig);
    virtual ~CApp();
    
    virtual bool OnInit();
};

#endif	/* CAPP_H */

