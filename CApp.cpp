/*!
 * \file CApp.cpp
 *
 * \author Nick Saxton
 */

#include "CApp.h"
#include "CFrame.h"

IMPLEMENT_APP(CApp)

/*! \brief Constructor
 *
 * This constructs the application class 
 */
CApp::CApp()
{
    srand(time(NULL));
}

/*! \brief Copy constructor
 */
CApp::CApp(const CApp& orig)
{
}

/*! \brief Destructor
 */
CApp::~CApp()
{
}

/*! Application initialization function 
 *
 * This function is called once when the
 * application is started. It creates the main frame for
 * the program and displays it. 
 * \returns true
 */
bool CApp::OnInit()
{
    wxInitAllImageHandlers();
    CFrame *frame = new CFrame();
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}