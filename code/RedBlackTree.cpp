// RedBlackTree.cpp: implementation of the RedBlackTree class.
//
//////////////////////////////////////////////////////////////////////

#include "RedBlackTree.h"
#include "Tools.h"
#pragma warning(disable:4996)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RedBlackTree::RedBlackTree():m_pSentinel(NULL), m_pRoot(NULL),fp(NULL)
{
    m_pSentinel = new TreeNode ;

    if (m_pSentinel == NULL)
    {
        exit(EXIT_FAILURE) ;
    }

    m_pSentinel->color  = black ;
    m_pSentinel->left   = m_pSentinel ;
    m_pSentinel->right  = m_pSentinel ;
    m_pSentinel->parent = m_pSentinel ;
    m_pRoot = m_pSentinel ;
}

RedBlackTree::~RedBlackTree()
{
    if (m_pRoot != m_pSentinel)
    {
        Destory(m_pRoot) ;
        m_pRoot = NULL ;
    }
    if (m_pSentinel != NULL)
    {
        delete m_pSentinel ;
        m_pSentinel = NULL ;
    }
}

int RedBlackTree::Insert(const char *szStr, int Offset)
{
    if (szStr == NULL)
    {
        return 0 ;
    }

    unsigned int hashValue = crc32(szStr) ;
    TreeNode * pNode = m_pRoot ;
    TreeNode * tmp = NULL ;

    // 如果树为空的话
    if (m_pRoot == m_pSentinel)
    {
        tmp = new TreeNode(hashValue) ;
        if (tmp == NULL)
        {
            exit(EXIT_FAILURE) ;
        }
         
        tmp->left = tmp->right = tmp->parent = m_pSentinel ;
        tmp->color = red ;
        tmp->pList->Push(Offset) ;

        m_pRoot = tmp ;
        return 1 ;
    }

    for (; pNode != m_pSentinel;)
    {
        if (hashValue < pNode->key && pNode->left != m_pSentinel)
        {
            pNode = pNode->left ;
        }
        else if (hashValue > pNode->key && pNode->right != m_pSentinel)
        {
            pNode = pNode->right ;
        }
        else if (hashValue == pNode->key)
        {
            pNode->pList->Push(Offset) ;
            return 1 ;
        }
        else
        {
            break ;
        }
    }

    if (pNode == m_pSentinel)
    {
        return 0;
    }

    tmp = NULL ;
    tmp = new TreeNode(hashValue) ;
    if (tmp == NULL)
    {
        exit(EXIT_FAILURE) ;
    }
    tmp->left = tmp->right = m_pSentinel ;
    tmp->color = red ;
    tmp->key = hashValue ;
    tmp->parent = pNode ;
    // 往左边插入
    if (hashValue < pNode->key && pNode->left == m_pSentinel)
    {
        pNode->left = tmp ;
    }
    // 入右边插入
    else if (hashValue > pNode->key && pNode->right == m_pSentinel)
    {
        pNode->right = tmp ;
    }
    tmp->pList->Push(Offset) ;
    insertFixup(tmp) ;
    return  1;
}

int RedBlackTree::Remove(const char * szStr, int Offset)
{
    MyList *lst = Find(szStr) ;
    unsigned int hashValue = crc32(szStr) ;
    if (lst != NULL && lst->GetSize() > 1)
    {
        lst->Delete(Offset) ;
        return 1 ;
    }
    else if (lst != NULL)
    {
        Delete(m_pRoot, hashValue) ;
        return 1 ;
    }
    return 0;
}

void RedBlackTree::Destory(TreeNode *T)
{
    if (T != m_pSentinel && T != NULL )
    {
        Destory(T->left) ;
        Destory(T->right) ;
    }
}

MyList * RedBlackTree::Find(const char * szStr)
{
    return Search(crc32(szStr)) ;
}

TreeNode * RedBlackTree::FindMin(TreeNode * T)
{
    if (m_pRoot == m_pSentinel || T == m_pSentinel)
    {
        return NULL ;
    }
    while (T->left != m_pSentinel )
    {
        T = T->left ;
    }
    return T ;
}

TreeNode * RedBlackTree::FindMax(TreeNode * T)
{
    if (m_pRoot == m_pSentinel || T == m_pSentinel)
    {
        return NULL ;
    }
    while (T->right != m_pSentinel )
    {
        T = T->right ;
    }
    return T ;
}

MyList * RedBlackTree::Search(unsigned int nValue)
{
    TreeNode * T = m_pRoot ;
    while (T != m_pSentinel && T->key != nValue)
    {
        if (nValue < T->key)
        {
            T = T->left ;
        }
        else
        {
            T = T->right ;
        }
    }
    
    if (T != m_pSentinel && nValue == T->key)
    {
        return T->pList ;
    }
    
    return NULL ;
}

