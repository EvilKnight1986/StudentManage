// dbf.h: interface for the dbf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBF_H__6F7CA3EB_476E_490C_BEBE_5C13124D5A0D__INCLUDED_)
#define AFX_DBF_H__6F7CA3EB_476E_490C_BEBE_5C13124D5A0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if _MSC_VER >= 1400
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std ;
#else
#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#endif 

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "MyList.h"

// 0x43 = 'C' ; 字符型
// 0x4e = 'N' ; 数值型
// 0x4c = 'L' ; 逻辑型
enum DBFFieldType 
{
    Character = 0x43,
    Number = 0x4E,
    Logical = 0x4c
};

const int FieldNameMaxLen(11) ;

// HeadEnd : 文件头的结束标志
// InforEnd: 记录的结束标志
enum DBFEndSymbol
{
    HeadEnd = 0x0D,
    InforEnd = 0x1A
};

//DBF文件头结构
typedef struct tagDBFHead  
{
    unsigned char vers;                  // 0 表示当前的版本信息
    unsigned char year;                  // 1 表示最近的更新日期，从1900年算起
    unsigned char month;                 // 2 月
    unsigned char day;                   // 3 日
    unsigned int  numberOfRecords;       // 4-7 记录数
    unsigned short headerLength;         // 8-9 文件头中的字节数
    unsigned short recordLength;         // 10-11 每个数据记录的长度
    unsigned short reserv1;              // 12-13 保留
    unsigned char incompleteTransaction; // 14 表示未完成的操作
    unsigned char encryptionFlag;        // 15 dBASE IV编密码标记
    int freeRecordThread;                // 16-19 保留字节，用于多用户处理时使用
    int reserv2;                         // 20-23 保留字节，用于多用户处理时使用
    int reserv3;                         // 24-27 保留字节，用于多用户处理时使用
    unsigned char mdxFlag;               // 28 DBF文件的MDX标识
    unsigned char languageDriver;        // 29 Language driver ID
    unsigned short reserv4;              // 30-31 保留字节
} DBFHead;

// 记录项信息描述
typedef struct tagDBFField
{
    char field_name[11];                // 字段名称
    char field_type;                    // 字段类型,C-字符型,N-数值型
    unsigned int offset;                // 偏移量
    unsigned char field_length;         // 字段长度
    unsigned char field_decimal;	    // 浮点数整数部分长度
    char reserved1[2];                  // 保留
    char dbaseiv_id;
    char reserved2[10];
    char production_index;
} DBFField;

class dbf  
{
public:
    friend ostream & operator << (ostream &os, const dbf &obj) ;
    int  InitFileSize(unsigned int nSize) ;
    int  AddRecord(void) ;
    int  ReadIndex(void) ;
    int  WriteIndex(void) ;
    int  GetRecordCount(void) ;
    int  GetItemCount(void) ;
    int  ReadNextRecord(void) ;
    int  ReadRecord(int nIndex) ;
    int  MoveToFirst(void) ;
    void Submit(void) ;
    void WriteEndState(void) ;
    void Clear(void) ;
    int  SetString(const char *ItemName, const char *Buf) ;
    int  SaveRecord(int nIndex) ;
    int  DeleteRecord(int nIndex) ;
    int  SetInt(const char *ItemName, int nValue) ;
    int  ReadInt(const char *ItemName, int &Result) ;
    int  ReadString(const char *ItemName, char * Buf) ;
    int  GetState(void) ;
    int  ReadItem(const char *ItemName, char *Buf) ;
    int  WriteRecord(int nPosition) ;
    int  HeadWriteToFile(void) ;
    void DisplayFieldInformat(void) ;
    void DisplayHeadInformat(void) ;
    int  GetOffset(const char *ItemName, int &nIndex) ;
    int  ReadHead(void) ;
    int  WriteHead(void) ;
    void SetHeadTime(void) ;
    int  CreateHead(void) ;
    int  AddField(const char *FieldName, const char type, int nLen) ;
    explicit dbf() ;
    explicit dbf(const char * FileName) ;
    ~dbf() ;
private:
    FILE * wfp ;
    FILE * rfp ;
    char * pFileName ;
    char * pFreeIndexName ;
    DBFHead * pHead ;
    DBFField * pField ;
    void * pBuf ;
    int nState ;
    int nFieldCount ;
public:
    int FileIncrease(unsigned int nPercent);
    MyList pFree;
private:	
    explicit dbf(const dbf &obj){}
    dbf & operator = (const dbf &obj) {}
};

#endif // !defined(AFX_DBF_H__6F7CA3EB_476E_490C_BEBE_5C13124D5A0D__INCLUDED_)
