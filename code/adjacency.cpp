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
*  �� �� �� : Adjacency
*  �������� : Adjacency��Ĺ��캯����ֻ����ʾ����
*  �����б� : size    --  �ڽӱ�ĳ�ʼ��С
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
Adjacency::Adjacency(int size):pList(NULL),nCapacity(size)
{
    nCapacity = size ;
    Malloc(size) ;
}


/*******************************************************************************
*
*  �� �� �� : ~Adjacency
*  �������� : Adjacency�����������
*  �����б� : 
*  ˵    �� : ������������Ŀռ�
*  ���ؽ�� : ��
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
*  �� �� �� : Malloc
*  �������� : Ϊ�ڽӱ������ڴ�ռ�
*  �����б� : size    --  ����ռ��С
*  ˵    �� : 
*  ���ؽ�� : �ɹ�����1,ʧ�ܷ���0
*
*******************************************************************************/
int Adjacency::Malloc(int size)
{
    unsigned int i(0) ;
    if (size > 1)
    {
        nCapacity = size ;

        // ���ԭ���Ѿ������˿ռ�Ļ������ͷ�ԭ����
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
*  �� �� �� : Realloc
*  �������� : Ϊ�ڽӱ����������ڴ�ռ�
*  �����б� : size    --  ����ռ��С
*  ˵    �� : 
*  ���ؽ�� : �ɹ�����1,ʧ�ܷ���0
*
*******************************************************************************/
int Adjacency::Realloc(int size)
{
    unsigned int i(0) ;
    unsigned oldSize(nCapacity) ;
    nCapacity = static_cast<int>(size * 1.5) ;
    List ** tmp = new List * [nCapacity] ;

    // ��������ڴ�ʧ�ܣ�����0
    if (tmp == NULL)
    {
        return 0 ;
    }

    memset(tmp, 0, sizeof(List *) * nCapacity) ;

    // ���ԭ��û������ռ�Ļ�������
    if (pList != NULL)
    {
        // ��ԭ�������ݸ��Ƶ��µĿռ�
        for(i = 0; i < oldSize; ++i)
        {
            tmp[i] = pList[i] ;
            pList[i] = NULL ;
        }
        // Ϊ�µĿռ�����ռ�
        for (; i < nCapacity; ++i)
        {
            tmp[i] = new List ;
        }
        // ɾ��ԭ����
        delete [] pList ;

        // ��������ĸ���pList
        pList = tmp ;

        return 1 ;
    }
    return 0 ;
}

/*******************************************************************************
*
*  �� �� �� : operator []
*  �������� : ����[]�����
*  �����б� : index  --   �±�
*  ˵    �� : ������ڵĻ����������ã���С��������Χ�ڣ���������
*  ���ؽ�� : �ɹ�����List &, ʧ�ܷ���0
*
*******************************************************************************/
List & Adjacency::operator [] (unsigned int index)
{
    // �ж��Ƿ��Ѿ�����
    if (index >= 0 && index < nCapacity)
    {
        return *(pList[index]) ;
    }
    // ��������ڣ���С��������Χ�ڣ�����֮
    else if (index >= nCapacity && index < RECORDMAX)
    {
        Realloc(index) ;
    }
    return *(pList[index]) ;
}

/*******************************************************************************
*
*  �� �� �� : GetSize
*  �������� : ȡ���ڽӱ�ָ���±���ָ������Ĵ�С
*  �����б� : index  --   �±�
*  ˵    �� : 
*  ���ؽ�� : ����ĳ��ȣ��������Ϊ�գ�����0
*
*******************************************************************************/
unsigned int Adjacency::GetSize(unsigned int index)
{
    return pList[index]->GetSize() ;
}

/*******************************************************************************
*
*  �� �� �� : ImportFile
*  �������� : ���ļ������ڽӱ�
*  �����б� : szFileName  --   �����ļ���
*  ˵    �� : 
*  ���ؽ�� : �ɹ����� 1��ʧ�ܷ���0
*
*******************************************************************************/
int Adjacency::ImportFile(const char *szFileName)
{
    if (szFileName == NULL)
    {
        return 0 ;
    }

    FILE * fp = NULL ;
    unsigned int  size(0)  , // ÿ������ĳ���
                  i(0)     ,
                  j(0)     ,
                  sum(0)   , // �ڽӱ�Ĵ�С
                  tmp(0)   , 
                  offset(0);

    fp = fopen(szFileName, "rb") ;
    if (fp == NULL)
    {
        cerr << "�������" << endl ;
        return 0 ;
    }

    // �����ڽӱ�Ĵ�С
    fread(&sum, sizeof(int), 1, fp) ;

    if (sum <= 0)
    {
        cerr << "�ļ�����" << endl ;
        return 0 ;
    }

    // ���֮ǰû�������ڴ�Ļ�
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
                // ��������ֵ��ƫ����,�����ڽӱ�
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
*  �� �� �� : ExportFile
*  �������� : ���ڽӱ������ļ�
*  �����б� : szFileName  --   �����ļ���
*  ˵    �� : 
*  ���ؽ�� : �ɹ����� 1��ʧ�ܷ���0
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
        cerr << "��������" << endl ;
        return 0 ;
    }

    // ��д���ڽӱ�Ĵ�С
    fwrite(&nCapacity, sizeof(int), 1, fp) ;

    // ���ν��ڽӱ��е�����д�뵽�ļ�
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
*  �� �� �� : GetCapacity
*  �������� : ȡ���ڽӱ��С
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : �ڽӱ�Ĵ�С
*
*******************************************************************************/
unsigned int Adjacency::GetCapacity()
{
    return nCapacity ;
}

