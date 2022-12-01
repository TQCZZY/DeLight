// DataCenter.h : main header file for the TEAMCHAT application
//

#if !defined(AFX_TEAMCHAT_H__0BEB4B36_10AE_46B6_8107_411F164644D0__INCLUDED_)
#define AFX_TEAMCHAT_H__0BEB4B36_10AE_46B6_8107_411F164644D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDataCenterApp:
// See DataCenter.cpp for the implementation of this class
//

class CDataCenterApp : public CWinApp
{
public:
	CDataCenterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataCenterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDataCenterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEAMCHAT_H__0BEB4B36_10AE_46B6_8107_411F164644D0__INCLUDED_)
