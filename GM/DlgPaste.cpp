// DlgPaste.cpp : implementation file
//
// Copyright (c) 1994-2020 By Dale L. Larson, All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "stdafx.h"
#include "Gm.h"
#include "DlgPaste.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPasteBitmapDialog dialog


CPasteBitmapDialog::CPasteBitmapDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CPasteBitmapDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(CPasteBitmapDialog)
    m_nPasteAction = -1;
    //}}AFX_DATA_INIT
}

void CPasteBitmapDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CPasteBitmapDialog)
    DDX_Radio(pDX, IDC_D_PASTE_KEEPSIZE, m_nPasteAction);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPasteBitmapDialog, CDialog)
    //{{AFX_MSG_MAP(CPasteBitmapDialog)
        // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
    ON_WM_HELPINFO()
    ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Html Help control ID Map

static DWORD adwHelpMap[] =
{
    IDC_D_PASTE_KEEPSIZE, IDH_D_PASTE_KEEPSIZE,
    IDC_D_PASTE_RESIZE, IDH_D_PASTE_RESIZE,
    0,0
};

BOOL CPasteBitmapDialog::OnHelpInfo(HELPINFO* pHelpInfo)
{
    return GetApp()->DoHelpTipHelp(pHelpInfo, adwHelpMap);
}

void CPasteBitmapDialog::OnContextMenu(CWnd* pWnd, CPoint point)
{
    GetApp()->DoHelpWhatIsHelp(pWnd, adwHelpMap);
}

