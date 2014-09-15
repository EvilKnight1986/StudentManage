// FileIndex.h: interface for the FileIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEINDEX_H__81A6A533_8B72_4210_B98E_F4B20D2E22D1__INCLUDED_)
#define AFX_FILEINDEX_H__81A6A533_8B72_4210_B98E_F4B20D2E22D1__INCLUDED_

/*******************************************************************************
*  
*  Copyright (c) all 2009 ���� All rights reserved
*  FileName : FileIndex.h
*  D a t e  : 2009.9.18
*  ��   ��  : ѧ������ϵͳ�ļ�������
*  ˵   ��  : 
*
*
*******************************************************************************/

#include "RedBlackTree.h"	// Added by ClassView
#include "dbf.h"	        // Added by ClassView
#include "adjacency.h"	    // Added by ClassView
#include "Config.h"
#include "Tools.h"

#if _MSC_VER > 1000
#pragma once
#endif                      // _MSC_VER > 1000

// �ļ�����
class FileIndex  
{
public:
	dbf lessdbf ;                       // �γ������ļ�
	dbf teadbf ;                        // ��ʦ�����ļ�
	dbf studbf ;                        // ѧ�������ļ�
    dbf stuSlectdbf ;                   // ѧ��ѡ�������ļ�
    dbf teaSelectdbf ;                  // ��ʦ�Ͽ������ļ�

    Adjacency stuSelect ;               // ѧ��ѡ��(ѧ��Ϊ�ؼ���)
    Adjacency stuLesSelect ;            // ѧ��ѡ��(�γ�idΪ�ؼ���)
    Adjacency teaSelect ;               // ��ʦ�Ͽ�(��ʦ����Ϊ�ؼ���)
    Adjacency teaLesSelect ;            // ��ʦ�Ͽ�(�γ�idΪ�ؼ���)

    RedBlackTree lessonNameIndex ;      // �γ�������
    RedBlackTree teaNameIndex ;         // ��ʦ������
	RedBlackTree stuNameIndex ;         // ѧ��������
public:
	int CreateSelectIndex(const char * szName) ;   // ����ѡ��/�ο�����
	int CreateNameIndex(  const char * szName) ;   // ������������
public:
	FileIndex() ;
	~FileIndex() ;
private:
	int SetIndexInvalida(const char *FileName);    // ��������Ϊ��Ч
	int CheckIndexSucc(const char *FileName);      // ��������ļ��Ƿ���ȷ
	int CreateAdjIndex(Adjacency &la, Adjacency &ra) ; // �����ڽӱ�
	int CreateRBTIndex(dbf & d, RedBlackTree & Tree) ; // ���������
	int CheckIndex(void);                        //  �������
};

int CheckDBF(void) ;

#endif // !defined(AFX_FILEINDEX_H__81A6A533_8B72_4210_B98E_F4B20D2E22D1__INCLUDED_)
