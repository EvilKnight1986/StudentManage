// List.cpp: implementation of the List class.
//
//////////////////////////////////////////////////////////////////////

#include "List.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

List::List():pHead(NULL),pLast(NULL),nSize(0)
{
}

List::~List()
{
    DistList p ;
    while (pHead != NULL)
    {
        p = pHead ;
        pHead = pHead->next ;
        delete p ;
    }
    pHead = pLast = NULL ;
}

DistPosition  List::operator [] (unsigned int index)
{
    if (index < 0 || index > nSize)
    {
        exit (EXIT_FAILURE);
    }
    
    unsigned int i(0) ;
    DistList p = pHead;
    for (; i < index; ++i)
    {
        p = p->next ;
    }
    return p ;
}

int List::IsEmpty()
{
    return nSize == 0 ? 1 : 0 ;
}

DistPosition List::Find(unsigned int data)
{
    if (pHead == NULL)
    {
        return NULL ;
    }
    else if (pHead != NULL && pHead->data == data)
    {
        return pHead ;
    }

    DistPosition p = NULL ;
    p = FindPrev(data) ;
    if( p != NULL)
    {
        return p->next ;
    }
    return NULL ;
}

DistPosition List::FindPrev(unsigned int data)
{
    DistPosition p = pHead ;
    if (p == NULL || p->next == NULL)
    {
        return NULL ;
    }
    
    for(; p->next != NULL && p->next->data != data; p = p->next)
        ;
    
    return p ;
}

int List::Insert(unsigned int data,  unsigned int offset,int nIndex)
{
    int i = 0;
    DistPosition p = pHead ;
    DistPosition tmp = new DistNode(data, offset) ;
    
    ++nSize ;
    // 如果链表是空的情况下
    if (pHead == NULL)
    {
        pHead = tmp ;
        pLast = tmp ;
        return 1 ;
    }

    for (; i < nIndex && p->next != NULL; p = p->next)
        ;

    tmp->next = p->next ;
    p->next = tmp ;
    if (tmp->next == NULL)
    {
        pLast = NULL ;
    }
    return 1 ;
}

int List::InsertPrev(unsigned int data, unsigned int offset)
{
    DistPosition tmp = new DistNode(data,offset) ;

    ++nSize ;

    tmp->next = pHead ;
    pHead = tmp ;
    if (pLast == NULL)
    {
        pLast = tmp ;
    }
    return 1 ;
}

int List::InsertLast(unsigned int data, unsigned int offset)
{
    DistPosition tmp = new DistNode(data, offset) ;

    ++nSize ;

    // 如果链表为空的情况
    if (pLast == NULL && pHead == NULL)
    {
        pLast = pHead = tmp ;
    }
    else
    {
        pLast->next = tmp ;
        pLast = tmp ;
    }
    return 1 ;
}

int List::Delete(unsigned int data)
{
    DistPosition p = FindPrev(data) ;

    if (p != NULL)
    {
        DistPosition tmp = p->next ;
        p->next = tmp->next ;
        --nSize ;
        delete tmp ;
        return 1 ;
    }
    else if (pHead != NULL && pHead->data == data)
    {
        p = pHead ;
        pHead = pLast = NULL ;
        --nSize ;
        delete p ;
    }
    return 0 ;
}


int List::Push(unsigned int data, unsigned int offset)
{
    return InsertPrev(data, offset) ;
}

unsigned int List::Pop()
{
    if (pHead != NULL)
    {
        int data(0) ;
        DistPosition tmp = pHead ;
        pHead = pHead->next ;
        data = tmp->data ;
        delete tmp ;
        --nSize ;
        return data ;        
    }
    return 0 ;
}

DistNode * List::Top()
{
    return (pHead != NULL)?pHead:NULL;
}

int List::GetSize()
{
    return nSize ;
}

int List::Clear()
{
    DistList p ;
    while (pHead != NULL)
    {
        p = pHead ;
        pHead = pHead->next ;
        delete p ;
    }
    pHead = pLast = NULL ;
    nSize = 0 ;
    return 1 ;
}
