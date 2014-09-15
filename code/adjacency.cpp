// Adjacency.cpp: implementation of the Adjacency class.
//
//////////////////////////////////////////////////////////////////////

#include "Adjacency.h"

#if _MSC_VER >= 1400
  #pragma warning(disable:4996)
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*******************************************************************************
*
*  函 数 名 : Adjacency
*  功能描述 : Adjacency类的构造函数，只能显示调用
*  参数列表 : size    --  邻接表的初始大小
*  说    明 : 
*  返回结果 : 
*
*******************************************************************************/
Adjacency::Adjacency(int size):pList(NULL),nCapacity(size)
{
    nCapacity = size ;
    Malloc(size) ;
}


/*******************************************************************************
*
*  函 数 名 : ~Adjacency
*  功能描述 : Adjacency类的析构函数
*  参数列表 : 
*  说    明 : 清理申请出来的空间
*  返回结果 : 无
*
*******************************************************************************/
Adjacency::~Adjacency()
{
    if (pList != NULL)
    {
        unsigned int i(0) ;
        for (i = 0; i < nCapacity; ++i)
        {
            if (pList[i] != NULL)
            {
                delete pList[i] ;
            }
        }
        delete [] pList;
        pList = NULL ;
    }
}

/*******************************************************************************
*
*  函 数 名 : Malloc
*  功能描述 : 为邻接表申请内存空间
*  参数列表 : size    --  申请空间大小
*  说    明 : 
*  返回结果 : 成功返回1,失败返回0
*
*******************************************************************************/
int Adjacency::Malloc(int size)
{
    unsigned int i(0) ;
    if (size > 1)
    {
        nCapacity = size ;

        // 如果原来已经申请了空间的话，先释放原来的
        if (pList != NULL)
        {
            delete [] pList ;
            pList = NULL ;
        }

        pList = new List*[nCapacity] ;
        memset(pList,0, sizeof(DistPosition) * nCapacity) ;

        for (i = 0; i < nCapacity; ++i)
        {
            pList[i] = new List ;
        }

        return 1 ;
    }
    return 0 ;
}

/*******************************************************************************
*
*  函 数 名 : Realloc
*  功能描述 : 为邻接表重新申请内存空间
*  参数列表 : size    --  申请空间大小
*  说    明 : 
*  返回结果 : 成功返回1,失败返回0
*
*******************************************************************************/
int Adjacency::Realloc(int size)
{
    unsigned int i(0) ;
    unsigned oldSize(nCapacity) ;
    nCapacity = static_cast<int>(size * 1.5) ;
    List ** tmp = new List * [nCapacity] ;

    // 如果申请内存失败，返回0
    if (tmp == NULL)
    {
        return 0 ;
    }

    memset(tmp, 0, sizeof(List *) * nCapacity) ;

    // 如果原来没有申请空间的话，跳过
    if (pList != NULL)
    {
        // 将原来的数据复制到新的空间
        for(i = 0; i < oldSize; ++i)
        {
            tmp[i] = pList[i] ;
            pList[i] = NULL ;
        }
        // 为新的空间申请空间
        for (; i < nCapacity; ++i)
        {
            tmp[i] = new List ;
        }
        // 删除原来的
        delete [] pList ;

        // 将新申请的赋给pList
        pList = tmp ;

        return 1 ;
    }
    return 0 ;
}

/*******************************************************************************
*
*  函 数 名 : operator []
*  功能描述 : 重载[]运算符
*  参数列表 : index  --   下标
*  说    明 : 如果存在的话，返回引用，大小在正常范围内，则新申请
*  返回结果 : 成功返回List &, 失败返回0
*
*******************************************************************************/
List & Adjacency::operator [] (unsigned int index)
{
    // 判断是否已经存在
    if (index >= 0 && index < nCapacity)
    {
        return *(pList[index]) ;
    }
    // 如果不存在，大小在正常范围内，申请之
    else if (index >= nCapacity && index < RECORDMAX)
    {
        Realloc(index) ;
    }
    return *(pList[index]) ;
}

