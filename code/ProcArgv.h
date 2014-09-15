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
* �γ���ش�����
*
*******************************************************************************/

// ����γ�������
void    LessonManageProc(FileIndex & fi)  ;

// �����û���ѯ�γ���Ϣ
void    LessonSelectProc(FileIndex & fi)  ;

// ��ӿγ�
void    LessonAddProc   (FileIndex & fi)  ;

// ��ʾ���пγ���Ϣ
void    LessonShowProc  (FileIndex & fi)  ;

// �޸Ŀγ���Ϣ
void    LessonModifiProc(FileIndex & fi)  ;

// ɾ���γ���Ϣ
void    LessonDeleteProc(FileIndex & fi)  ;


/*******************************************************************************
*
* ��ʦ��ش�����
*
*******************************************************************************/

// ��ʦ��Ϣ������
void    TeacherManageProc(FileIndex & fi) ;

// �����ѯ��ʦ��Ϣ
void    TeacherSelectProc(FileIndex & fi) ;

// ���������ʦ��Ϣ
void    TeacherAddProc   (FileIndex & fi) ;

// ��ʾ������ʦ��Ϣ
void    TeacherShowProc  (FileIndex & fi) ;

// �޸���ʦ��Ϣ
void    TeacherModifiProc(FileIndex & fi) ;

// ɾ����ʦ��Ϣ
void    TeacherDeleteProc(FileIndex & fi) ;

/*******************************************************************************
*
* ѧ����ش�����
*
*******************************************************************************/

// ѧ������������
void    StudentManageProc(FileIndex & fi) ;

// ����ѧ����ѯ
void    StudentSelectProc(FileIndex & fi) ;

// �������ѧ��
void    StudentAddProc   (FileIndex & fi) ;

// ��ʾ���е�ѧ��
void    StudentShowProc  (FileIndex & fi) ;

// �޸�ѧ����Ϣ
void    StudentModifiProc(FileIndex & fi) ;

// ɾ��ѧ����Ϣ
void    StudentDeleteProc(FileIndex & fi) ;

/*******************************************************************************
*
* ������ش�����
*
*******************************************************************************/

// ͨ��ѧ��������ѧ��
int    SelectStudentName(FileIndex & fi) ;

// ͨ���γ������ҿγ�
int    SelectLesName(FileIndex & fi) ;

/*******************************************************************************
*
* ѧ��ѡ����ش�����
*
*******************************************************************************/

// ����ѧ��ѡ��������
void    StuSelManageProc(FileIndex & fi) ;

// �����û���ѯѧ��ѡ��
void    StuSelSelectProc(FileIndex & fi) ;

// ���ѧ��ѡ��
void    StuSelAddProc   (FileIndex & fi) ;

// ��ѯ�γ̱�ѡ�����
void    StuSelShowProc  (FileIndex & fi) ;

// �޸�ѧ��ѡ��
void    StuSelModifiProc(FileIndex & fi) ;

// ɾ��ѧ��ѡ��
void    StuSelDeleteProc(FileIndex & fi) ;


/*******************************************************************************
*
* ��ʦ�ο���ش�����
*
*******************************************************************************/

// ��ʦ�οι���������
void    TeaSelManageProc(FileIndex & fi) ;

// ��ѯ��ʦ�ο�
void    TeaSelSelectProc(FileIndex & fi) ;

// ������ʦ�ο�
void    TeaSelAddProc   (FileIndex & fi) ;

// ��ʾ������ʦ�ο�
void    TeaSelShowProc  (FileIndex & fi) ;

// �޸���ʦ�ο���Ϣ
void    TeaSelModifiProc(FileIndex & fi) ;

// ɾ����ʦ�ο���Ϣ
void    TeaSelDeleteProc(FileIndex & fi) ;

#endif // !defined(AFX_PROCARGV_H__62D1C1A4_CD9B_41A1_963E_FFC4BADEE9D2__INCLUDED_)
