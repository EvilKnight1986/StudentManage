/******************************************************************************
* Copyright (c) 2009, ���� ,All right reserved.
*
* �� �� ��: entry.cpp
*
* ��������: ѧ������ϵͳ�������
*
* �� �� ��: ����,  2009�� 9��20��
*
* ��������: 2009.9.20
*
* �� �� ��: 1.0
*
* �޸ļ�¼: 
*
* ���ﻷ����Windows XP SP2�� VC 6.0 sp5
*			Windows 7��Visual Studio 2008
* 
*******************************************************************************/
#include "ProcArgv.h"
#include "FileIndex.h"
#include "test.h"

int main(void)
{
    int n(0) ;
	// ��������ļ��Ƿ���ڣ��������򴴽�
    CheckDBF() ;

    FileIndex fi ;

	// Ϊ�����ã��������ѧ������ʦ��ѧ��ѡ�Σ���ʦ�οβ�������
    AddData(fi) ;

    system("title ѧ����Ϣ����ϵͳ Preview    Copyright (c) all 2009 ���� All rights reserved") ;

	// ����˵�����ʾ
    MainMenu() ;

    while(cin >> n && n != 0)
    {
        switch(n)
        {
        case 1:
			// ѧ������
            StudentManageProc(fi) ;
            break;
        case 2:
			// ��ʦ����
            TeacherManageProc(fi) ;
            break ;
        case 3:
			// �γ̹���
            LessonManageProc(fi) ;
            break;
        case 4:
			// ѧ��ѡ�ι���
            StuSelManageProc(fi) ;
            break;
        case 5:
			// ��ʦѡ�ι���
            TeaSelManageProc(fi) ;
            break;
        default:
            printf("����ȷѡ��!");
            getchar();
        }
        fflush(stdin) ;
        MainMenu() ;
    }
    return 0 ;
}