/*******************************************************************************
*
*  函 数 名 : GetSize
*  功能描述 : 取得邻接表指定下标所指向链表的大小
*  参数列表 : index  --   下标
*  说    明 : 
*  返回结果 : 链表的长度，如果链表为空，返回0
*
*******************************************************************************/
unsigned int Adjacency::GetSize(unsigned int index)
{
    return pList[index]->GetSize() ;
}

/*******************************************************************************
*
*  函 数 名 : ImportFile
*  功能描述 : 从文件读入邻接表
*  参数列表 : szFileName  --   导出文件名
*  说    明 : 
*  返回结果 : 成功返回 1，失败返回0
*
*******************************************************************************/
int Adjacency::ImportFile(const char *szFileName)
{
    if (szFileName == NULL)
    {
        return 0 ;
    }

    FILE * fp = NULL ;
    unsigned int  size(0)  , // 每个链表的长度
                  i(0)     ,
                  j(0)     ,
                  sum(0)   , // 邻接表的大小
                  tmp(0)   , 
                  offset(0);

    fp = fopen(szFileName, "rb") ;
    if (fp == NULL)
    {
        cerr << "导入出错" << endl ;
        return 0 ;
    }

    // 读出邻接表的大小
    fread(&sum, sizeof(int), 1, fp) ;

    if (sum <= 0)
    {
        cerr << "文件错误" << endl ;
        return 0 ;
    }

    // 如果之前没有申请内存的话
    if (pList == NULL || sum > nCapacity)
    {
        if(Malloc(sum) == 0)
        {
            return 0 ;
        }
    }

    for (i = 0; i < sum; ++i)
    {
        fread(&size, sizeof(int), 1, fp) ;
        if (! feof(fp))
        {
            for(j = 0; j < size; ++j)
            {
                // 读出结点的值和偏移量,丢入邻接表
                fread(&tmp,    sizeof(int), 1, fp) ;
                fread(&offset, sizeof(int), 1, fp) ;

                pList[i]->Push(tmp, offset) ;
            }
        }
    }
    if (fp != NULL)
    {
        fclose(fp) ;
        fp = NULL ;
    }
    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : ExportFile
*  功能描述 : 将邻接表导出到文件
*  参数列表 : szFileName  --   导出文件名
*  说    明 : 
*  返回结果 : 成功返回 1，失败返回0
*
*******************************************************************************/
int Adjacency::ExportFile(const char *szFileName)
{
    if (szFileName == NULL)
    {
        return 0 ;
    }
    
    FILE * fp = NULL ;
    unsigned int  nSize(0) ,
                  i(0),
                  j(0),
                  tmp(0),
                  offset(0);
    
    fp = fopen(szFileName, "wb") ;
    if (fp == NULL)
    {
        cerr << "导出出错" << endl ;
        return 0 ;
    }

    // 先写入邻接表的大小
    fwrite(&nCapacity, sizeof(int), 1, fp) ;

    // 依次将邻接表中的数据写入到文件
    for (i = 0;i < nCapacity; ++i)
    {
        nSize = pList[i]->GetSize() ;
        fwrite(&nSize, sizeof(int), 1, fp) ;
        for(j = 0; j < nSize; ++j)
        {
            tmp = (pList[i])->operator[](j)->GetData() ;
            offset = (pList[i])->operator[](j)->GetOffset() ;
            fwrite(&tmp,    sizeof(int), 1, fp) ;
            fwrite(&offset, sizeof(int), 1, fp) ;
        }
    }
    if (fp != NULL)
    {
        fclose(fp) ;
        fp = NULL ;
    }
    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : GetCapacity
*  功能描述 : 取得邻接表大小
*  参数列表 : 
*  说    明 : 
*  返回结果 : 邻接表的大小
*
*******************************************************************************/
unsigned int Adjacency::GetCapacity()
{
    return nCapacity ;
}

