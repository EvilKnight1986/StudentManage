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

// 0x43 = 'C' ; �ַ���
// 0x4e = 'N' ; ��ֵ��
// 0x4c = 'L' ; �߼���
enum DBFFieldType 
{
    Character = 0x43,
    Number = 0x4E,
    Logical = 0x4c
};

const int FieldNameMaxLen(11) ;

// HeadEnd : �ļ�ͷ�Ľ�����־
// InforEnd: ��¼�Ľ�����־
enum DBFEndSymbol
{
    HeadEnd = 0x0D,
    InforEnd = 0x1A
};

//DBF�ļ�ͷ�ṹ
typedef struct tagDBFHead  
{
    unsigned char vers;                  // 0 ��ʾ��ǰ�İ汾��Ϣ
    unsigned char year;                  // 1 ��ʾ����ĸ������ڣ���1900������
    unsigned char month;                 // 2 ��
    unsigned char day;                   // 3 ��
    unsigned int  numberOfRecords;       // 4-7 ��¼��
    unsigned short headerLength;         // 8-9 �ļ�ͷ�е��ֽ���
    unsigned short recordLength;         // 10-11 ÿ�����ݼ�¼�ĳ���
    unsigned short reserv1;              // 12-13 ����
    unsigned char incompleteTransaction; // 14 ��ʾδ��ɵĲ���
    unsigned char encryptionFlag;        // 15 dBASE IV��������
    int freeRecordThread;                // 16-19 �����ֽڣ����ڶ��û�����ʱʹ��
    int reserv2;                         // 20-23 �����ֽڣ����ڶ��û�����ʱʹ��
    int reserv3;                         // 24-27 �����ֽڣ����ڶ��û�����ʱʹ��
    unsigned char mdxFlag;               // 28 DBF�ļ���MDX��ʶ
    unsigned char languageDriver;        // 29 Language driver ID
    unsigned short reserv4;              // 30-31 �����ֽ�
} DBFHead;

// ��¼����Ϣ����
typedef struct tagDBFField
{
    char field_name[11];                // �ֶ�����
    char field_type;                    // �ֶ�����,C-�ַ���,N-��ֵ��
    unsigned int offset;                // ƫ����
    unsigned char field_length;         // �ֶγ���
    unsigned char field_decimal;	    // �������������ֳ���
    char reserved1[2];                  // ����
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
