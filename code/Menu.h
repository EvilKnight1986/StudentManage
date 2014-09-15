// Menu.h: interface for the Menu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENU_H__3278B521_1806_411E_AE96_797F0E2530F8__INCLUDED_)
#define AFX_MENU_H__3278B521_1806_411E_AE96_797F0E2530F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <stdio.h>
#include <stdlib.h>
#if _MSC_VER >= 1400
#include <iostream>
using namespace std ;
#else
#include <iostream.h>
#endif 


void DisplayStudentTitle(void) ;
void DisplayLessonTitle(void) ;
void DisplayTeacherTitle(void) ;
void DisplayStuSelTitle(void) ;
void DisplayTeaSelTitle(void) ;

// 界面主菜单
void MainMenu(void) ;

// 学生选课主菜单
void StuSelManageMenu(void) ;

// 老师任课主菜单
void TeaSelManageMenu(void) ;

// 学生管理菜单
void StuManageMenu(void) ;

// 老师管理菜单
void TeaManageMenu(void) ;

// 课程管理菜单
void LesManageMenu(void) ;

// 查询学生菜单
void SelectStuMenu(void) ;

// 添加学生菜单
void AddStuMenu(void) ;

// 修改学生菜单
void ModifiStuMenu(void) ;

// 删除学生菜单
void DeleteStuMenu(void) ;

// 查询老师菜单
void SelectTeaMenu(void) ;

// 添加老师菜单
void AddTeaMenu(void) ;

// 修改老师菜单
void ModifiTeaMenu(void) ;

// 删除老师菜单
void DeleteTeaMenu(void) ;

// 查询课程菜单
void SelectLesMenu(void) ;

// 添加课程菜单
void AddLesMenu(void) ;

// 修改课程菜单
void ModifiLesMenu(void) ;

// 删除课程菜单
void DeleteLesMenu(void) ;

// 查询学生选课菜单
void SelectStuSelMenu(void) ;

// 添加学生选课菜单
void AddStuSelMenu(void) ;

// 修改学生选课菜单
void ModifiStuSelMenu(void) ;

// 删除学生选课菜单
void DeleteStuSelMenu(void) ;

// 查询课程的选课情况
void SelectLessMenu(void) ;

// 查询老师任课菜单
void SelectTeaSelMenu(void) ;

// 添加老师任课菜单
void AddTeaSelMenu(void) ;

// 修改老师任课菜单
void ModifiTeaSelMenu(void) ;

// 删除老师任课菜单
void DeleteTeaSelMenu(void) ;


#endif // !defined(AFX_MENU_H__3278B521_1806_411E_AE96_797F0E2530F8__INCLUDED_)
