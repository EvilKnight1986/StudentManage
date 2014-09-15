// Adjacency.h: interface for the Adjacency class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADJACENCY_H__5BF7404E_5C52_4628_B154_09ADECEE8B28__INCLUDED_)
#define AFX_ADJACENCY_H__5BF7404E_5C52_4628_B154_09ADECEE8B28__INCLUDED_
/*******************************************************************************
*  
*  Copyright (c) all 2009 ���� All rights reserved
*  FileName : adjacency.cpp
*  D a t e  : 2009.9.16
*  ��   ��  : ��̬�ڽӱ�
*  ˵   ��  : 
*
*******************************************************************************/

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "List.h"
#include "Config.h"
#include <string.h>

class Adjacency  
{
public:
    // ȡ���ڽӱ��С
    unsigned int GetCapacity(void) ;
    // �������ļ�
    int ExportFile(const char * szFileName) ;
    // ���ļ�����
    int ImportFile(const char * szFileName) ;
    // ȡ���ڽӱ���ָ������ĳ���
    unsigned int GetSize(unsigned int index) ;
    // ����[]������
    List & operator [](unsigned int index) ;

public:
    Adjacency(int size = 10) ;
    ~Adjacency() ;

private:
    // �����ڴ�ռ�
    int Malloc(int size) ;
    // ���������ڴ�ռ�
    int Realloc(int size) ;

private:
    List ** pList ;
    unsigned int nCapacity ;
} ;

#endif // !defined(AFX_ADJACENCY_H__5BF7404E_5C52_4628_B154_09ADECEE8B28__INCLUDED_)
