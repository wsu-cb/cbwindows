// LBoxGfx2.h
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

#ifndef _LBOXGFX2_H
#define _LBOXGFX2_H

#ifndef     _DRAGDROP_H
#include    "DragDrop.h"
#endif

class CDrawObj;

/////////////////////////////////////////////////////////////////////////////

#define ID_TIP_LISTITEM_HIT             1
#define MAX_LISTITEM_TIP_WIDTH          200     // Max pixel width of tips

/////////////////////////////////////////////////////////////////////////////
// These messages are sent by the CGrafixListBox2 to its parent window.
// It allows the list's content to be overridden. It's primary use
// is to deliver a random selection of pieces or markers.
#define WM_OVERRIDE_SELECTED_ITEM2       (WM_USER + 500) // WPARAM = int*
#define WM_OVERRIDE_SELECTED_ITEM_LIST2  (WM_USER + 501) // WPARAM = CDWordArray*

/////////////////////////////////////////////////////////////////////////////
// Custom Listbox - containing colors

class CGrafixListBox2 : public CListBox
{
// Construction
public:
    CGrafixListBox2();

// Attributes
public:
    int  GetTopSelectedItem();
    void EnableDrag(BOOL bEnable = TRUE) { m_bAllowDrag = bEnable; }
    void EnableSelfDrop(BOOL bEnable = TRUE) { m_bAllowSelfDrop = bEnable; }
    void EnableDropScroll(BOOL bEnable = TRUE) { m_bAllowDropScroll = bEnable; }
    const std::vector<CB::not_null<CDrawObj*>>* GetItemMap() { return m_pItemMap; }
    CDrawObj& GetCurMapItem();
    void GetCurMappedItemList(std::vector<CB::not_null<CB::propagate_const<CDrawObj*>>>& pLst);
    BOOL IsMultiSelect()
        { return (GetStyle() & (LBS_EXTENDEDSEL | LBS_MULTIPLESEL)) != 0; }
    // Note: the following pointer is only good during drag and drop.
    // the data is only good during the drop. It is essentially a
    // hack to have valid data when selecting items with Shift-Click.
    // Ask Microsoft why I had to do this. The number of selections
    // data in the case of a shift click isn't valid until the button
    // is released. Makes it tough to use a pre setup list during the
    // drag operation.
    std::vector<CB::not_null<CB::propagate_const<CDrawObj*>>>& GetMappedMultiSelectList() { return m_multiSelList; }

// Operations
public:
    void SetItemMap(const std::vector<CB::not_null<CDrawObj*>>* pMap, BOOL bKeepPosition = TRUE);
    void UpdateList(BOOL bKeepPosition = TRUE);
    void SetCurSelMapped(CDrawObj* pMapVal);
    void SetCurSelsMapped(const std::vector<CB::not_null<CDrawObj*>>& items);
    void SetSelFromPoint(CPoint point);
    void ShowFirstSelection();
    CDrawObj& MapIndexToItem(size_t nIndex);
    size_t MapItemToIndex(CDrawObj* pItem);
    void MakeItemVisible(int nItem);

// Overrides - the subclass of this class must override these
public:
    virtual unsigned OnItemHeight(size_t nIndex) /* override */ = 0;
    virtual void OnItemDraw(CDC* pDC, size_t nIndex, UINT nAction, UINT nState,
        CRect rctItem) /* override */ = 0;
    virtual BOOL OnDragSetup(DragInfo* pDI) /* override */
    {
        pDI->m_dragType = DRAG_INVALID;
        return FALSE;
    }
    virtual void OnDragCleanup(DragInfo* pDI) /* override */ { }

    // For tool tip processing
    virtual BOOL OnIsToolTipsEnabled() /* override */ { return FALSE; }
    virtual int  OnGetHitItemCodeAtPoint(CPoint point, CRect& rct) /* override */ { return -1; }
    virtual void OnGetTipTextForItemCode(int nItemCode, CString& strTip, CString& strTitle) /* override */ { }

// Implementation
protected:
    /* N.B.:  this class could be templatized to hold any pointer,
                but that generality isn't actually needed yet */
    const std::vector<CB::not_null<CDrawObj*>>* m_pItemMap;          // Maps index to item
    std::vector<CB::not_null<CB::propagate_const<CDrawObj*>>> m_multiSelList;      // Holds mapped multi select items on drop

    // Tool tip support
    CToolTipCtrl m_toolTip;
    int     m_nCurItemCode;

    // Drag and scroll support vars
    BOOL    m_bAllowDrag;
    BOOL    m_bAllowSelfDrop;       // Only if m_bAllowDrag == TRUE
    BOOL    m_bAllowDropScroll;     // Scroll on OnDragItem

    CPoint  m_clickPoint;
    int     m_nTimerID;
    BOOL    m_triggeredCursor;
    HWND    m_hLastWnd;

    int     m_nLastInsert;          // Last index with insert line

    void  DoInsertLineProcessing(UINT nPhase, DragInfo* pdi);
    void  DoAutoScrollProcessing(DragInfo* pdi);
    void  DoToolTipHitProcessing(CPoint point);

    CWnd* GetWindowFromPoint(CPoint point);
    int   SpecialItemFromPoint(CPoint pnt);
    void  DrawInsert(int nIndex);
    void  DrawSingle(int nIndex);

    // Overrides
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS) override;
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS) override;
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) override;

    //{{AFX_MSG(CGrafixListBox2)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg LRESULT OnDragItem(WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif

