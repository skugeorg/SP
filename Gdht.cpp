#ifndef __rbt_h_
#define __rbt_h_

#include <iostream>
#include <cstdio>
#include <cstring>
#include "def.h"

/* Red-black tree representation type */
struct rbtree
{
  /* Node color representation type */
  enum rbcolor { eRED, eBLACK }; /* End of 'rbcolor' enum */

  /* Tree node representation type */
  struct node
  {
    INT Key;               /* Node key value */
    rbcolor Color;         /* Node color value */
    node *Less, *More,     /* Node subtree pointers */
         *Parent;          /* Node parent pointer */

    /* Node draw info */
    DBL X, Y,              /* Current node position */
        XDest, YDest;      /* Destination node position */

    /* Class constructor.
     * ARGUMENTS:
     * - new key value:
     *   const INT NewKey;
     * - new color value:
     *   rbcolor NewColor;
     * - new left-right subtree pointer values:
     *   node *NewLess, *NewMore;
     * - new parent pointer value:
     *   node *NewParent;
     */
    node(
      INT NewKey, rbcolor NewColor = eRED,
      node *NewLess = nullptr, node *NewMore = nullptr,
      node *NewParent = nullptr)
      : Key(NewKey), Color(NewColor),
        Less(NewLess), More(NewMore), Parent(NewParent),
        X(0), Y(0), XDest(0), YDest(0)
    {
    } /* End of 'node' function */
  }; /* End of 'node' structure */

  /* Tree root pointer */
  node *Root;

  /* Class default constructor */
  rbtree(VOID) : Root(nullptr)
  {
  } /* End of 'rbtree' function */

  /* Class destructor */
  ~rbtree(VOID)
  {
    Clear(&Root);
  } /* End of '~rbtree' function */

  /* Remove copying constructor */
  rbtree(const rbtree &) = delete;
  /* Remove assignment operator */
  rbtree &operator=(const rbtree &) = delete;

  /* Clear all tree nodes function.
   * ARGUMENTS:
   * - pointer to top node pointer:
   *   node **T;
   * RETURNS: None.
   */
  VOID Clear(node **T = nullptr)
  {
    if (T == nullptr)
      Clear(&Root);
    else if (*T != nullptr)
    {
      Clear(&(*T)->Less);
      Clear(&(*T)->More);
      delete *T;
      *T = nullptr;
    }
  } /* End of 'Clear' function */

  /* Check if node color is black function.
   * ARGUMENTS:
   * - node to check:
   *   node *Nd;
   * RETURNS:
   * (BOOL) TRUE if node color is black, FALSE if it is red one.
   */
  BOOL IsBlack(node *Nd)
  {
    return Nd == nullptr || Nd->Color == eBLACK;
  } /* End of 'IsBlack' function */

  /* Rotate node to left (counter clock wise) function.
   * ARGUMENTS:
   * - node to be rotated:
   *   node *X;
   * RETURNS: None.
   */
  VOID LeftRotate(node *X)
  {
    node *Y = X->More;
    X->More = Y->Less;

    if (Y->Less != nullptr)
      Y->Less->Parent = X;

    Y->Parent = X->Parent;

    if (X->Parent == nullptr)
      Root = Y;
    else if (X == X->Parent->Less)
      X->Parent->Less = Y;
    else
      X->Parent->More = Y;

    Y->Less = X;
    X->Parent = Y;
  } /* End of 'LeftRotate' function */

  /* Rotate node to right (clock wise) function.
   * ARGUMENTS:
   * - node to be rotated:
   *   node *Y;
   * RETURNS: None.
   */
  VOID RightRotate(node *Y)
  {
    node *X = Y->Less;
    Y->Less = X->More;

    if (X->More != nullptr)
      X->More->Parent = Y;

    X->Parent = Y->Parent;

    if (Y->Parent == nullptr)
      Root = X;
    else if (Y == Y->Parent->Less)
      Y->Parent->Less = X;
    else
      Y->Parent->More = X;

    X->More = Y;
    Y->Parent = X;
  } /* End of 'RightRotate' function */

