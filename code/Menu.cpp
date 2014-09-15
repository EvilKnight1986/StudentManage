// Menu.cpp: implementation of the Menu class.
//
//////////////////////////////////////////////////////////////////////

#include "Menu.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*******************************************************************************
*
*  Copyright (c) all 2009 黄奇 All rights reserved
*  FileName : Menu.c
*  D a t e  : 2009.9.8
*  功   能  : 程序菜单的显示
*  说   明  :
*
*
*******************************************************************************/
void MainMenu(void)
{
    // 调用系统命令清屏
	system("cls");
	printf("\r\n");
	printf("\r\n");
	printf("\t*************************************************************\n");
	printf("                          学生信息管理系统\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\t\t1.学生信息管理\n");
	printf("\r\t\t2.老师信息管理\n");
	printf("\r\t\t3.课程信息管理\n");
	printf("\r\t\t4.学生选课管理\n");
    printf("\r\t\t5.老师任课管理\n");
	printf("\r\t\t0.退出\n");
	printf("\r\n");
	printf("\r\n");
    printf("              Copyright (c) all 2009 黄奇 All rights reserved\r\n");
    printf("                                                作 者 : 黄 奇\r\n");
    printf("                                                版 本 : Preview\r\n");
    printf("\r\t***********************************************************\n");
    
	printf("\t请选择：");
    return ;
}

void StuManageMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            学生信息管理\n");
    printf("\n");
    printf("\t\t1.查询学生信息\n");
    printf("\t\t2.增加学生信息\n");
    printf("\t\t3.修改学生信息\n");
    printf("\t\t4.删除学生信息\n");
    printf("\t\t5.显示所有学生\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

void SelectStuMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            学生信息查询\n");
    printf("\n");
    printf("\t\t1.按学号查询\n");
    printf("\t\t2.按姓名查询\n");
    printf("\t\tTips: 程序对大小写敏感\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

void AddStuMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            添加学生信息\n");
    printf("\n");
    printf("\t\t1.开始添加\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

void ModifiStuMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            学生信息修改\n");
    printf("\n");
    printf("\t\t1.确认修改\n");
    printf("\t\tTips: 只能通过学号修改指定id学生数据\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

void DeleteStuMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            删除学生信息\n");
    printf("\n");
    printf("\t\t1.确认删除\n");
    printf("\t\tTips: 只能通过学号删除指定id学生信息\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

// 老师开始

void TeaManageMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            老师信息管理\n");
    printf("\n");
    printf("\t\t1.查询老师信息\n");
    printf("\t\t2.增加老师信息\n");
    printf("\t\t3.修改老师信息\n");
    printf("\t\t4.删除老师信息\n");
    printf("\t\t5.显示所有老师\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

void SelectTeaMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            老师信息查询\n");
    printf("\n");
    printf("\t\t1.按工号查询\n");
    printf("\t\t2.按姓名查询\n");
    printf("\t\tTips: 程序对大小写敏感\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

void AddTeaMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            添加老师信息\n");
    printf("\n");
    printf("\t\t1.开始添加\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}


void ModifiTeaMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            老师信息修改\n");
    printf("\n");
    printf("\t\t1.确认修改\n");
    printf("\t\tTips: 只能通过学号修改指定id老师数据\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

void DeleteTeaMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            删除老师信息\n");
    printf("\n");
    printf("\t\t1.确认删除\n");
    printf("\t\tTips: 只能通过学号删除指定id学生信息\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}
// 老师结束

void LesManageMenu(void)
{
    system("cls") ;
    printf("\n") ;
    printf("\n") ;
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            课程信息管理\n");
    printf("\n") ;
    printf("\t\t1.查询课程信息\n");
    printf("\t\t2.增加课程信息\n");
    printf("\t\t3.修改课程信息\n");
    printf("\t\t4.删除课程信息\n");
    printf("\t\t5.显示所有课程\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

void SelectLesMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            查询课程信息\n");
    printf("\n");
    printf("\t\t1.按课程号查询\n");
    printf("\t\t2.按课程名查询\n");
    printf("\t\tTips: 程序对大小写敏感\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

void AddLesMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            添加课程信息\n");
    printf("\n");
    printf("\t\t1.开始添加\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}


void ModifiLesMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            修改课程信息\n");
    printf("\n");
    printf("\t\t1.确认修改\n");
    printf("\t\tTips: 只能通过课程号修改指定id课程数据\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

void DeleteLesMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            删除课程信息\n");
    printf("\n");
    printf("\t\t1.确认删除\n");
    printf("\t\tTips: 只能通过课程号删除指定id课程信息\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

// 学生选课主菜单
void StuSelManageMenu(void)
{
    system("cls") ;
    printf("\n") ;
    printf("\n") ;
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            学生选课管理\n");
    printf("\n") ;
    printf("\t\t1.查询学生选课\n");
    printf("\t\t2.增加学生选课\n");
    printf("\t\t3.修改学生成绩\n");
    printf("\t\t4.删除学生选课\n");
    printf("\t\t5.查询选课学生\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

// 老师任课主菜单
void TeaSelManageMenu(void)
{
    system("cls") ;
    printf("\n") ;
    printf("\n") ;
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            老师任课管理\n");
    printf("\n") ;
    printf("\t\t1.查询老师任课\n");
    printf("\t\t2.增加老师任课\n");
    printf("\t\t3.修改老师任课\n");
    printf("\t\t4.删除老师任课\n");
    printf("\t\t5.查询任课老师\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

// 查询学生选课菜单
void SelectStuSelMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            查询学生选课\n");
    printf("\n");
    printf("\t\t1.按学号查询\n");
    printf("\t\t2.按姓名查询\n");
    printf("\t\tTips: 程序对大小写敏感\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

// 添加学生选课菜单
void AddStuSelMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            添加学生选课\n");
    printf("\n");
    printf("\t\t1.开始添加\n");
    printf("\t\tTips: 只能通过学生id和课程id添加\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

// 修改学生选课菜单
void ModifiStuSelMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            修改学生成绩\n");
    printf("\n");
    printf("\t\t1.确认修改\n");
    printf("\t\tTips: 只能通过学号修改指定课程id数据\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

// 删除学生选课菜单
void DeleteStuSelMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            删除学生选课\n");
    printf("\n");
    printf("\t\t1.确认删除\n");
    printf("\t\tTips: 只能通过学号和课程号删除已选课程\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

void SelectLessMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            查询课程信息\n");
    printf("\n");
    printf("\t\t1.按课程号查询\n");
    printf("\t\t2.按课程名查询\n");
    printf("\t\tTips: 程序对大小写敏感\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

// 查询老师任课菜单
void SelectTeaSelMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            查询老师任课\n");
    printf("\n");
    printf("\t\t1.按工号查询\n");
    printf("\t\t2.按姓名查询\n");
    printf("\t\tTips: 程序对大小写敏感\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

// 添加老师任课菜单
void AddTeaSelMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            添加老师任课\n");
    printf("\n");
    printf("\t\t1.开始添加\n");
    printf("\t\tTips: 只能通过教师id和课程id添加\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

// 修改老师任课菜单
void ModifiTeaSelMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            修改老师任课\n");
    printf("\n");
    printf("\t\t1.确认修改\n");
    printf("\t\tTips: 只能通过工号修改指定id老师数据\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

// 删除老师任课菜单
void DeleteTeaSelMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          学生信息管理系统\n");
    printf("                            删除老师任课\n");
    printf("\n");
    printf("\t\t1.确认删除\n");
    printf("\t\tTips: 只能通过工号和课程号删除已选课程\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.返回上级菜单\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t请选择：");
    return ;
}

void DisplayStudentTitle(void)
{
    printf("\t%5s%32s%4s", " 学号","     姓名       ","   性别") ;
    printf("%11s%12s\n","   生日", "电话") ;
    return ;
}

void DisplayLessonTitle(void)
{

}
void DisplayTeacherTitle(void)
{
    printf("\t%5s%32s%4s", " 工号","     姓名       ","   性别") ;
    printf("%11s%12s\n","   生日 ", "电话 ") ;
    return ;
}

void DisplayStuSelTitle(void)
{
    printf("\t%5s%46s", "id", "           课程名      ") ;
    printf("%2s%5s%5s\n", "学分", "学时", "成绩") ;
}
void DisplayTeaSelTitle(void)
{
    printf("\t%5s%46s", "id", "           课程名      ") ;
    printf("%2s%5s\n", "学分", "学时") ;
}
