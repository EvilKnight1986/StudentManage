/*******************************************************************************
*  
*  Copyright (c) all 2009 ���� All rights reserved
*  FileName : Tools.h
*  D a t e  : 2009.9.20
*  ��   ��  : һЩʵ�õĺ���
*  ˵   ��  : 
*
*
*******************************************************************************/

#if !defined(AFX_TOOLS_H__EC816A18_2F06_4553_A7B7_9A2F1711348F__INCLUDED_)
#define AFX_TOOLS_H__EC816A18_2F06_4553_A7B7_9A2F1711348F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <io.h>
#include "FileIndex.h"

typedef struct __tagDate
{
    int year ;
    int month ;
    int day ;
}date ;

// �ж�ƽ������
int isLeap(int m) ;

// �ж��Ƿ���һ����ȷ������
int isSuccDate(date &pd) ;

// �ж�����ַ����Ƿ�ȫ������
int isSuccPhoto(const char *szBuf) ;

// ��ȫ���룬�����
int SafeInput(char *szBuffer, int nSize) ;

// �Ƿ���ʮ������
int IsDecNum(char szSrc[]) ;

// ���˿հ׷�
int SkipSpace(char *szBuf, int nSize) ;

void init_crc32_table() ;
unsigned long crc32(const char* str) ;

// ����crcֵ
unsigned int cal_crc(const char *str) ;

// RSHash ����
unsigned int RSHash(const char *str) ;

// using this hash function
// JS Hash Function 
unsigned int JSHash(const char *str) ;

// P. J. Weinberger Hash Function
unsigned int PJWHash(const char *str) ;

// ELF Hash Function
unsigned int ELFHash(const char *str) ;

// BKDR Hash Function
unsigned int BKDRHash(const char *str) ;

// SDBM Hash Function
unsigned int SDBMHash(const char *str) ;

// DJB Hash Function
unsigned int DJBHash(const char *str) ;

// AP Hash Function
unsigned int APHash(const char *str) ;


#endif // !defined(AFX_TOOLS_H__EC816A18_2F06_4553_A7B7_9A2F1711348F__INCLUDED_)
