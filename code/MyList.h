// MyList.h: interface for the MyList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLIST_H__C6B7955D_68C6_4D6D_9A9E_6587C741979D__INCLUDED_)
#define AFX_MYLIST_H__C6B7955D_68C6_4D6D_9A9E_6587C741979D__INCLUDED_

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

class node
{
public:
        node(int Data):data(Data),next(NULL){}
public:
        unsigned int data ;
        node * next;
};

typedef node * position ;
typedef position list ;


class MyList  
{
public:
        unsigned int & operator [] (unsigned int index) ;
        int GetSize(void);
        int Top(void);
        int Pop(void);
        int Push(unsigned int data);
        int Delete(unsigned int data);
        int InsertLast(unsigned int data);
        int InsertPrev(unsigned int data);
        int Insert(unsigned int data, int nIndex);
        position FindPrev(unsigned int data);
        position Find(unsigned int data);
        int IsEmpty(void);
public:
        MyList();
        ~MyList();
private:
        list pHead;
        list pLast;
        unsigned int nSize;
};

#endif // !defined(AFX_MYLIST_H__C6B7955D_68C6_4D6D_9A9E_6587C741979D__INCLUDED_)