TreeNode * RedBlackTree::getGrandParent(const TreeNode * pNode)
{
    if (pNode != m_pSentinel && pNode->parent != m_pSentinel)
    {
        return pNode->parent->parent ;
    }
    return m_pSentinel ;
}

TreeNode * RedBlackTree::getUncle(const TreeNode * pNode)
{
    TreeNode * p = getGrandParent(pNode) ;
    if (p == m_pSentinel)
    {
        return m_pSentinel ;
    }

    if (p->left == pNode->parent)
    {
        return p->right ;
    }
    else
    {
        return p->left ;
    }
    return m_pSentinel ;
}

TreeNode * RedBlackTree::getSibling(const TreeNode * pNode)
{
    if (pNode == m_pSentinel || pNode->parent == m_pSentinel || pNode == m_pRoot)
    {
        return m_pSentinel ;
    }

    if (pNode->parent->left == pNode)
    {
        return pNode->parent->right ;
    }
    else
    {
        return pNode->parent->left ;
    }
    return m_pSentinel ;
}

void RedBlackTree::insertFixup(TreeNode * pNode)
{
        if (pNode == m_pSentinel)
        {
            return; // impossible actually.   
        }

        TreeNode * pUncle = m_pSentinel;    
        TreeNode * pGrandParent = NULL;   
        while (pNode != m_pRoot && red == pNode->parent->color)    
        {   
            pUncle = getUncle(pNode);   
            pGrandParent = getGrandParent(pNode);   
            if (pUncle != NULL && pUncle != m_pSentinel && pUncle->color == red)   
            {   
                pNode->parent->color = black;   
                pUncle->color = black;   
                pGrandParent->color = red;   
                pNode = pGrandParent;   
            }   
            else  
            {   
                if (pNode->parent == pGrandParent->left)     
                {   
                    if (pNode == pNode->parent->right)   
                    {   
                        pNode = pNode->parent;   
                        rotateLeft(pNode);   
                    }   
                    pNode->parent->color = black;   
                    pGrandParent->color = red;   
                    rotateRight(pGrandParent);   
                }   
                else  
                {   
                    if (pNode == pNode->parent->left)   
                    {   
                        pNode = pNode->parent;   
                        rotateRight(pNode);   
                    }   
                    pNode->parent->color = black;   
                    pGrandParent->color = red;   
                    rotateLeft(pGrandParent);   
                }   
            }   
        }   
        m_pRoot->color = black;   
}

void RedBlackTree::removeFixup(TreeNode * pNode)
{
    TreeNode * pSibling = NULL;   
    while ((pNode != m_pRoot) && (pNode->color == black))   
    {   
        pSibling = getSibling(pNode);   
        if (pNode == pNode->parent->left) // left child node   
        {   
            if (pSibling->color == red)   
            {   
                // case 1, can change to case 2, 3, 4   
                pNode->parent->color = red;   
                pSibling->color = black;   
                rotateLeft(pNode->parent);   
                // change to new sibling,    
                pSibling = pNode->parent->right;   
            }   
            // case 2;   
            if ((black == pSibling->left->color) && (black == pSibling->right->color))    
            {    
                pSibling->color = red;    
                pNode = pNode->parent;    
            }   
            else  
            {   
                if (black == pSibling->right->color)    
                {    
                    pSibling->color = red;    
                    pSibling->left->color = black;    
                    rotateRight(pSibling);    
                    pSibling = pNode->parent->right;    
                }   
                pSibling->color = pNode->parent->color;   
                pNode->parent->color = black;   
                pSibling->right->color = black;   
                rotateLeft(pNode->parent);   
                break;    
            }   
        }   
        else  
        {   
            if (pSibling->color == red)   
            {   
                // case 1, can change to case 2, 3, 4   
                pNode->parent->color = red;   
                pSibling->color = black;   
                rotateRight(pNode->parent);   
                // change to new sibling,    
                pSibling = pNode->parent->left;   
            }   
            // case 2;   
            if ((black == pSibling->left->color) && (black == pSibling->right->color))    
            {    
                pSibling->color = red;    
                pNode = pNode->parent;    
            }   
            else  
            {   
                if (black == pSibling->left->color)    
                {    
                    pSibling->color = red;    
                    pSibling->right->color = black;    
                    rotateLeft(pSibling);    
                    pSibling = pNode->parent->left;    
                }   
                pSibling->color = pNode->parent->color;   
                pNode->parent->color = black;   
                pSibling->left->color = black;   
                rotateRight(pNode->parent);   
                break;    
            }   
        }   
    }   
    pNode->color = black;   
}

