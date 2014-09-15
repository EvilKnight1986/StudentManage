// Menu.cpp: implementation of the Menu class.
//
//////////////////////////////////////////////////////////////////////

#include "Menu.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*******************************************************************************
*
*  Copyright (c) all 2009 ���� All rights reserved
*  FileName : Menu.c
*  D a t e  : 2009.9.8
*  ��   ��  : ����˵�����ʾ
*  ˵   ��  :
*
*
*******************************************************************************/
void MainMenu(void)
{
    // ����ϵͳ��������
	system("cls");
	printf("\r\n");
	printf("\r\n");
	printf("\t*************************************************************\n");
	printf("                          ѧ����Ϣ����ϵͳ\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\t\t1.ѧ����Ϣ����\n");
	printf("\r\t\t2.��ʦ��Ϣ����\n");
	printf("\r\t\t3.�γ���Ϣ����\n");
	printf("\r\t\t4.ѧ��ѡ�ι���\n");
    printf("\r\t\t5.��ʦ�οι���\n");
	printf("\r\t\t0.�˳�\n");
	printf("\r\n");
	printf("\r\n");
    printf("              Copyright (c) all 2009 ���� All rights reserved\r\n");
    printf("                                                �� �� : �� ��\r\n");
    printf("                                                �� �� : Preview\r\n");
    printf("\r\t***********************************************************\n");
    
	printf("\t��ѡ��");
    return ;
}

void StuManageMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ѧ����Ϣ����\n");
    printf("\n");
    printf("\t\t1.��ѯѧ����Ϣ\n");
    printf("\t\t2.����ѧ����Ϣ\n");
    printf("\t\t3.�޸�ѧ����Ϣ\n");
    printf("\t\t4.ɾ��ѧ����Ϣ\n");
    printf("\t\t5.��ʾ����ѧ��\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

void SelectStuMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ѧ����Ϣ��ѯ\n");
    printf("\n");
    printf("\t\t1.��ѧ�Ų�ѯ\n");
    printf("\t\t2.��������ѯ\n");
    printf("\t\tTips: ����Դ�Сд����\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

void AddStuMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ���ѧ����Ϣ\n");
    printf("\n");
    printf("\t\t1.��ʼ���\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

void ModifiStuMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ѧ����Ϣ�޸�\n");
    printf("\n");
    printf("\t\t1.ȷ���޸�\n");
    printf("\t\tTips: ֻ��ͨ��ѧ���޸�ָ��idѧ������\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

void DeleteStuMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ɾ��ѧ����Ϣ\n");
    printf("\n");
    printf("\t\t1.ȷ��ɾ��\n");
    printf("\t\tTips: ֻ��ͨ��ѧ��ɾ��ָ��idѧ����Ϣ\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

// ��ʦ��ʼ

void TeaManageMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ��ʦ��Ϣ����\n");
    printf("\n");
    printf("\t\t1.��ѯ��ʦ��Ϣ\n");
    printf("\t\t2.������ʦ��Ϣ\n");
    printf("\t\t3.�޸���ʦ��Ϣ\n");
    printf("\t\t4.ɾ����ʦ��Ϣ\n");
    printf("\t\t5.��ʾ������ʦ\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

void SelectTeaMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ��ʦ��Ϣ��ѯ\n");
    printf("\n");
    printf("\t\t1.�����Ų�ѯ\n");
    printf("\t\t2.��������ѯ\n");
    printf("\t\tTips: ����Դ�Сд����\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

void AddTeaMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            �����ʦ��Ϣ\n");
    printf("\n");
    printf("\t\t1.��ʼ���\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}


void ModifiTeaMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ��ʦ��Ϣ�޸�\n");
    printf("\n");
    printf("\t\t1.ȷ���޸�\n");
    printf("\t\tTips: ֻ��ͨ��ѧ���޸�ָ��id��ʦ����\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

void DeleteTeaMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ɾ����ʦ��Ϣ\n");
    printf("\n");
    printf("\t\t1.ȷ��ɾ��\n");
    printf("\t\tTips: ֻ��ͨ��ѧ��ɾ��ָ��idѧ����Ϣ\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}
// ��ʦ����

void LesManageMenu(void)
{
    system("cls") ;
    printf("\n") ;
    printf("\n") ;
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            �γ���Ϣ����\n");
    printf("\n") ;
    printf("\t\t1.��ѯ�γ���Ϣ\n");
    printf("\t\t2.���ӿγ���Ϣ\n");
    printf("\t\t3.�޸Ŀγ���Ϣ\n");
    printf("\t\t4.ɾ���γ���Ϣ\n");
    printf("\t\t5.��ʾ���пγ�\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

void SelectLesMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ��ѯ�γ���Ϣ\n");
    printf("\n");
    printf("\t\t1.���γ̺Ų�ѯ\n");
    printf("\t\t2.���γ�����ѯ\n");
    printf("\t\tTips: ����Դ�Сд����\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

void AddLesMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ��ӿγ���Ϣ\n");
    printf("\n");
    printf("\t\t1.��ʼ���\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}


void ModifiLesMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            �޸Ŀγ���Ϣ\n");
    printf("\n");
    printf("\t\t1.ȷ���޸�\n");
    printf("\t\tTips: ֻ��ͨ���γ̺��޸�ָ��id�γ�����\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

void DeleteLesMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ɾ���γ���Ϣ\n");
    printf("\n");
    printf("\t\t1.ȷ��ɾ��\n");
    printf("\t\tTips: ֻ��ͨ���γ̺�ɾ��ָ��id�γ���Ϣ\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

// ѧ��ѡ�����˵�
void StuSelManageMenu(void)
{
    system("cls") ;
    printf("\n") ;
    printf("\n") ;
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ѧ��ѡ�ι���\n");
    printf("\n") ;
    printf("\t\t1.��ѯѧ��ѡ��\n");
    printf("\t\t2.����ѧ��ѡ��\n");
    printf("\t\t3.�޸�ѧ���ɼ�\n");
    printf("\t\t4.ɾ��ѧ��ѡ��\n");
    printf("\t\t5.��ѯѡ��ѧ��\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

// ��ʦ�ο����˵�
void TeaSelManageMenu(void)
{
    system("cls") ;
    printf("\n") ;
    printf("\n") ;
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ��ʦ�οι���\n");
    printf("\n") ;
    printf("\t\t1.��ѯ��ʦ�ο�\n");
    printf("\t\t2.������ʦ�ο�\n");
    printf("\t\t3.�޸���ʦ�ο�\n");
    printf("\t\t4.ɾ����ʦ�ο�\n");
    printf("\t\t5.��ѯ�ο���ʦ\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

// ��ѯѧ��ѡ�β˵�
void SelectStuSelMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ��ѯѧ��ѡ��\n");
    printf("\n");
    printf("\t\t1.��ѧ�Ų�ѯ\n");
    printf("\t\t2.��������ѯ\n");
    printf("\t\tTips: ����Դ�Сд����\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

// ���ѧ��ѡ�β˵�
void AddStuSelMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ���ѧ��ѡ��\n");
    printf("\n");
    printf("\t\t1.��ʼ���\n");
    printf("\t\tTips: ֻ��ͨ��ѧ��id�Ϳγ�id���\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

// �޸�ѧ��ѡ�β˵�
void ModifiStuSelMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            �޸�ѧ���ɼ�\n");
    printf("\n");
    printf("\t\t1.ȷ���޸�\n");
    printf("\t\tTips: ֻ��ͨ��ѧ���޸�ָ���γ�id����\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

// ɾ��ѧ��ѡ�β˵�
void DeleteStuSelMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ɾ��ѧ��ѡ��\n");
    printf("\n");
    printf("\t\t1.ȷ��ɾ��\n");
    printf("\t\tTips: ֻ��ͨ��ѧ�źͿγ̺�ɾ����ѡ�γ�\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

void SelectLessMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ��ѯ�γ���Ϣ\n");
    printf("\n");
    printf("\t\t1.���γ̺Ų�ѯ\n");
    printf("\t\t2.���γ�����ѯ\n");
    printf("\t\tTips: ����Դ�Сд����\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

// ��ѯ��ʦ�οβ˵�
void SelectTeaSelMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ��ѯ��ʦ�ο�\n");
    printf("\n");
    printf("\t\t1.�����Ų�ѯ\n");
    printf("\t\t2.��������ѯ\n");
    printf("\t\tTips: ����Դ�Сд����\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

// �����ʦ�οβ˵�
void AddTeaSelMenu(void)
{
    system("cls");
    printf("\r\n");
    printf("\r\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            �����ʦ�ο�\n");
    printf("\n");
    printf("\t\t1.��ʼ���\n");
    printf("\t\tTips: ֻ��ͨ����ʦid�Ϳγ�id���\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

// �޸���ʦ�οβ˵�
void ModifiTeaSelMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            �޸���ʦ�ο�\n");
    printf("\n");
    printf("\t\t1.ȷ���޸�\n");
    printf("\t\tTips: ֻ��ͨ�������޸�ָ��id��ʦ����\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

// ɾ����ʦ�οβ˵�
void DeleteTeaSelMenu(void)
{
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("                          ѧ����Ϣ����ϵͳ\n");
    printf("                            ɾ����ʦ�ο�\n");
    printf("\n");
    printf("\t\t1.ȷ��ɾ��\n");
    printf("\t\tTips: ֻ��ͨ�����źͿγ̺�ɾ����ѡ�γ�\n");
    printf("\n");
    printf("\n");
    printf("\t\t0.�����ϼ��˵�\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t**************************************************************\n");
    printf("\t��ѡ��");
    return ;
}

void DisplayStudentTitle(void)
{
    printf("\t%5s%32s%4s", " ѧ��","     ����       ","   �Ա�") ;
    printf("%11s%12s\n","   ����", "�绰") ;
    return ;
}

void DisplayLessonTitle(void)
{

}
void DisplayTeacherTitle(void)
{
    printf("\t%5s%32s%4s", " ����","     ����       ","   �Ա�") ;
    printf("%11s%12s\n","   ���� ", "�绰 ") ;
    return ;
}

void DisplayStuSelTitle(void)
{
    printf("\t%5s%46s", "id", "           �γ���      ") ;
    printf("%2s%5s%5s\n", "ѧ��", "ѧʱ", "�ɼ�") ;
}
void DisplayTeaSelTitle(void)
{
    printf("\t%5s%46s", "id", "           �γ���      ") ;
    printf("%2s%5s\n", "ѧ��", "ѧʱ") ;
}
