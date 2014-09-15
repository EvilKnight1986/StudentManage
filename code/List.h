// List.h: interface for the List class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIST_H__CFDEEA1C_9BA0_4FB9_B4C3_C87B4E3EC490__INCLUDED_)
#define AFX_LIST_H__CFDEEA1C_9BA0_4FB9_B4C3_C87B4E3EC490__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <io.h>
#include <stdio.h>
#include <stdlib.h>

#if _MSC_VER >= 1400
#include <iostream>
using namespace std ;
#else
#include <iostream.h>
#endif 

class DistNode
{
public:
    DistNode(int Data,int Offset):data(Data),offset(Offset),next(NULL){}
    unsigned int GetData()   { return data;   }
    unsigned int GetOffset() { return offset; }
public:
    unsigned int data   ;
    unsigned int offset ;
    DistNode  *  next   ;
};

typedef DistNode * DistPosition ;
typedef DistPosition DistList ;

class List  
{
public:
    DistPosition operator [] (unsigned int index) ;
    int GetSize(void);
    DistNode * Top(void);
    unsigned int Pop(void);
    int Push(unsigned int data, unsigned int offset);
    int Delete(unsigned int data);
    int InsertLast(unsigned int data, unsigned int offset);
    int InsertPrev(unsigned int data, unsigned int offset);
    int Insert(unsigned int data,  unsigned int offset,int nIndex);
    DistPosition FindPrev(unsigned int data);
    DistPosition Find(unsigned int data);
    int IsEmpty(void);
public:
    int Clear();
    List();
    ~List();
private:
    DistList pHead;
    DistList pLast;
    unsigned int nSize;
};

#endif // !defined(AFX_LIST_H__CFDEEA1C_9BA0_4FB9_B4C3_C87B4E3EC490__INCLUDED_)
