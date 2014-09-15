/******************************************************************************
* Copyright (c) 2009, 黄奇 ,All right reserved.
*
* 文 件 名: entry.cpp
*
* 功能描述: 学生管理系统程序入口
*
* 创 建 人: 黄奇,  2009年 9月20日
*
* 创建日期: 2009.9.20
*
* 版 本 号: 1.0
*
* 修改记录: 
*
* 编绎环境：Windows XP SP2、 VC 6.0 sp5
*			Windows 7、Visual Studio 2008
* 
*******************************************************************************/
#include "ProcArgv.h"
#include "FileIndex.h"
#include "test.h"

int main(void)
{
    int n(0) ;
	// 检测数据文件是否存在，不存在则创建
    CheckDBF() ;

    FileIndex fi ;

	// 为测试用，用于添加学生，老师、学生选课，老师任课测试数据
    AddData(fi) ;

    system("title 学生信息管理系统 Preview    Copyright (c) all 2009 黄奇 All rights reserved") ;

	// 程序菜单的显示
    MainMenu() ;

    while(cin >> n && n != 0)
    {
        switch(n)
        {
        case 1:
			// 学生管理
            StudentManageProc(fi) ;
            break;
        case 2:
			// 老师管理
            TeacherManageProc(fi) ;
            break ;
        case 3:
			// 课程管理
            LessonManageProc(fi) ;
            break;
        case 4:
			// 学生选课管理
            StuSelManageProc(fi) ;
            break;
        case 5:
			// 老师选课管理
            TeaSelManageProc(fi) ;
            break;
        default:
            printf("请正确选择!");
            getchar();
        }
        fflush(stdin) ;
        MainMenu() ;
    }
    return 0 ;
}
