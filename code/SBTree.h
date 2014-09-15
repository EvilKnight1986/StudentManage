// SBTree.h: interface for the SBTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SBTREE_H__F79D9CF8_A500_4250_8278_2A28E6C1B3B8__INCLUDED_)
#define AFX_SBTREE_H__F79D9CF8_A500_4250_8278_2A28E6C1B3B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MyList.h"

class SBTNode
{
public:
    SBTNode() ;
    SBTNode(unsigned int nValue) ;
    ~SBTNode(){}
public:
    SBTNode * left   ;
    SBTNode * right  ;
    SBTNode * parent ;
    unsigned int key ;
    MyList     list  ;
    int       hight  ;
};

class SBTree  
{
public:
	void Maintain(SBTNode * T, bool flag) ;
	void Rank(void);
	SBTNode * Find(unsigned int nValue) ;
	void Insert(unsigned int nValue, int Offset) ;
	void RotateRight(SBTNode * T) ;
	void RotateLeft (SBTNode * T) ;
        SBTree();
	~SBTree();
private:
        void rank(SBTNode * T) ;
        void Destroy(SBTNode * T);
        SBTNode * m_pRoot;
};

#endif // !defined(AFX_SBTREE_H__F79D9CF8_A500_4250_8278_2A28E6C1B3B8__INCLUDED_)
