// ProcArgv.h: interface for the ProcArgv class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROCARGV_H__62D1C1A4_CD9B_41A1_963E_FFC4BADEE9D2__INCLUDED_)
#define AFX_PROCARGV_H__62D1C1A4_CD9B_41A1_963E_FFC4BADEE9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Menu.h"
#include "FileIndex.h"
#include "MyList.h"

/*******************************************************************************
*
* 课程相关处理函数
*
*******************************************************************************/

// 处理课程主程序
void    LessonManageProc(FileIndex & fi)  ;

// 处理用户查询课程信息
void    LessonSelectProc(FileIndex & fi)  ;

// 添加课程
void    LessonAddProc   (FileIndex & fi)  ;

// 显示所有课程信息
void    LessonShowProc  (FileIndex & fi)  ;

// 修改课程信息
void    LessonModifiProc(FileIndex & fi)  ;

// 删除课程信息
void    LessonDeleteProc(FileIndex & fi)  ;


/*******************************************************************************
*
* 老师相关处理函数
*
*******************************************************************************/

// 老师信息主函数
void    TeacherManageProc(FileIndex & fi) ;

// 处理查询教师信息
void    TeacherSelectProc(FileIndex & fi) ;

// 处理添加老师信息
void    TeacherAddProc   (FileIndex & fi) ;

// 显示所有老师信息
void    TeacherShowProc  (FileIndex & fi) ;

// 修改老师信息
void    TeacherModifiProc(FileIndex & fi) ;

// 删除老师信息
void    TeacherDeleteProc(FileIndex & fi) ;

/*******************************************************************************
*
* 学生相关处理函数
*
*******************************************************************************/

// 学生管理主函数
void    StudentManageProc(FileIndex & fi) ;

// 处理学生查询
void    StudentSelectProc(FileIndex & fi) ;

// 处理添加学生
void    StudentAddProc   (FileIndex & fi) ;

// 显示所有的学生
void    StudentShowProc  (FileIndex & fi) ;

// 修改学生信息
void    StudentModifiProc(FileIndex & fi) ;

// 删除学生信息
void    StudentDeleteProc(FileIndex & fi) ;

/*******************************************************************************
*
* 查找相关处理函数
*
*******************************************************************************/

// 通过学生名查找学生
int    SelectStudentName(FileIndex & fi) ;

// 通过课程名查找课程
int    SelectLesName(FileIndex & fi) ;

/*******************************************************************************
*
* 学生选课相关处理函数
*
*******************************************************************************/

// 处理学生选课主程序
void    StuSelManageProc(FileIndex & fi) ;

// 处理用户查询学生选课
void    StuSelSelectProc(FileIndex & fi) ;

// 添加学生选课
void    StuSelAddProc   (FileIndex & fi) ;

// 查询课程被选的情况
void    StuSelShowProc  (FileIndex & fi) ;

// 修改学生选课
void    StuSelModifiProc(FileIndex & fi) ;

// 删除学生选课
void    StuSelDeleteProc(FileIndex & fi) ;


/*******************************************************************************
*
* 老师任课相关处理函数
*
*******************************************************************************/

// 老师任课管理主函数
void    TeaSelManageProc(FileIndex & fi) ;

// 查询老师任课
void    TeaSelSelectProc(FileIndex & fi) ;

// 增加老师任课
void    TeaSelAddProc   (FileIndex & fi) ;

// 显示所有老师任课
void    TeaSelShowProc  (FileIndex & fi) ;

// 修改老师任课信息
void    TeaSelModifiProc(FileIndex & fi) ;

// 删除老师任课信息
void    TeaSelDeleteProc(FileIndex & fi) ;

#endif // !defined(AFX_PROCARGV_H__62D1C1A4_CD9B_41A1_963E_FFC4BADEE9D2__INCLUDED_)