  /* Fix red-black tree properties after insertion function.
   * ARGUMENTS:
   * - newly inserted node:
   *   node *Z;
   * RETURNS: None.
   */
  VOID CorrectInsert(node *Z)
  {
    while (Z->Parent != nullptr && Z->Parent->Color == eRED)
    {
      node *Grandparent = Z->Parent->Parent;
      if (Grandparent == nullptr)
        break;

      if (Z->Parent == Grandparent->Less)
      {
        node *Uncle = Grandparent->More;

        if (!IsBlack(Uncle))
        {
          Z->Parent->Color = eBLACK;
          Uncle->Color = eBLACK;
          Grandparent->Color = eRED;
          Z = Grandparent;
        }
        else
        {
          if (Z == Z->Parent->More)
          {
            Z = Z->Parent;
            LeftRotate(Z);
          }
          Z->Parent->Color = eBLACK;
          Grandparent->Color = eRED;
          RightRotate(Grandparent);
        }
      }
      else
      {
        node *Uncle = Grandparent->Less;

        if (!IsBlack(Uncle))
        {
          Z->Parent->Color = eBLACK;
          Uncle->Color = eBLACK;
          Grandparent->Color = eRED;
          Z = Grandparent;
        }
        else
        {
          if (Z == Z->Parent->Less)
          {
            Z = Z->Parent;
            RightRotate(Z);
          }
          Z->Parent->Color = eBLACK;
          Grandparent->Color = eRED;
          LeftRotate(Grandparent);
        }
      }
    }
    Root->Color = eBLACK;
  } /* End of 'CorrectInsert' function */

  /* Insert new node function.
   * ARGUMENTS:
   * - key to be inserted:
   *   INT Key;
   * RETURNS: None.
   */
  VOID Insert(INT Key)
  {
    node *NewNode = new node(Key),
         *Parent = nullptr,
         *TreePtr = Root;

    while (TreePtr != nullptr)
    {
      if (Key == TreePtr->Key)
      {
        delete NewNode;
        return;
      }
      Parent = TreePtr;
      TreePtr = NewNode->Key < TreePtr->Key ? TreePtr->Less : TreePtr->More;
    }

    NewNode->Parent = Parent;
    if (Parent == nullptr)
      Root = NewNode;
    else if (NewNode->Key < Parent->Key)
      Parent->Less = NewNode;
    else
      Parent->More = NewNode;

    CorrectInsert(NewNode);
  } /* End of 'Insert' function */

  /* Access/Insert wrapper for compatibility.
   * ARGUMENTS:
   * - key to be inserted:
   *   INT Key;
   * RETURNS: None.
   */
  VOID Acces(INT Key)
  {
    Insert(Key);
  } /* End of 'Acces' function */

  /* Delete node function (Stub for visualization purposes).
   * ARGUMENTS:
   * - key to be deleted:
   *   INT Key;
   * RETURNS: None.
   */
  VOID Delete(INT Key)
  {
    /* Full Red-Black deletion is complex and omitted for brevity.
     * This is a placeholder to prevent linker errors. */
    std::cout << "Delete called for key: " << Key << " (Stub)" << std::endl;
  } /* End of 'Delete' function */

  /* Draw tree to console function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID Draw(VOID)
  {
    Put();
  } /* End of 'Draw' function */

  /* Search node by key function.
   * ARGUMENTS:
   * - key to search:
   *   INT Key;
   * RETURNS:
   * (node *) pointer to found node, or nullptr if not found.
   */
  node *Search(INT Key)
  {
    node *Current = Root;
    while (Current != nullptr)
    {
      if (Key == Current->Key)
        return Current;
      Current = Key < Current->Key ? Current->Less : Current->More;
    }
    return nullptr;
  } /* End of 'Search' function */

  /* Output all tree nodes function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID Put(VOID)
  {
    Put(Root);
    std::cout << std::endl;
  } /* End of 'Put' function */

  /* Output tree node with subtrees function.
   * ARGUMENTS:
   * - tree node pointer:
   *   node *T;
   * RETURNS: None.
   */
  VOID Put(node *T)
  {
    if (T == nullptr)
      std::cout << "\x1b[38;2;55;55;55mNIL\x1b[38;2;255;255;255m";
    else
    {
      std::cout << T->Key
                << (T->Color == eBLACK
                      ? "\x1b[38;2;55;55;55m[B]"
                      : "\x1b[38;2;255;5;5m[R]")
                << "\x1b[38;2;255;255;255m";
      std::cout << "(";
      Put(T->Less);
      std::cout << ",";
      Put(T->More);
      std::cout << ")";
    }
  } /* End of 'Put' function */

  /* Count total nodes in subtree.
   * ARGUMENTS:
   * - tree node pointer:
   *   node *T;
   * RETURNS:
   * (INT) number of nodes.
   */
  INT CountNodes(node *T)
  {
    if (T == nullptr)
      return 0;
    return 1 + CountNodes(T->Less) + CountNodes(T->More);
  } /* End of 'CountNodes' function */

  /* Get maximum depth of subtree.
   * ARGUMENTS:
   * - tree node pointer:
   *   node *T;
   * RETURNS:
   * (INT) maximum depth.
   */
  INT GetMaxDepth(node *T)
  {
    if (T == nullptr)
      return 0;
    INT l = GetMaxDepth(T->Less);
    INT r = GetMaxDepth(T->More);
    return 1 + (l > r ? l : r);
  } /* End of 'GetMaxDepth' function */

