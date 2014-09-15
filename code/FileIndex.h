// FileIndex.h: interface for the FileIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEINDEX_H__81A6A533_8B72_4210_B98E_F4B20D2E22D1__INCLUDED_)
#define AFX_FILEINDEX_H__81A6A533_8B72_4210_B98E_F4B20D2E22D1__INCLUDED_

/*******************************************************************************
*  
*  Copyright (c) all 2009 黄奇 All rights reserved
*  FileName : FileIndex.h
*  D a t e  : 2009.9.18
*  功   能  : 学生管理系统文件索引类
*  说   明  : 
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

// 文件索引
class FileIndex  
{
public:
	dbf lessdbf ;                       // 课程数据文件
	dbf teadbf ;                        // 教师数据文件
	dbf studbf ;                        // 学生数据文件
    dbf stuSlectdbf ;                   // 学生选课数据文件
    dbf teaSelectdbf ;                  // 老师认课数据文件

    Adjacency stuSelect ;               // 学生选课(学号为关键字)
    Adjacency stuLesSelect ;            // 学生选课(课程id为关键字)
    Adjacency teaSelect ;               // 老师认课(老师工号为关键字)
    Adjacency teaLesSelect ;            // 老师认课(课程id为关键字)

    RedBlackTree lessonNameIndex ;      // 课程名索引
    RedBlackTree teaNameIndex ;         // 教师名索引
	RedBlackTree stuNameIndex ;         // 学生名索引
public:
	int CreateSelectIndex(const char * szName) ;   // 创建选课/任课索引
	int CreateNameIndex(  const char * szName) ;   // 创建姓名索引
public:
	FileIndex() ;
	~FileIndex() ;
private:
	int SetIndexInvalida(const char *FileName);    // 将索引置为无效
	int CheckIndexSucc(const char *FileName);      // 检测索引文件是否正确
	int CreateAdjIndex(Adjacency &la, Adjacency &ra) ; // 创建邻接表
	int CreateRBTIndex(dbf & d, RedBlackTree & Tree) ; // 创建红黑树
	int CheckIndex(void);                        //  检测索引
};

int CheckDBF(void) ;

#endif // !defined(AFX_FILEINDEX_H__81A6A533_8B72_4210_B98E_F4B20D2E22D1__INCLUDED_)
