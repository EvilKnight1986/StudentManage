// MyList.cpp: implementation of the MyList class.
//
//////////////////////////////////////////////////////////////////////

#include "MyList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyList::MyList():pHead(NULL),pLast(NULL),nSize(0)
{
}

MyList::~MyList()
{
    list p ;
    while (pHead != NULL)
    {
        p = pHead ;
        pHead = pHead->next ;
        delete p ;
    }
    pHead = pLast = 0 ;
}


int MyList::IsEmpty()
{
    return nSize == 0 ? 1 : 0 ;
}

position MyList::Find(unsigned int data)
{
    if (pHead->data == data)
    {
        return pHead ;
    }
    return FindPrev(data)->next ;
}

position MyList::FindPrev(unsigned int data)
{
    position p = pHead ;
    if (p == NULL || p->next == NULL)
    {
        return NULL ;
    }
    
    for(; p->next != NULL && p->next->data != data; p = p->next)
        ;
    
    return p ;
}

int MyList::Insert(unsigned int data, int nIndex)
{
    int i = 0;
    position p = pHead ;
    position tmp = new node(data) ;
    
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

int MyList::InsertPrev(unsigned int data)
{
    position tmp = NULL ;
    tmp = new node(data) ;
    if (tmp == NULL)
    {
        return 0 ;
    }

    ++nSize ;

    tmp->next = pHead ;
    pHead = tmp ;
    if (pLast == NULL)
    {
        pLast = tmp ;
    }
    return 1 ;
}

int MyList::InsertLast(unsigned int data)
{
    position tmp = new node(data) ;
    
    if (tmp == NULL)
    {
        return 0 ;
    }

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

int MyList::Delete(unsigned int data)
{
    position p = FindPrev(data) ;

    if (p != NULL)
    {
        position tmp = p->next ;
        p->next = tmp->next ;
        --nSize ;
        delete tmp ;
        return 1 ;
    }
    return 0 ;
}



int MyList::Push(unsigned int data)
{
    return InsertPrev(data) ;
}

int MyList::Pop()
{
    if (pHead != NULL)
    {
        unsigned int data(0) ;
        position tmp = pHead ;
        pHead = pHead->next ;
        data = tmp->data ;
        delete tmp ;
        --nSize ;
        return data ;        
    }
    return 0 ;
}

int MyList::Top()
{
    return (pHead != NULL)?pHead->data:0;
}

int MyList::GetSize()
{
    return nSize ;
}

unsigned int & MyList::operator [](unsigned int index)
{
    if (index < 0 || index > nSize)
    {
        exit (EXIT_FAILURE);
    }
    
    unsigned int i(0) ;
    list p = pHead;
    for (; i < index; ++i)
    {
        p = p->next ;
    }
    return p->data ;
}