void RedBlackTree::rotateLeft(TreeNode * pNode)
{
    if (pNode == m_pSentinel || pNode == NULL || pNode->right == m_pSentinel \
            || pNode->right == NULL)
    {
        return ;
    }
    TreeNode * x = pNode ;
    TreeNode * y = pNode->right ;

    x->right = y->left ;
    if (y->left != m_pSentinel)
    {
        y->left->parent = x ;
    }
    y->left = x ;
    y->parent = x->parent ;
    x->parent = y ;
    if (x == y->parent->left)
    {
        y->parent->left = y ;
    }
    else
    {
        y->parent->right = y ;
    }
    
    if (pNode == m_pRoot)
    {
        m_pRoot = y ;
    }
}

void RedBlackTree::rotateRight(TreeNode * pNode)
{
    if (pNode == m_pSentinel || pNode->left == m_pSentinel)
    {
        return ;
    }
    
    TreeNode * x = pNode->left ;
    TreeNode * y = pNode ;
    y->left = x->right ;
    if (x->right != m_pSentinel)
    {
        x->right->parent = y ;
    }
    x->right = y ;
    x->parent = y->parent ;
    y->parent = x ;
    if (y == x->parent->left)
    {
        x->parent->left = x ;
    }
    else
    {
        x->parent->right = x ;
    }
    
    if (pNode == m_pRoot)
    {
        m_pRoot = x ;
    }
}

// 先
void RedBlackTree::Preorder(void)
{
    preorder(m_pRoot) ;
}

// 后
void RedBlackTree::Postorder(void)
{
    postorder(m_pRoot) ;
}

// 中
void RedBlackTree::Inorder(void)
{
    inorder(m_pRoot) ;
}

void RedBlackTree::inorder(TreeNode * T)
{
    if (T != m_pSentinel)
    {
        inorder(T->left) ;
        cout << T->key << " " << ((T->color == red)? "red":"black") << endl ;
        inorder(T->right) ;
    }
}

void RedBlackTree::postorder(TreeNode * T)
{
    if (T != m_pSentinel)
    {
        postorder(T->left) ;
        postorder(T->right) ;
        cout << T->key << " " << ((T->color == red)? "red":"black") << endl ;
    }
}

void RedBlackTree::preorder(TreeNode * T)
{
    if (T != m_pSentinel)
    {
        cout << T->key << " " << ((T->color == red)? "red":"black") << endl ;
        preorder(T->left) ;
        preorder(T->right) ;
    }
}

void RedBlackTree::Delete(TreeNode *T, unsigned int nValue)
{
    if (T == NULL || T == m_pSentinel)
    {
        return ;
    }

    while(T != m_pSentinel)
    {
        if (nValue < T->key)
        {
            T = T->left ;
        }
        else if (nValue > T->key)
        {
            T = T->right ;
        }
        else
        {
            break ;
        }
    }

    if (T == m_pSentinel)
    {
        return ;
    }

    if (T->left != m_pSentinel && T->right != m_pSentinel)
    {
        TreeNode * p = FindMin(T->right) ;
        if (p != m_pSentinel && p != NULL)
        {
            T->key = p->key;
            Delete(T->right, T->key) ;
        }
    }

    // 只有左儿子
    else if (T->left)
    {
        TreeNode * p = T ;

        if (m_pRoot == T)
        {
            m_pRoot = T->left ;
            m_pRoot->parent = m_pSentinel ;
            delete T ;
        }
        else
        {
            T->left->parent = T->parent ;
            if (T->parent->left == T)
            {
                T->parent->left = T->left ;
            }
            else
            {
                T->parent->right = T->left ;
            }
            delete p ;
        }
    }
    
    else if (T->right)
    {
        if (m_pRoot == T)
        {
            m_pRoot = T->left ;
            m_pRoot->parent = m_pSentinel ;
            delete T ;
        }
        else
        {
            TreeNode * p = T ;
            T->right->parent = T->parent ;
            if (T->parent->left == T)
            {
                T->parent->left = T->right ;
            }
            else
            {
                T->parent->right = T->right ;
            }
            delete p ;
        }
    }
}

