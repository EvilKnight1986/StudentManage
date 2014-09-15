// SBTree.cpp: implementation of the SBTree class.
//
//////////////////////////////////////////////////////////////////////

#include "SBTree.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SBTNode NIL ;
SBTNode * pNil = &NIL ;

SBTNode::SBTNode():left(pNil),right(pNil),parent(pNil), key(0),hight(1){}
SBTNode::SBTNode(unsigned int nValue):left(pNil),right(pNil),parent(pNil),\
key(nValue),hight(1){}




SBTree::SBTree():m_pRoot(pNil){};
SBTree::~SBTree()
{
    // 递归调用Destroy删除树
    Destroy(m_pRoot) ;
}

void SBTree::RotateLeft(SBTNode * T)
{
    if (T == pNil || T->right == pNil)
    {
        return ;
    }

    /*

           x     右旋转       y
          / \    ---->       / \
         y   C              A   x
        / \      <----         / \
       A   B     左旋转       B   C

    */
    SBTNode * y = T ;
    SBTNode * x = y->right ;
    SBTNode * t = pNil ;

    y->right = x->left ;
    x->left->parent = y ;

    x->left = y ;
    t = y->parent ;
    y->parent = x ;
    x->parent = t ;

    if (x->parent->left == y)
    {
        x->parent->left = x ;
    }
    else if (x->parent->right == y)
    {
        x->parent->right = x ;
    }

    x->hight = y->hight ;
    
    y->hight = y->left->hight + y->right->hight + 1 ;

    if (y == m_pRoot)
    {
        m_pRoot = x ;
    }
}

void SBTree::RotateRight(SBTNode * T)
{
    if (T == NULL || T->left == NULL)
    {
        return ;
    }

    SBTNode * x = T ;
    SBTNode * y = x->left ;
    SBTNode * t = NULL ;

    x->left = y->right ;
    y->right->parent = x ;

    y->right = x ;
    t = y->parent ;
    y->parent = x->parent ;
    x->parent = t ;

    if (y->parent->left == x)
    {
        y->parent->left = y ;
    }
    else if (y->parent->right == x)
    {
        y->parent->right = y ;
    }

    y->hight = x->hight ;

    x->hight = x->left->hight + y->left->hight + 1 ;

    if (x == m_pRoot)
    {
        m_pRoot = y ;
    }
}

void SBTree::Destroy(SBTNode * T)
{
    if (T != NULL)
    {
        Destroy(T->left) ;
        Destroy(T->right) ;
        delete T ;
    }
}

void SBTree::Insert(unsigned int nValue, int Offset)
{
    SBTNode * T = Find(nValue) ;
    // 如果没有找到
    if (T == pNil)
    {
        SBTNode * t = pNil;
        T = m_pRoot ;

        // 如果当前树为空
        if (m_pRoot == pNil)
        {
            SBTNode * tmp = new SBTNode(nValue);
            if (tmp == NULL)
            {
                return ;
            }
            tmp->parent = pNil ;
            m_pRoot = tmp ;
        }

        while (T != pNil)
        {
            if (nValue < T->key && T->left != pNil)
            {
                T->hight += 1 ;
                t = T ;
                T = T->left ;
            }
            else if (nValue > T->key && T->right != pNil)
            {
                T->hight += 1 ;
                t = T ;
                T = T->right ;
            }
            
            else if (nValue < T->key && T->left == pNil)
            {
                SBTNode * tmp = new SBTNode(nValue);
                if (tmp == NULL)
                {
                    return ;
                }
                T->left = tmp ;
                tmp->parent = T ;
                T->hight += 1 ;
                break ;
            }
            else if (nValue > T->key && T->right == pNil)
            {
                SBTNode * tmp = new SBTNode(nValue);
                if (tmp == NULL)
                {
                    return ;
                }
                T->right = tmp ;
                tmp->parent = T ;
                T->hight += 1 ;
                break ;
            } // end of else if
        }// end of while

        for (;t != pNil && t != NULL ; t = t->parent)
        {
            Maintain(t, nValue >= t->key) ;
        }
    }
    else
    {
        T->list.Push(Offset) ;
    }

}

SBTNode * SBTree::Find(unsigned int nValue)
{
    SBTNode * T ;
    T = m_pRoot ;
    while(T != pNil && T->key != nValue)
    {
        if (nValue < T->key)
        {
            T = T->left ; 
        }
        else if (nValue > T->key)
        {
            T = T->right ;
        }
    }
    return pNil ;
}

void SBTree::Rank(void)
{
    rank(m_pRoot) ;
}

void SBTree::Maintain(SBTNode * T, bool flag)
{
    if (flag || T == pNil)
    {
        return ;
    }

    if (T->left != pNil && T != NULL && T->left != NULL \
                            && T->left->left->hight > T->right->hight)
    {
        RotateRight(T) ;
    }
    else if (T->left != pNil && T != NULL && T->left != NULL\
                        && T->left->right->hight > T->right->hight)
    {
        RotateLeft(T->left)  ;
        RotateRight(T) ;
    }
    else if (T->right != pNil && T != NULL && T->right != NULL \
                    && T->right->right->hight > T->left->hight)
    {
        RotateLeft(T) ;
    }
    else if (T->right != pNil && T != NULL && T->right != NULL\
                    && T->right->left->hight > T->left->hight)
    {
        RotateRight(T->right) ;
        RotateLeft(T) ;
    }

    Maintain(T->left, false) ;
    Maintain(T->right, true) ;
    Maintain(T, false) ;
    Maintain(T, true) ;
}

void SBTree::rank(SBTNode * T)
{
    if (T != pNil && T != NULL)
    {
        rank(T->left)  ;
        cout << T->key << "   " << T->hight << endl ;
        rank(T->right) ;
    }
}
