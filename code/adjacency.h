// Adjacency.h: interface for the Adjacency class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADJACENCY_H__5BF7404E_5C52_4628_B154_09ADECEE8B28__INCLUDED_)
#define AFX_ADJACENCY_H__5BF7404E_5C52_4628_B154_09ADECEE8B28__INCLUDED_
/*******************************************************************************
*  
*  Copyright (c) all 2009 黄奇 All rights reserved
*  FileName : adjacency.cpp
*  D a t e  : 2009.9.16
*  功   能  : 动态邻接表
*  说   明  : 
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
    // 取得邻接表大小
    unsigned int GetCapacity(void) ;
    // 导出到文件
    int ExportFile(const char * szFileName) ;
    // 从文件导入
    int ImportFile(const char * szFileName) ;
    // 取得邻接表所指向链表的长度
    unsigned int GetSize(unsigned int index) ;
    // 重载[]操作符
    List & operator [](unsigned int index) ;

public:
    Adjacency(int size = 10) ;
    ~Adjacency() ;

private:
    // 申请内存空间
    int Malloc(int size) ;
    // 重新申请内存空间
    int Realloc(int size) ;

private:
    List ** pList ;
    unsigned int nCapacity ;
} ;

#endif // !defined(AFX_ADJACENCY_H__5BF7404E_5C52_4628_B154_09ADECEE8B28__INCLUDED_)
