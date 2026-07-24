#pragma once

#include <iostream>

/* Red-black tree type definitions */
using INT  = int;
using BOOL = bool;
using VOID = void;
using DBL  = double;

const BOOL TRUE  = true;
const BOOL FALSE = false;

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
   * Handles the 3 cases of red-red violations described in the lecture.
   * ARGUMENTS:
   * - newly inserted node:
   *   node *Z;
   * RETURNS: None.
   */
  VOID CorrectInsert(node *Z)
  {
    /* While parent of Z is red (property 4 is violated) */
    while (Z->Parent != nullptr && Z->Parent->Color == eRED)
    {
      node *Grandparent = Z->Parent->Parent;
      if (Grandparent == nullptr)
        break;

      /* If parent is the left child of grandparent */
      if (Z->Parent == Grandparent->Less)
      {
        node *Uncle = Grandparent->More; /* Uncle is the right child */

        /* Case 1: Uncle is RED -> Recolor parents and grandparent */
        if (!IsBlack(Uncle))
        {
          Z->Parent->Color = eBLACK;
          Uncle->Color = eBLACK;
          Grandparent->Color = eRED;
          Z = Grandparent; /* Move up to grandparent and repeat */
        }
        /* Uncle is BLACK (or NIL) */
        else
        {
          /* Case 2: Z is right child (triangle) -> Left rotate to make it Case 3 */
          if (Z == Z->Parent->More)
          {
            Z = Z->Parent;
            LeftRotate(Z);
          }
          /* Case 3: Z is left child (line) -> Recolor and right rotate grandparent */
          Z->Parent->Color = eBLACK;
          Grandparent->Color = eRED;
          RightRotate(Grandparent);
        }
      }
      /* Mirror image: parent is the right child of grandparent */
      else
      {
        node *Uncle = Grandparent->Less;

        /* Case 1: Uncle is RED -> Recolor */
        if (!IsBlack(Uncle))
        {
          Z->Parent->Color = eBLACK;
          Uncle->Color = eBLACK;
          Grandparent->Color = eRED;
          Z = Grandparent;
        }
        /* Uncle is BLACK (or NIL) */
        else
        {
          /* Case 2: Z is left child (triangle) -> Right rotate to make it Case 3 */
          if (Z == Z->Parent->Less)
          {
            Z = Z->Parent;
            RightRotate(Z);
          }
          /* Case 3: Z is right child (line) -> Recolor and left rotate grandparent */
          Z->Parent->Color = eBLACK;
          Grandparent->Color = eRED;
          LeftRotate(Grandparent);
        }
      }
    }
    /* Property 2: Root must always be black */
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

    /* Standard BST search for the insertion point */
    while (TreePtr != nullptr)
    {
      if (Key == TreePtr->Key)
      {
        delete NewNode; /* Duplicate keys are not allowed */
        return;
      }
      Parent = TreePtr;
      TreePtr = NewNode->Key < TreePtr->Key ? TreePtr->Less : TreePtr->More;
    }

    /* Link the new node to its parent */
    NewNode->Parent = Parent;
    if (Parent == nullptr)
      Root = NewNode; /* Tree was empty */
    else if (NewNode->Key < Parent->Key)
      Parent->Less = NewNode;
    else
      Parent->More = NewNode;

    /* Fix any violated red-black properties */
    CorrectInsert(NewNode);
  } /* End of 'Insert' function */

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

}; /* End of 'rbtree' structure */
