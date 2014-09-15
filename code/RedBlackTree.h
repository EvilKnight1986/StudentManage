// RedBlackTree.h: interface for the RedBlackTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REDBLACKTREE_H__36010BDB_D651_426D_94D2_2CED692385AD__INCLUDED_)
#define AFX_REDBLACKTREE_H__36010BDB_D651_426D_94D2_2CED692385AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MyList.h"

enum rg_color { red, black} ;

class TreeNode
{
public:
    TreeNode():left(NULL),right(NULL),parent(NULL), key(0),pList(NULL),color(red)
    {
        pList = new MyList ;
    }
    TreeNode(int nValue):left(NULL),right(NULL),parent(NULL),key(nValue),\
            color(red)
    {
        pList = new MyList ;
    }
    ~TreeNode()
    {
        if (pList)
        {
            delete pList ;
            pList = NULL ;
        }
    }
public:
    TreeNode * left   ;
    TreeNode * right  ;
    TreeNode * parent ;
    unsigned int key  ;
    MyList  * pList   ;
    rg_color   color  ;
};

class RedBlackTree
{
public:
    int  Clear(void) ;
    void RecursionPreorder(TreeNode * T) ;
    int  ExportFile(const char * szFileName) ;
    int  ImportFile(const char * szFileName) ;
    void Inorder(void) ;
    void Postorder(void) ;
    void Preorder(void) ;
    int  Remove(const char * szStr, int Offset) ;
    int  Insert(const char *szStr, int Offset) ;
    MyList * Search(unsigned int nValue) ;
    TreeNode *  FindMax(TreeNode * T) ;
    TreeNode *  FindMin(TreeNode * T) ;
    MyList * Find(const char * szStr) ;
public:
    RedBlackTree()  ;
    ~RedBlackTree() ;
private:
    TreeNode * InsertNoRotate(unsigned int nValue, int Color);
    void Delete(TreeNode *T, unsigned int nValue) ;
    void rotateRight(TreeNode * pNode) ;
    void rotateLeft(TreeNode  * pNode) ;
    void removeFixup(TreeNode * pNode) ;
    void insertFixup(TreeNode * pNode) ;
    void Destory(TreeNode *T)   ;
    void inorder(TreeNode * T)  ;
    void postorder(TreeNode * T);
    void preorder(TreeNode * T) ;
    TreeNode * getGrandParent (const TreeNode *pNode) ;
    TreeNode * getSibling(const TreeNode * pNode) ;
    TreeNode * getUncle(const TreeNode * pNode) ;
    RedBlackTree & operator   =   (const RedBlackTree &obj){} ;
private:
    FILE *fp;
    TreeNode * m_pSentinel ;
    TreeNode * m_pRoot ;
};

#endif // !defined(AFX_REDBLACKTREE_H__36010BDB_D651_426D_94D2_2CED692385AD__INCLUDED_)
