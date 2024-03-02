#pragma once
#include <afxext.h>
#include "Resource.h"
#include "Groups.h"
#include <fstream>
#include <string>
#include "MainFrm.h"
#include <gdiplus.h>
using namespace Gdiplus;


class LoginView : public CFormView
{
	DECLARE_DYNCREATE(LoginView)

protected:
	LoginView();
	virtual ~LoginView() {};

public:

	enum { IDD = IDD_LOGIN };
	DECLARE_MESSAGE_MAP()
	afx_msg
	void OnBnClickedOk();
	void OnPaint();
	
public:
	virtual void OnInitialUpdate();
};