TreeNode * RedBlackTree::InsertNoRotate(unsigned int nValue, int Color)
{
    TreeNode * pNode = m_pRoot ;
    TreeNode * tmp = NULL ;
    
    // 如果树为空的话
    if (m_pRoot == m_pSentinel)
    {
        tmp = new TreeNode(nValue) ;
        if (tmp == NULL)
        {
            exit(EXIT_FAILURE) ;
        }
        
        tmp->left = tmp->right = tmp->parent = m_pSentinel ;
        if (Color == 0)
        {
            tmp->color = red ;
        }
        else
        {
            tmp->color = black ;
        }
        
        m_pRoot = tmp ;
        return tmp ;
    }
    
    for (; pNode != m_pSentinel;)
    {
        if (nValue < pNode->key && pNode->left != m_pSentinel)
        {
            pNode = pNode->left ;
        }
        else if (nValue > pNode->key && pNode->right != m_pSentinel)
        {
            pNode = pNode->right ;
        }
        else
        {
            break ;
        }
    }
    
    if (pNode == m_pSentinel)
    {
        return 0;
    }
    
    tmp = NULL ;
    tmp = new TreeNode(nValue) ;
    if (tmp == NULL)
    {
        exit(EXIT_FAILURE) ;
    }
    tmp->left = tmp->right = m_pSentinel ;
    if (Color == red)
    {
        tmp->color = red ;
    }
    else
    {
        tmp->color = black ;
    }
    tmp->key = nValue ;
    tmp->parent = pNode ;
    // 往左边插入
    if (nValue < pNode->key && pNode->left == m_pSentinel)
    {
        pNode->left = tmp ;
    }
    // 入右边插入
    else if (nValue > pNode->key && pNode->right == m_pSentinel)
    {
        pNode->right = tmp ;
    }
    
    return tmp;
}

// 导入
int RedBlackTree::ImportFile(const char *szFileName)
{
#ifdef _DEBUG
    int nSum(0) ;
#endif
    if (fp != NULL)
    {
        fclose(fp) ;
        fp = NULL ;
    }

    fp = fopen(szFileName,"r+b") ;
    if (fp == NULL)
    {
        return 0 ;
    }

    int nValue(0),
        color(0) ,
        i(0)     ,
        nSize(0) ,
        tmp(0)   ,
        nCount(0)   ;
    TreeNode * p = NULL ;
    while(! feof(fp))
    {
        fread(&nValue, sizeof(int), 1, fp) ;
        fread(&color,  sizeof(int), 1, fp) ;
        if (! feof(fp))
        {
            nSize = 0 ;
            fread(&nSize, sizeof(int), 1, fp) ;
#ifdef _DEBUG
            if (nSize > 1)
            {
                nSum += nSize ;
            }
#endif
                p = InsertNoRotate(nValue, color) ;
            for (i = 0; i< nSize; ++i)
            {
                fread(&tmp, sizeof(int), 1, fp) ;
                p->pList->Push(tmp) ;
            }
        }
    }

    if(fp != NULL)
    {
        fclose(fp) ;
        fp = NULL ;
    }
#ifdef _DEBUG
    cout << "碰撞的哈希值一共有" << nSum << "个" << endl;
#endif
    return 1 ;
}

// 导出
int RedBlackTree::ExportFile(const char *szFileName)
{
    if (szFileName == NULL)
    {
        return 0 ;
    }
    
    fp = fopen(szFileName, "wb") ;
    if (fp == NULL)
    {
        return 0 ;
    }
    
    RecursionPreorder(m_pRoot) ;

    if (fp != NULL)
    {
        fclose(fp) ;
        fp = NULL ;
    }
#ifdef _DEBUG
    cout << "\t导出成功" << endl ;
#endif
    return 1 ;
}

void RedBlackTree::RecursionPreorder(TreeNode *T)
{
    if (T != m_pSentinel)
    {
        int i(0),
            tmp(0),
            nSize(0);

        fwrite(&(T->key),   sizeof(int), 1, fp)   ;
        fwrite(&(T->color), sizeof(int), 1, fp) ;

        nSize = T->pList->GetSize() ;
        fwrite(&nSize, sizeof(int), 1, fp) ;

        while( ! T->pList->IsEmpty() )
        {
            tmp = T->pList->Pop() ;
            fwrite(&tmp, sizeof(int), 1, fp) ;
        }
        fflush(fp) ;
        RecursionPreorder(T->left)  ;
        RecursionPreorder(T->right) ;
    }
    return ;
}

int RedBlackTree::Clear()
{
    if (m_pRoot != m_pSentinel)
    {
        Destory(m_pRoot) ;
        m_pRoot = NULL ;
    }
    if (m_pSentinel != NULL)
    {
        delete m_pSentinel ;
        m_pSentinel = NULL ;
    }
    m_pSentinel = new TreeNode ;
    if (m_pSentinel == NULL)
    {
        exit(EXIT_FAILURE) ;
    }
    m_pSentinel->color = black ;
    m_pSentinel->left   = m_pSentinel ;
    m_pSentinel->right  = m_pSentinel ;
    m_pSentinel->parent = m_pSentinel ;
    m_pRoot = m_pSentinel ;
    return 1 ;
}
