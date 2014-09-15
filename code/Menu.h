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

// �������˵�
void MainMenu(void) ;

// ѧ��ѡ�����˵�
void StuSelManageMenu(void) ;

// ��ʦ�ο����˵�
void TeaSelManageMenu(void) ;

// ѧ������˵�
void StuManageMenu(void) ;

// ��ʦ����˵�
void TeaManageMenu(void) ;

// �γ̹���˵�
void LesManageMenu(void) ;

// ��ѯѧ���˵�
void SelectStuMenu(void) ;

// ���ѧ���˵�
void AddStuMenu(void) ;

// �޸�ѧ���˵�
void ModifiStuMenu(void) ;

// ɾ��ѧ���˵�
void DeleteStuMenu(void) ;

// ��ѯ��ʦ�˵�
void SelectTeaMenu(void) ;

// �����ʦ�˵�
void AddTeaMenu(void) ;

// �޸���ʦ�˵�
void ModifiTeaMenu(void) ;

// ɾ����ʦ�˵�
void DeleteTeaMenu(void) ;

// ��ѯ�γ̲˵�
void SelectLesMenu(void) ;

// ��ӿγ̲˵�
void AddLesMenu(void) ;

// �޸Ŀγ̲˵�
void ModifiLesMenu(void) ;

// ɾ���γ̲˵�
void DeleteLesMenu(void) ;

// ��ѯѧ��ѡ�β˵�
void SelectStuSelMenu(void) ;

// ���ѧ��ѡ�β˵�
void AddStuSelMenu(void) ;

// �޸�ѧ��ѡ�β˵�
void ModifiStuSelMenu(void) ;

// ɾ��ѧ��ѡ�β˵�
void DeleteStuSelMenu(void) ;

// ��ѯ�γ̵�ѡ�����
void SelectLessMenu(void) ;

// ��ѯ��ʦ�οβ˵�
void SelectTeaSelMenu(void) ;

// �����ʦ�οβ˵�
void AddTeaSelMenu(void) ;

// �޸���ʦ�οβ˵�
void ModifiTeaSelMenu(void) ;

// ɾ����ʦ�οβ˵�
void DeleteTeaSelMenu(void) ;


#endif // !defined(AFX_MENU_H__3278B521_1806_411E_AE96_797F0E2530F8__INCLUDED_)