  /* Helper to calculate X and Y coordinates.
   * ARGUMENTS:
   * - current node:
   *   node *T;
   * - current horizontal index:
   *   INT &count;
   * - current depth:
   *   INT depth;
   * - horizontal step:
   *   INT xStep;
   * - vertical step:
   *   INT yStep;
   * RETURNS: None.
   */
  VOID SetXYHelper(node *T, INT &count, INT depth, INT xStep, INT yStep)
  {
    if (T == nullptr)
      return;
    
    SetXYHelper(T->Less, count, depth + 1, xStep, yStep);
    
    count++;
    T->X = count * xStep;
    T->Y = (depth + 1) * yStep;
    T->XDest = T->X;
    T->YDest = T->Y;
    
    SetXYHelper(T->More, count, depth + 1, xStep, yStep);
  } /* End of 'SetXYHelper' function */

  /* Calculate X and Y coordinates for drawing.
   * ARGUMENTS:
   * - window width:
   *   INT Width;
   * - window height:
   *   INT Height;
   * RETURNS: None.
   */
  VOID SetXY(INT Width, INT Height)
  {
    INT total = CountNodes(Root);
    if (total == 0)
      return;
    
    INT count = 0;
    INT maxDepth = GetMaxDepth(Root);
    
    INT xStep = Width / (total + 1);
    if (xStep < 40)
      xStep = 40; /* Minimum horizontal spacing */
    
    INT yStep = Height / (maxDepth + 2);
    if (yStep < 50)
      yStep = 50; /* Minimum vertical spacing */

    SetXYHelper(Root, count, 0, xStep, yStep);
  } /* End of 'SetXY' function */

  /* Display tree on given HDC.
   * ARGUMENTS:
   * - device context:
   *   HDC hDC;
   * RETURNS: None.
   */
  VOID Display(HDC hDC)
  {
    HFONT hFont = CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
                             CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
    HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

    DisplayHelper(Root, hDC);

    SelectObject(hDC, hOldFont);
    DeleteObject(hFont);
  } /* End of 'Display' function */

  /* Helper recursive function for Display.
   * ARGUMENTS:
   * - current node:
   *   node *T;
   * - device context:
   *   HDC hDC;
   * RETURNS: None.
   */
  VOID DisplayHelper(node *T, HDC hDC)
  {
    if (T == nullptr)
      return;

    INT radius = 20;

    /* 1. Draw connections (lines) to children FIRST, so they appear UNDER circles */
    HPEN hLinePen = CreatePen(PS_SOLID, 2, RGB(80, 80, 80));
    HPEN hOldLinePen = (HPEN)SelectObject(hDC, hLinePen);

    if (T->Less != nullptr)
    {
      MoveToEx(hDC, (INT)T->X, (INT)T->Y, nullptr);
      LineTo(hDC, (INT)T->Less->X, (INT)T->Less->Y);
    }
    if (T->More != nullptr)
    {
      MoveToEx(hDC, (INT)T->X, (INT)T->Y, nullptr);
      LineTo(hDC, (INT)T->More->X, (INT)T->More->Y);
    }

    SelectObject(hDC, hOldLinePen);
    DeleteObject(hLinePen);

    /* 2. Draw the node circle */
    HBRUSH hBrush = (T->Color == eBLACK) ? CreateSolidBrush(RGB(40, 40, 40)) : CreateSolidBrush(RGB(220, 50, 50));
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
    HPEN hCirclePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HPEN hOldCirclePen = (HPEN)SelectObject(hDC, hCirclePen);

    Ellipse(hDC, (INT)T->X - radius, (INT)T->Y - radius, (INT)T->X + radius, (INT)T->Y + radius);

    SelectObject(hDC, hOldBrush);
    SelectObject(hDC, hOldCirclePen);
    DeleteObject(hBrush);
    DeleteObject(hCirclePen);

    /* 3. Draw the number (Key) inside the circle */
    CHAR str[32];
    sprintf_s(str, "%d", T->Key);
    
    SetTextColor(hDC, RGB(255, 255, 255));
    SetBkMode(hDC, TRANSPARENT);
    
    SIZE sz;
    GetTextExtentPoint32(hDC, str, (INT)strlen(str), &sz);
    TextOut(hDC, (INT)T->X - sz.cx / 2, (INT)T->Y - sz.cy / 2, str, (INT)strlen(str));

    /* 4. Recursively draw children */
    DisplayHelper(T->Less, hDC);
    DisplayHelper(T->More, hDC);
  } /* End of 'DisplayHelper' function */

}; /* End of 'rbtree' structure */
#endif /* __rbt_h_ */
