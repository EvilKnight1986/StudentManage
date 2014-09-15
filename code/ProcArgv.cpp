// ProcArgv.cpp: implementation of the ProcArgv class.
//
//////////////////////////////////////////////////////////////////////

/*******************************************************************************
*  
*  Copyright (c) all 2009 ���� All rights reserved
*  FileName : ProcArgv.cpp
*  D a t e  : 2009.9.20
*  ��   ��  : �����û�����
*  ˵   ��  : 
*
*
*******************************************************************************/

#include "ProcArgv.h"

#if _MSC_VER >= 1400
  #pragma warning(disable:4996)
  #pragma warning(disable:6031)
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*******************************************************************************
*
*  �� �� �� : StuSelManageProc
*  �������� : ����ѧ��ѡ��������
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : ��
*
*******************************************************************************/
void StuSelManageProc(FileIndex & fi)
{
    int n(0) ;
    StuSelManageMenu() ;
    while(cin >> n && n != 0)
    {
        switch(n)
        {
        case 1:
            // ��ѯѧ��ѡ��
            StuSelSelectProc(fi) ;
            break;
        case 2:
            // ����ѧ��ѡ��
            StuSelAddProc(fi) ;
            break;
        case 3:
            // �޸�ѧ��ѡ��
            StuSelModifiProc(fi) ;
            break;
        case 4:
            // ɾ��ѧ��ѡ��
            StuSelDeleteProc(fi) ;
            break;
        case 5:
            // ��ѯ�γ̱�ѡ�����
            StuSelShowProc(fi) ;
            break ;
        default:
            cout << "\t����ȷѡ��" << endl ;
        }
        StuSelManageMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : StuSelSelectProc
*  �������� : �û���ѯѧ��ѡ�δ�������
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : ��
*
*******************************************************************************/
void StuSelSelectProc(FileIndex & fi)
{
    int n(0) ;
    int id(0);
    char szName[48] = {0} ;
    List  *p = NULL ;

    SelectStuSelMenu() ;

    while (cin >> n && n != 0)
    {
        p = NULL ;
        fflush(stdin) ;

        // ͨ��ѧ�Ų�ѯ
        if (n == 1)
        {
            cout << "\t������Ҫ��ѯѧ����ѧ��: " << flush ;
            cin >> id ;
        } // end of if

        // ͨ��������ѯ
        else if (n == 2)
        {
            if (SelectStudentName(fi) == 1)
            {
                cout << "\t����������Ҫ��ѯѧ����id: " << flush ;
                cin >> id ;
                if (id <= 0)
                {
                    cout << "\t��Ҫͽ��Ѱ��ϵͳ©��" << endl ;
                    getchar() ;
                }
            } // end of if
        } // end of else if

        id -= 1 ;
        if (id >= 0)
        {
            p = &(fi.stuSelect[id]) ;
            if (p != NULL)
            {
                int i(0) ,
                    nSize(p->GetSize()) ;
                
                if ( fi.studbf.ReadRecord(id) != 1 )
                {
                    cout << "\t�Բ����Ҳ�����ѧ��" << endl ;
                    //getchar() ;
                }
                else if (nSize == 0)
                {
                    cout << "\t�Բ��𣬴�ѧ����û��ѡ��" << endl ;
                }
                else
                {
                    DisplayStudentTitle() ;
                    cout << fi.studbf << endl << endl;
                    cout << "\t��ѧ����ѡ��" << setw(2) << nSize << "�ſγ�" << endl ;
                    cout << endl << "\tѡ���б�" << endl ;
                    DisplayStuSelTitle() ;
                    for (i = 0; i < nSize; ++i)
                    {
                        if (fi.lessdbf.ReadRecord(p->operator [](i)->GetData()) == 1)
                        {
                            cout << fi.lessdbf << flush ;
                            // �����ɼ�
                            fi.stuSlectdbf.ReadRecord(p->operator [](i)->GetOffset()) ;
                            memset(szName, 0, 5) ;
                            fi.stuSlectdbf.ReadString("grade", szName) ;
                            cout << szName << endl ;
                        }
                    }
                }
            }
        }
        else
        {
            cout << "\t��Ҫ��ͼѰ��ϵͳ��©��" << endl ;
        }
        fflush(stdin) ;
        getchar() ;
        SelectStuSelMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : StuSelAddProc
*  �������� : ���ѧ��ѡ��
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void StuSelAddProc(FileIndex & fi)
{
    int n(0) ;
    int StuId(0) ,
        LesId(0) ,
        offset(0) ,
        grade(60);
    char buf[16] = {0} ;
    char state(0) ;

    AddStuSelMenu() ;
    while(cin >> n && n != 0)
    {
        if (n == 1)
        {
            cout << "\t������Ҫѡ��ѧ����id: " << flush ;
            cin >> StuId ;
            while (StuId < 1  && fi.studbf.ReadRecord(StuId - 1) != 1)
            {
                cout << "\tid����ȷ,����������" << endl ;
                cin >> StuId ;
            }

            memset(buf, 0, 16) ;
            sprintf(buf, "%10d", StuId - 1) ;
            fi.stuSlectdbf.SetString("stuId", buf) ;

            cout << "\t������Ҫѡ�Ŀγ�ID: " << flush ;
            cin >> LesId ;
            while(LesId < 1  && fi.lessdbf.ReadRecord(LesId - 1) != 1)
            {
                cout << "\t�γ�id����ȷ,����������" << endl ;
                cin >> LesId ;
            }
            memset(buf, 0, 16) ;
            sprintf(buf, "%10d", LesId - 1) ;
            fi.stuSlectdbf.SetString("LesId", buf) ;

            memset(buf, 0, 16) ;

            cout << "\t�Ƿ�Ҫ���ø������ſγ̵ķ���: Y/N: " << flush ;  
            cin >> state ;

            if (state == 'y' || state == 'Y')
            {
                cout << "\t������ɼ�: " << flush ;
                cin >> grade ;
                while (grade < 0 || grade > 100)
                {
                    cout << "\t������Χ���ԣ�����������" << endl ;
                    cin >> grade ;
                }
            }

            // Ĭ�ϳɼ�60��
            sprintf(buf, "%4d", grade) ;
            fi.stuSlectdbf.SetString("grade", buf) ;

            // �ж�ѧ���Ƿ��Ѿ�ѡ�����ſ�
            if (fi.stuSelect[StuId-1].Find(LesId-1) == NULL)
            {
                offset = fi.stuSlectdbf.AddRecord() ;
                // ��������
                fi.stuLesSelect[LesId-1].Push(StuId-1, offset) ;
                fi.stuSelect[StuId-1].Push(LesId-1, offset) ;
                cout << "\t��ӳɹ�" << endl ;
            }
            else
            {
                cout << "\t���ʧ�ܣ��Ѿ�����" << endl ;
            }
        }
        fflush(stdin) ;
        getchar() ;
        AddStuSelMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : StuSelShowProc
*  �������� : ��ѯ�γ̱�ѡ�����
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void StuSelShowProc(FileIndex & fi)
{
    int n(0) ,
        LesId(0) ;
    List * p = NULL ;
    char szName[48] = {0} ;
    SelectLessMenu() ;
    while(cin >> n && n != 0)
    {
        if (n == 1)
        {
            cout << "\t�������ѯ�γ�ID: " << flush ;
            cin >> LesId ;
            while(fi.lessdbf.ReadRecord(LesId-1) != 1)
            {
                cout << "\t�γ̺Ų���ȷ������������: " << flush ;
                cin >> LesId ;
            }
        }
        else if (n == 2)
        {
            if (SelectLesName(fi) == 1)
            {
                cout << "\t�������ѯ�γ�ID: " << flush ;
                cin >> LesId ;
                while(fi.lessdbf.ReadRecord(LesId-1) != 1)
                {
                    cout << "\t�γ̺Ų���ȷ������������: " << flush ;
                    cin >> LesId ;
                    if (LesId == 0)
                    {
                        break ;
                    }
                }
            }
            else
            {
                cout << "\t���������ַ�����" << endl ;
            }
        }

        if (LesId > 0)
        {
            int nSize(0) ;
            cout << endl ;
            DisplayStuSelTitle() ;
            if (fi.lessdbf.ReadRecord(LesId-1) == 1)
            {
                cout << fi.lessdbf << endl ;
            }
            p = &(fi.stuLesSelect[LesId -1]) ;
            if (p != NULL && p->GetSize() > 0)
            {
                nSize = p->GetSize() ;
                cout << "\tѡ�����ſε�ѧ������ " << setw(2) << nSize << flush;
                cout << "λ" << endl ;
                // �������ѡ��ѧ����������ѧ��
                cout << "\tid\tname" << endl ;
                int i(0) ;
                for (; i < nSize; ++i)
                {
                    if(fi.studbf.ReadRecord(p->operator [](i)->offset) == 1)
                    {
                        memset(szName, 0, 48) ;
                        fi.studbf.ReadItem("id", szName) ;
                        printf("%10s", szName) ;
                        memset(szName, 0, 48) ;
                        fi.studbf.ReadItem("name", szName) ;
                        printf("%32s\n", szName) ;
                    }
                }
            }
            else
            {
                cout << "\t�Բ������ſγ�û��ѧ��ѡ��" << endl ;
            }
        }

        if (n != 1 && n != 2)
        {
            cout << "\t��������ȷѡ��" << endl ;
        }

        fflush(stdin) ;
        getchar() ;
        SelectLessMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : StuSelModifiProc
*  �������� : �޸�ѧ��ѡ��
*  �����б� : fi   --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void StuSelModifiProc(FileIndex & fi)
{
    int StuId(0) ,
        LesId(0) ,
        grade(0) ;
    int n(0) ;
    DistNode * p = NULL;
    ModifiStuSelMenu() ;
    
    while(cin >> n && n != 0)
    {
        if (n == 1)
        {
            cout << "\t������ѧ��id: " << flush ;
            cin >> StuId ;
            while(StuId <= 0 && fi.studbf.ReadRecord(StuId-1) != 1)
            {
                cout << "\t����ѧ��id����ȷ,����������: " << flush ;
                cin >> StuId ;
            }

            cout << "\t������γ�id: " << flush ;
            cin >> LesId ;

            while(LesId <= 0 && fi.lessdbf.ReadRecord(LesId-1) != 1)
            {
                cout << "\t����γ�id����ȷ,����������: " << flush ;
                cin >> LesId ;
            }
            
            // ȡ��ָ��ѧ��ѡ����Ϣ�ڵ��е�����
            p = fi.stuSelect[StuId-1].Find(LesId-1) ;
            if (p != NULL)
            {
                int offset = p->GetOffset() ;
                char buf[8] = {0} ;
                
                // ����ԭ���ķ���
                fi.stuSlectdbf.ReadRecord(offset) ;
                fi.stuSlectdbf.ReadItem("grade", buf) ;
                
                cout << "\tԭ����: " << buf << endl ;
                cout << "\t�������µķ���: " << flush ;
                cin >> grade ;
                while (grade < 0 || grade > 100)
                {
                    cout << "\t������Χ���ԣ�����������" << endl ;
                    cin >> grade ;
                }
                sprintf(buf, "%4d", grade) ;
                fi.stuSlectdbf.SetString("grade", buf) ;
                if (fi.stuSlectdbf.WriteRecord(offset) == offset)
                {
                    cout << "\t�޸ķ����ɹ�" << endl ;
                }
                else
                {
                    cout << "\t�޸ķ���ʧ��" << endl ;
                }
            }
            else
            {
                cout << "\t�Բ��𣬸���û��ѡ�����ſγ�" << endl ;
            }
        }
        getchar() ;
        fflush(stdin) ;
        ModifiStuSelMenu() ;
    }

}

/*******************************************************************************
*
*  �� �� �� : StuSelDeleteProc
*  �������� : ɾ��ѧ��ѡ��
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void StuSelDeleteProc(FileIndex & fi)
{
    int StuId(0) ,
        LesId(0) ,
        grade(0) ;
    int n(0) ;
    char state(0) ;
    DistNode * p = NULL;
    DeleteStuSelMenu() ;
    
    while(cin >> n && n != 0)
    {
        if (n == 1)
        {
            cout << "\t������ѧ��id: " << flush ;
            cin >> StuId ;
            while(StuId <= 0 && fi.studbf.ReadRecord(StuId-1) != 1)
            {
                cout << "\t����ѧ��id����ȷ,����������: " << flush ;
                cin >> StuId ;
            }

            int i(0) ,
                nSize(fi.stuSelect[StuId-1].GetSize()) ;
            if (nSize > 0)
            {
                cout << "\t������ѡ��"<< nSize << "��" << flush ;
                cout << "ѡ���б�����:(ֻ��ʾ�γ�id)" << endl ;
            }
            else
            {
                cout << "\t����û��ѡ��" << endl ;
            }
            
            cout << "\t" << flush;
            
            // ���ѧ����ѡ�Ŀγ̵�id
            for (; i < nSize ; ++i)
            {
                cout << fi.stuSelect[StuId-1][i]->data + 1 << " " ;
            }
            cout << endl ;
            
            cout << "\t������γ�id: " << flush ;
            cin >> LesId ;
            while(LesId <= 0 && fi.lessdbf.ReadRecord(LesId-1) != 1)
            {
                cout << "\t����γ�id����ȷ,����������: " << flush ;
                cin >> LesId ;
            }
            
            p = fi.stuSelect[StuId-1].Find(LesId-1) ;
            if (p != NULL)
            {
                int offset = p->GetOffset() ;
                char LessName[49] = {0};
                fi.lessdbf.ReadItem("name", LessName) ;
                SkipSpace(LessName, 48) ;
                
                cout << "\tȷ��Ҫɾ��" << LessName << " ��? Y/N :" << flush ;
                cin >> state ;

                if (state == 'n' || state == 'N')
                {
                    break;
                }

                if (fi.stuSlectdbf.DeleteRecord(offset) == 1)
                {
                    fi.stuSelect[StuId-1].Delete(LesId - 1) ;
                    fi.stuLesSelect[LesId-1].Delete(StuId - 1) ;
                    cout << "\tɾ���ɹ�" << endl ;
                }
                else
                {
                    cout << "\tɾ���ɹ�ʧ��" << endl ;
                }
            }
            else
            {
                cout << "\t�Բ��𣬸���û��ѡ�����ſγ�" << endl ;
            }
        }
        getchar() ;
        fflush(stdin) ;
        DeleteStuSelMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : TeaSelManageProc
*  �������� : ��ʦ�οι���������
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void TeaSelManageProc(FileIndex & fi)
{
    int n(0) ;
    TeaSelManageMenu() ;
    while(cin >> n && n != 0)
    {
        switch(n)
        {
        case 1:
            TeaSelSelectProc(fi) ;
            break;
        case 2:
            TeaSelAddProc(fi) ;
            break;
        case 3:
            TeaSelModifiProc(fi) ;
            break;
        case 4:
            TeaSelDeleteProc(fi) ;
            break;
        case 5:
            TeaSelShowProc(fi) ;
            break ;
        default:
            cout << "\t����ȷѡ��" << endl ;
        }
        TeaSelManageMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : TeaSelSelectProc
*  �������� : ��ѯ��ʦ�ο�
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void TeaSelSelectProc(FileIndex & fi)
{
    int n(0) ;
    int id(0);
    char szName[48] = {0} ;
    List  *p = NULL ;
    SelectTeaMenu() ;
    while (cin >> n && n != 0)
    {
        p = NULL ;
        fflush(stdin) ;
        if (n == 1)
        {
            cout << "\t������Ҫ��ѯ��ʦ�Ĺ���: " << flush ;
            cin >> id ;
        } // end of if
        else if (n == 2)
        {
            memset(szName, 0, 48) ;
            cout << "\t����Ҫ��ѯ��ʦ������: " << flush ;
            SafeInput(szName, 48) ;
            SkipSpace(szName, 48) ;
            MyList * pNameList = NULL ;
            pNameList = fi.teaNameIndex.Find(szName) ;
            if (pNameList == NULL)
            {
                cout << "\t�Ҳ��������ʦ" << endl ;
                getchar() ;
                break ;
            }
            else
            {
                unsigned int len(pNameList->GetSize()) ;
                unsigned int j(0) ;
                for (;j < len;++j)
                {
                    fi.teadbf.ReadRecord(pNameList->operator [](j)) ;
                    cout << fi.teadbf << endl;
                }
                cout << "\t����������Ҫ��ѯ��ʦ�Ĺ���: " << flush ;
                cin >> id ;
                if (id <= 0)
                {
                    cout << "\t��Ҫͽ��Ѱ��ϵͳ©��" << endl ;
                    getchar() ;
                }
            } // end of else
        } // end of else if
        
        id -= 1 ;
        if (id >= 0)
        {
            p = &(fi.teaSelect[id]) ;
            if (p != NULL)
            {
                int i(0) ,
                    nSize(p->GetSize()) ;
                
                if (fi.teadbf.ReadRecord(id) != 1)
                {
                    cout << "\t�Բ����Ҳ����˽�ʦ" << endl ;
                    //getchar() ;
                }
                else if (nSize == 0)
                {
                    cout << "\t�Բ��𣬴˽�ʦ��û��ѡ��" << endl ;
                }
                else
                {
                    DisplayTeacherTitle() ;
                    cout << fi.teadbf << endl << endl;
                    cout << "\t�ý�ʦ����" << setw(2) << nSize << "�ſγ�" << endl ;
                    cout << endl << "\t�ο��б�" << endl ;
                    DisplayTeaSelTitle() ;
                    for (i = 0; i < nSize; ++i)
                    {
                        // �����γ���Ϣ
                        if (fi.lessdbf.ReadRecord(p->operator [](i)->GetData()) == 1)
                        {
                            cout << fi.lessdbf << endl ;
                        }
                    } // end of for
                } // end of else
            } // end of p != NULL
        } // end of if id >=0 && id < 10000
        else
        {
            cout << "\t��Ҫ��ͼѰ��ϵͳ��©��" << endl ;
        }
        fflush(stdin) ;
        getchar() ;
        SelectTeaMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : TeaSelAddProc
*  �������� : ������ʦ�ο�
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void TeaSelAddProc(FileIndex & fi)
{
    int n(0) ;
    int TeaId(0) ,
        LesId(0) ,
        offset(0) ;
    char buf[16] = {0} ;
    AddTeaSelMenu() ;
    while(cin >> n && n != 0)
    {
        if (n == 1)
        {
            cout << "\t������Ҫ�ον�ʦ��id: " << flush ;
            cin >> TeaId ;
            while (TeaId < 1  && fi.teadbf.ReadRecord(TeaId - 1) != 1)
            {
                cout << "\tid����ȷ,����������" << endl ;
                cin >> TeaId ;
            }
            
            memset(buf, 0, 16) ;
            sprintf(buf, "%10d", TeaId) ;
            fi.teaSelectdbf.SetString("TeaId", buf) ;
            
            cout << "\t������Ҫ�εĿγ�ID: " << flush ;
            cin >> LesId ;
            while(LesId < 1  && fi.lessdbf.ReadRecord(LesId - 1) != 1)
            {
                cout << "\t�γ�id����ȷ,����������" << endl ;
                cin >> LesId ;
            }
            memset(buf, 0, 16) ;
            sprintf(buf, "%10d", LesId) ;
            fi.teaSelectdbf.SetString("LesId", buf) ;
            
            memset(buf, 0, 16) ;
            if (fi.teaSelect[TeaId-1].Find(LesId-1) == NULL)
            {
                offset = fi.teaSelectdbf.AddRecord() ;
                // ��������
                fi.teaLesSelect[LesId-1].Push(TeaId-1, offset) ;
                fi.teaSelect[TeaId-1].Push(LesId-1, offset) ;
                cout << "\t��ӳɹ�" << endl ;
            }
            else
            {
                cout << "\t���ʧ�ܣ��Ѿ�����" << endl ;
            }
        }
        fflush(stdin) ;
        getchar() ;
        AddTeaSelMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : TeaSelShowProc
*  �������� : ��ʾ������ʦ�ο�
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void TeaSelShowProc(FileIndex & fi)
{
    int n(0) ,
        LesId(0) ;
    List * p = NULL ;
    char szName[48] = {0} ;
    SelectLessMenu() ;
    while(cin >> n && n != 0)
    {
        if (n == 1)
        {
            cout << "\t�������ѯ�γ�ID: " << flush ;
            cin >> LesId ;
            while(fi.lessdbf.ReadRecord(LesId-1) != 1)
            {
                cout << "\t�γ̺Ų���ȷ������������: " << flush ;
                cin >> LesId ;
            }
        }
        else if (n == 2)
        {
            char buf[48] = {0} ;
            MyList * pLes = NULL ;
            cout << "\t������Ҫ��ѯ�γ���: " << flush ;
            SafeInput(buf, 48) ;
            SkipSpace(buf,48) ;
            
            if ((pLes = fi.lessonNameIndex.Find(buf) )== NULL)
            {
                cout << "\t�γ�������ȷ������������: " << flush ;
                SafeInput(buf, 48) ; 
                SkipSpace(buf, 48) ;
            }

            //ȡ��id
            int i(0) ,
                offset(0) ,
                nSize(pLes->GetSize()) ;
            memset(szName, 0, 48) ;
            if (nSize > 0)
            {
                DisplayStuSelTitle() ;
            }
            for (i = 0; i < nSize; ++i)
            {
                offset = pLes->operator [](i);
                if(fi.lessdbf.ReadRecord(offset) == 1)
                {
                    fi.lessdbf.ReadItem("name", szName) ;
                    SkipSpace(szName,48) ;
                    if (stricmp(szName, buf) == 0)
                    {
                        cout << fi.lessdbf << endl ;
                    }
                }
            }
            cout << "\t�������ѯ�γ�ID: " << flush ;
            cin >> LesId ;
            while(fi.lessdbf.ReadRecord(LesId-1) != 1)
            {
                cout << "\t�γ̺Ų���ȷ������������: " << flush ;
                cin >> LesId ;
            }
        }

        if (LesId > 0)
        {
            int nSize(0) ;
            cout << endl ;
            DisplayTeaSelTitle() ;
            if (fi.lessdbf.ReadRecord(LesId-1) == 1)
            {
                cout << fi.lessdbf << endl ;
            }
            p = &(fi.teaLesSelect[LesId -1]) ;
            if (p != NULL && p->GetSize() > 0)
            {
                nSize = p->GetSize() ;
                cout << "\t�����ſεĽ̹��� " << setw(2) << nSize << flush;
                cout << "λ" << endl ;
                // �������ѡ��ѧ����������ѧ��
                cout << "\tid\tname" << endl ;
                int i(0) ;
                for (; i < nSize; ++i)
                {
                    if(fi.teadbf.ReadRecord(p->operator [](i)->offset) == 1)
                    {
                        memset(szName, 0, 48) ;
                        fi.teadbf.ReadItem("id", szName) ;
                        printf("%10s", szName) ;
                        memset(szName, 0, 48) ;
                        fi.teadbf.ReadItem("name", szName) ;
                        printf("%32s\n", szName) ;
                    }
                }

            }
            else
            {
                cout << "\t�Բ������ſγ�û����ʦ�ο�" << endl ;
            }
        }

        if (n != 1 && n != 2)
        {
            cout << "\t��������ȷѡ��" << endl ;
        }

        fflush(stdin) ;
        getchar() ;
        SelectLessMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : TeaSelModifiProc
*  �������� : �޸���ʦ�ο���Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� :  ��û�б�ĸ�����ϢҪ�޸ģ�������������
*  ���ؽ�� : 
*
*******************************************************************************/
void TeaSelModifiProc(FileIndex & fi)
{
    cout << "\t���ܴ���" << endl ;
    getchar() ;
}

/*******************************************************************************
*
*  �� �� �� : TeaSelDeleteProc
*  �������� : ɾ����ʦ�ο���Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : ��
*  ���ؽ�� : ��
*
*******************************************************************************/
void TeaSelDeleteProc(FileIndex & fi)
{
    int TeaId(0) ,
        LesId(0) ;
    int n(0) ;
    char state(0) ;
    DistNode * p = NULL;
    DeleteTeaSelMenu() ;
    
    while(cin >> n && n != 0)
    {
        if (n == 1)
        {
            cout << "\t�������ʦ����: " << flush ;
            cin >> TeaId ;
            while(TeaId <= 0 && fi.teadbf.ReadRecord(TeaId-1) != 1)
            {
                cout << "\t�����ʦ���Ų���ȷ,����������: " << flush ;
                cin >> TeaId ;
            }
            
            int i(0) ,
                nSize(fi.teaSelect[TeaId-1].GetSize()) ;
            if (nSize > 0)
            {
                cout << "\t�ý�ʦ���ο�"<< nSize << "�ſ�" << flush ;
                cout << "ѡ���б�����:(ֻ��ʾ�γ�id)" << endl ;
            }
            else
            {
                cout << "\t�ý�ʦû���ο�" << endl ;
            }
            cout << "\t" << flush;
            for (; i < nSize ; ++i)
            {
                cout << fi.teaSelect[TeaId-1][i]->data + 1 << " " ;
            }
            cout << endl ;
            
            cout << "\t������γ�id: " << flush ;
            cin >> LesId ;
            while(LesId <= 0 && fi.lessdbf.ReadRecord(LesId-1) != 1)
            {
                cout << "\t����γ�id����ȷ,����������: " << flush ;
                cin >> LesId ;
            }
            p = fi.teaSelect[TeaId-1].Find(LesId-1) ;
            if (p != NULL)
            {
                int offset = p->GetOffset() ;
                char LessName[49] = {0};
                fi.lessdbf.ReadItem("name", LessName) ;
                SkipSpace(LessName, 48) ;
                
                cout << "\tȷ��Ҫɾ��" << LessName << " ��? Y/N :" << flush ;
                cin >> state ;
                
                if (state == 'n' || state == 'N')
                {
                    break;
                }
                
                if (fi.teaSelectdbf.DeleteRecord(offset) == 1)
                {
                    fi.teaSelect[TeaId-1].Delete(LesId - 1) ;
                    fi.teaLesSelect[LesId-1].Delete(TeaId - 1) ;
                    cout << "\tɾ���ɹ�" << endl ;
                }
                else
                {
                    cout << "\tɾ���ɹ�ʧ��" << endl ;
                }
            }
            else
            {
                cout << "\t�Բ��𣬸���û��ѡ�����ſγ�" << endl ;
            }
        }
        getchar() ;
        fflush(stdin) ;
        DeleteTeaSelMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : LessonManageProc
*  �������� : �γ̹���������
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void LessonManageProc(FileIndex & fi)
{
    int n(0) ;
    LesManageMenu() ;
    while(cin >> n && n != 0)
    {
        switch(n)
        {
        case 1:
            LessonSelectProc(fi) ;
            break;
        case 2:
            LessonAddProc(fi) ;
            break;
        case 3:
            LessonModifiProc(fi) ;
            break;
        case 4:
            LessonDeleteProc(fi) ;
            break;
        case 5:
            LessonShowProc(fi) ;
            break ;
        default:
            cout << "\t����ȷѡ��" << endl ;
        }
        LesManageMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : LessonSelectProc
*  �������� : ��ѯ�γ���Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void LessonSelectProc(FileIndex & fi) 
{
    unsigned int i(0),
        nSize(0) ;
    int n(0)       ,
        nOffset(0) ,
        nSelect(0) ;
    MyList * pList = NULL ;
    char buf[56] = {0} ;
    SelectLesMenu() ;
    while(cin >> n && n != 0)
    {
        fflush(stdin) ;
        // ���γ̺Ų�ѯ
        if (n == 1)
        {
            cout << "\t������Ҫ��ѯ�γ̵Ŀγ̺�:" << flush ;
            cin >> nSelect ;
            fflush(stdin) ;
            if (fi.lessdbf.ReadRecord(nSelect - 1) == 1)
            {
                cout << fi.lessdbf << endl ;
            }
            else
            {
                cout << "\t�Բ��𣬲鲻���ÿγ�" << endl ;
            }
        }
        // ��������ѯ
        else if (n == 2)
        {
            memset(buf, 0, 56) ;
            cout << "\t������Ҫ��ѯ�γ���:" << flush ;
            SafeInput(buf, 48) ;
            SkipSpace(buf, 48) ;
            pList = fi.lessonNameIndex.Find(buf) ;
            if (pList == NULL)
            {
                cout << "\t�Բ��𣬲鲻���ÿγ�" << endl ;
            }
            else
            {
                nSize = pList->GetSize() ;
                for (i = 0; i < nSize; ++i)
                {
                    nOffset = pList->operator[](i) ;
                    if (fi.lessdbf.ReadRecord(nOffset) == 1)
                    {
                        fi.lessdbf.ReadItem("name", buf) ;
                        
                        cout << fi.lessdbf << endl ;
                    }
                }
            }
        }
        getchar() ;
        fflush(stdin) ;
        SelectLesMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : LessonAddProc
*  �������� : ���ӿγ���Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void LessonAddProc(FileIndex & fi) 
{
    int n(0) ;
    unsigned int nIndex(0) ;
    char buf[56] = {0} ;
    char szName[56] = {0} ;
    AddLesMenu() ;
    while(cin >> n && n != 0)
    {
        fflush(stdin) ;
        if (n == 1)
        {
            memset(buf, 0, 56) ;
            cout << "\t������Ҫ��ӵĿγ���: " << flush ;
            // ������󳤶�Ϊ32
            SafeInput(szName, 48) ;
            SkipSpace(szName, 48) ;
            fi.lessdbf.SetString("name", szName) ;
            
            cout << "\t������Ҫ��ӿγ̵�ѧ����: " << flush ;
            SafeInput(buf, 2) ;
            SkipSpace(buf, 2) ;
            fi.lessdbf.SetString("mark", buf) ;
            
            cout << "\t������Ҫ��ӿγ̵�ѧʱ��: " << flush ;
            SafeInput(buf, 4) ;
            SkipSpace(buf, 4) ;
            fi.lessdbf.SetString("period", buf) ;
            
            nIndex = fi.lessdbf.AddRecord() ;
            
            // ���������������Ϣ
            if( fi.lessonNameIndex.Insert(szName, nIndex) == 1)
            {
                cout << "\t��ӳɹ�" << endl ;
            }
            else
            {
                cout << "\t���ʧ��" << endl ;
            }
            getchar() ;
            fflush(stdin) ;
        }
        AddTeaMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : LessonShowProc
*  �������� : ��ʾ�γ���Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void LessonShowProc(FileIndex & fi) 
{
    int i(0) ,
        state(0) ;
    system("cls") ;
    cout << "\t�γ���Ϣ�б�:" << endl ;
    for (i = 0; ; ++i)
    {
        state = fi.lessdbf.ReadRecord(i) ;
        if (state == -1)
        {
            break;
        }
        else if (state == 1)
        {
            cout << fi.lessdbf << endl ;
        }
    }
    getchar() ;
    fflush(stdin) ;
    return ;
}

/*******************************************************************************
*
*  �� �� �� : LessonModifiProc
*  �������� : �޸Ŀγ���Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void LessonModifiProc(FileIndex & fi)
{
    int n(0) ;
    unsigned int nIndex(0) ;
    char buf[56] = {0};
    char szName[56] = {0} ;
    char State(0) ;
    ModifiLesMenu();
    while(cin >> n && n != 0)
    {
        fflush(stdin) ;
        if (n == 1)
        {
            cout << "\t��������Ҫ�޸Ŀγ̵�ID: " << flush ;
            cin >> nIndex ;
            fflush(stdin) ;
            nIndex -= 1 ;
            while ( fi.lessdbf.ReadRecord(nIndex) != 1)
            {
                cout << "\t����Ŀγ�ID���ԣ�����������: " << flush ;
                cin >> nIndex ;
            }
            cout << "\t��ȷ��Ҫ�޸����¿γ̵���Ϣ ?" << endl;
            cout << fi.lessdbf << endl ;
            cout << "\t��ѡ��: Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'N' || State == 'n')
            {
                break ;
            }
            cout << "\t��Ҫ�޸Ŀγ�����? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'y')
            {
                memset(buf, 0, 56) ;
                fi.lessdbf.ReadItem("name", szName) ;
                SkipSpace(szName, 48) ;
                cout << "\t�������¿γ���: " << flush ;
                SafeInput(buf, 48) ;
                SkipSpace(buf, 48) ;
                // �����������ģ���ԭ���Ĳ�ͬ���͸�������
                if (stricmp(buf, szName) != 0)
                {
                    fi.lessdbf.SetString("name", buf) ;
                    fi.lessonNameIndex.Remove(szName, nIndex) ;
                    fi.lessonNameIndex.Insert(buf, nIndex) ;
                }                
            }

            cout << "\t��Ҫ�޸Ŀγ̵�ѧ����? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'N')
            {
                memset(buf, 0, 4) ;
                cout << "\t�������µ�ѧ����: " << flush ;
                SafeInput(buf, 2) ;
                fi.lessdbf.SetString("mark", buf) ;
            }

            cout << "\t��Ҫ�޸Ŀγ̵�ѧʱ��? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'N')
            {
                memset(buf, 0, 8) ;
                cout << "\t�������µ�ѧʱ��: " << flush ;
                SafeInput(buf, 4) ;
                fi.lessdbf.SetString("period", buf) ;
            }
            
            if (fi.lessdbf.SaveRecord(nIndex) == 1)
            {
                cout << "�޸ĳɹ�" << endl ;
            }
            else
            {
                cout << "�޸�ʧ��" << endl ;
            }
        }// end of if
        ModifiLesMenu();
        fflush(stdin) ;
    } //enf of while
}

/*******************************************************************************
*
*  �� �� �� : LessonDeleteProc
*  �������� : ɾ���γ���Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void LessonDeleteProc(FileIndex & fi) 
{
    int n(0) ;
    DeleteLesMenu() ;
    while(cin >> n && n != 0)
    {
        if (n == 1)
        {
            int nIndex(0) ;
            char State(0) ;
            char szName[64] = {0} ;
            
            cout << "\t������Ҫɾ���γ̵Ŀγ̺� : " << flush ;
            cin >> nIndex ;
            nIndex -= 1 ;
            fflush(stdin) ;
            State = fi.lessdbf.ReadRecord(nIndex) ;
            while (State == 0)
            {
                cout << "\t����������γ̺�: " << flush ;
                cin >> nIndex ;
                nIndex -= 1 ;
                State = fi.lessdbf.ReadRecord(nIndex) ;
            }
            if (State == -1)
            {
                return  ;
            }

            cout << fi.studbf << endl ;
            cout << "\t��ȷ��Ҫɾ���˿γ���Ϣ: Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'y' || State == 'Y')
            {
                fi.lessdbf.ReadItem("name", szName) ;
                SkipSpace(szName, 64) ;
                if (fi.lessdbf.DeleteRecord(nIndex) == 1)
                {
                    // ����ɾ��ѧ����ѡ�α�����������ļ���ļ�¼
                    unsigned int  nStuId(0)  , // ѧ��Id
                        nTeaId(0) ,
                        nLesId(nIndex)  , // �γ�Id
                        nOffset(0) , // �ļ�ƫ��
                        i(0) ,
                        nCount( fi.stuLesSelect[nLesId].GetSize()) ;
                    // ��ɾ��ѡ�����ſε�ѧ����¼
                    for (; i < nCount; ++i)
                    {
                        // �����ļ�ƫ��
                        nOffset = fi.stuLesSelect[nLesId][i]->GetOffset() ;
                        nStuId = fi.stuLesSelect[nLesId][i]->GetData() ;
                        // delete student select lesson record from dbf
                        fi.stuSlectdbf.DeleteRecord(nOffset) ;
                        fi.stuLesSelect[nLesId].Delete(nStuId) ;
                        fi.stuSelect[nStuId].Delete(nLesId) ;
                    }
                    nCount = fi.teaLesSelect[nLesId].GetSize() ;    
                    // ��ɾ��ѡ�����ſε���ʦ��¼
                    for (i = 0; i < nCount; ++i)
                    {
                        // �����ļ�ƫ��
                        nOffset = fi.teaLesSelect[nLesId][i]->GetOffset() ;
                        nTeaId = fi.teaLesSelect[nLesId][i]->GetData() ;
                        // delete student select lesson record from dbf
                        fi.teaSelectdbf.DeleteRecord(nOffset) ;
                        fi.teaLesSelect[nLesId].Delete(nTeaId) ;
                        fi.teaSelect[nTeaId].Delete(nLesId) ;
                    }
                    // ����ٽ����ſδӿγ�����������ɾ��
                    fi.lessonNameIndex.Remove(szName, nIndex) ;
                    cout << "\tɾ���ɹ�" << endl ;
                } // end of if (fi.lessdbf.DeleteRecord(nIndex) == 1)
                else
                {
                    cout << "\tɾ��ʧ��" << endl ;
                }
            }
        }// end of if (State == 'y' || State == 'Y')
        else
        {
            cout << "\t����ȷѡ��" << endl ;
        }
        getchar() ;
        DeleteLesMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : TeacherManageProc
*  �������� : ��ʦ��Ϣ������
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void TeacherManageProc(FileIndex & fi)
{
    int n(0) ;
    TeaManageMenu() ;
    while(cin >> n && n != 0)
    {
        switch(n)
        {
        case 1:
            TeacherSelectProc(fi) ;
            break;
        case 2:
            TeacherAddProc(fi) ;
            break;
        case 3:
            TeacherModifiProc(fi) ;
            break;
        case 4:
            TeacherDeleteProc(fi) ;
            break;
        case 5:
            TeacherShowProc(fi) ;
            break ;
        default:
            cout << "\t����ȷѡ��" << endl ;
        }
        TeaManageMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : TeacherSelectProc
*  �������� : �����ѯ��ʦ��Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void TeacherSelectProc(FileIndex & fi)
{
    unsigned int i(0),
        nSize(0) ;
    int n(0)       ,
        nOffset(0) ,
        nSelect(0) ;
    MyList * pList = NULL ;
    char buf[64] = {0} ;
    SelectTeaMenu() ;
    while(cin >> n && n != 0)
    {
        fflush(stdin) ;
        // ��ѧ�Ų�ѯ
        if (n == 1)
        {
            cout << "\t������Ҫ��ѯ��ʦ�Ĺ���:" << flush ;
            cin >> nSelect ;
            fflush(stdin) ;
            if (fi.teadbf.ReadRecord(nSelect - 1) == 1)
            {
                cout << fi.teadbf << endl ;
            }
            else
            {
                cout << "\t�Բ��𣬲鲻������ʦ" << endl ;
            }
        }
        // ��������ѯ
        else if (n == 2)
        {
            memset(buf, 0, 64) ;
            cout << "\t������Ҫ��ѯ��ʦ������:" << flush ;
            SafeInput(buf, 64) ;
            SkipSpace(buf, 64) ;
            pList = fi.teaNameIndex.Find(buf) ;
            if (pList == NULL)
            {
                cout << "\t�Բ��𣬲鲻������ʦ" << endl ;
            }
            else
            {
                nSize = pList->GetSize() ;
                for (i = 0; i < nSize; ++i)
                {
                    nOffset = pList->operator[](i) ;
                    if (fi.teadbf.ReadRecord(nOffset) == 1)
                    {
                        fi.teadbf.ReadItem("name", buf) ;
                        
                        cout << fi.teadbf << endl ;
                    }
                }
            }
            
        }
        getchar() ;
        fflush(stdin) ;
        SelectTeaMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : TeacherAddProc
*  �������� : ���������ʦ��Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void TeacherAddProc(FileIndex & fi)
{
    int n(0) ;
    unsigned int nIndex(0) ;
    date d ;
    char buf[64] = {0} ;
    char szName[64] = {0} ;
    AddTeaMenu() ;
    while(cin >> n && n != 0)
    {
        fflush(stdin) ;
        if (n == 1)
        {
            memset(buf, 0, 64) ;
            cout << "\t������Ҫ�����ʦ������: " << flush ;
            // ������󳤶�Ϊ32
            SafeInput(szName, 32) ;
            SkipSpace(szName, 32) ;
            fi.teadbf.SetString("name", szName) ;
            
            cout << "\t������Ҫ�����ʦ���Ա�: " << flush ;
            SafeInput(buf, 2) ;
            SkipSpace(buf, 2) ;
            fi.teadbf.SetString("sex", buf) ;
            
            cout << "\t������Ҫ�����ʦ�ĳ�������: ��ʽ:��-��-��: " << flush ;
            scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
            while(isSuccDate(d) == 0)
            {
                cout << "\t������Ҫ�����ʦ�ĳ�������: ��ʽ:��-��-��: " << flush ;
                scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
            }
            memset(buf, 0, 64) ;
            sprintf(buf, "%d%d%d", d.year, d.month, d.day) ;
            fi.teadbf.SetString("birthday", buf) ;
            
            memset(buf, 0, 64 ) ;
            cout << "\t������Ҫ�����ʦ�ĵ绰: " << flush ;
            SafeInput(buf, 18) ;
            while(isSuccPhoto(buf) == 0)
            {
                cout << "������Ҫ�����ʦ�ĵ绰: " << flush ;
                SafeInput(buf, 18) ;
            }
            fi.teadbf.SetString("telephone", buf) ;
            nIndex = fi.teadbf.AddRecord() ;
            
            // ���������������Ϣ
            if (fi.teaNameIndex.Insert(szName, nIndex) == 1)
            {
                cout << "\t��ӳɹ�" << endl ;
            }
            else
            {
                cout << "\t���ʧ��" << endl ;
            }
            getchar() ;
            fflush(stdin) ;
        }
        AddTeaMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : TeacherShowProc
*  �������� : ��ʾ������ʦ��Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void TeacherShowProc(FileIndex & fi)
{
    int i(0) ,
        state(0) ;
    system("cls") ;
    cout << "\t��ʦ��Ϣ�б�:" << endl ;
    for (i = 0; ; ++i)
    {
        state = fi.teadbf.ReadRecord(i) ;
        if (state == -1)
        {
            break;
        }
        else if (state == 1)
        {
            cout << fi.teadbf << endl ;
        }
    }
    getchar() ;
    fflush(stdin) ;
    return ;
}

/*******************************************************************************
*
*  �� �� �� : TeacherModifiProc
*  �������� : �޸���ʦ��Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void TeacherModifiProc(FileIndex & fi)
{
    int n(0) ;
    unsigned int nIndex(0) ;
    char buf[32] = {0};
    char szName[32] = {0} ;
    char State(0) ;
    ModifiTeaMenu();
    while(cin >> n && n != 0)
    {
        fflush(stdin) ;
        if (n == 1)
        {
            cout << "\t��������Ҫ�޸���ʦ��ID: " << flush ;
            cin >> nIndex ;
            fflush(stdin) ;
            nIndex -= 1 ;
            while ( fi.teadbf.ReadRecord(nIndex) != 1)
            {
                cout << "\t�������ʦID���ԣ�����������: " << flush ;
                cin >> nIndex ;
            }
            cout << "\t��ȷ��Ҫ�޸�������ʦ����Ϣ ?" << endl;
            cout << fi.teadbf << endl ;
            cout << "\t��ѡ��: Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'N' || State == 'n')
            {
                break ;
            }
            cout << "\t��Ҫ�޸�������? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'y')
            {
                memset(buf, 0, 32) ;
                fi.teadbf.ReadItem("name", szName) ;
                SkipSpace(szName, 32) ;
                cout << "\t�������û�������: " << flush ;
                SafeInput(buf, 32) ;
                SkipSpace(buf, 32) ;
                // �����������ģ���ԭ���Ĳ�ͬ���͸�������
                if (stricmp(buf, szName) != 0)
                {
                    fi.teadbf.SetString("name", buf) ;
                    fi.teaNameIndex.Remove(szName, nIndex) ;
                    fi.teaNameIndex.Insert(buf, nIndex) ;
                }                
            }
            cout << "\t��Ҫ�޸���ʦ���Ա���? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'N')
            {
                memset(buf, 0, 32) ;
                cout << "\t��������ʦ���Ժ���Ա�: " << flush ;
                SafeInput(buf, 2) ;
                fi.teadbf.SetString("sex", buf) ;
            }
            
            cout << "\t��Ҫ�޸���ʦ��������? Y/N :" << flush ;
            cin >> State ;
            if (State == 'Y' || State == 'y') 
            {
                date d ;
                fflush(stdin) ;
                cout << "\t��������ʦ�µĳ�������: ��-��-��: " << flush ;
                scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
                fflush(stdin) ;
                while(isSuccDate(d) == 0)
                {
                    cout << "��������ʦ�ĳ�������: ��ʽ:��-��-��: " << flush ;
                    scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
                    fflush(stdin) ;
                }
                memset(buf, 0, 32) ;
                sprintf(buf, "%d%d%d", d.year, d.month, d.day) ;
                fi.teadbf.SetString("birthday", buf) ;
            }
            
            cout << "\t��Ҫ�޸���ʦ�ĵ绰������? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if(State == 'Y' || State == 'y')
            {
                memset(buf, 0 , 32) ;
                cout << "\t������Ҫ�޸���ʦ�ĵ绰: " << flush ;
                SafeInput(buf, 18) ;
                while(isSuccPhoto(buf) == 0)
                {
                    cout << "\t������Ҫ�޸���ʦ�ĵ绰: " << flush ;
                    SafeInput(buf, 18) ;
                    fflush(stdin) ;
                }
                fi.teadbf.SetString("telephone", buf) ;
            }
            if (fi.teadbf.SaveRecord(nIndex) == 1)
            {
                cout << "�޸ĳɹ�" << endl ;
            }
            else
            {
                cout << "�޸�ʧ��" << endl ;
            }
        }// end of if
        ModifiTeaMenu();
        fflush(stdin) ;
    } //enf of while
}

/*******************************************************************************
*
*  �� �� �� : TeacherDeleteProc
*  �������� : ɾ����ʦ��Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void TeacherDeleteProc(FileIndex & fi)
{
    int n(0) ;
    DeleteTeaMenu() ;
    while(cin >> n && n != 0)
    {
        if (n == 1)
        {
            int nIndex(0) ;
            char State(0) ;
            char szName[64] = {0} ;
            
            cout << "\t������Ҫɾ����ʦID : " << flush ;
            cin >> nIndex ;
            nIndex -= 1 ;
            fflush(stdin) ;
            fi.teadbf.ReadRecord(nIndex) ;
            cout << fi.teadbf << endl ;
            cout << "\t��ȷ��Ҫɾ������ʦ��Ϣ: Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'y' || State == 'Y')
            {
                fi.teadbf.ReadItem("name", szName) ;
                SkipSpace(szName, 64) ;
                if (fi.teadbf.DeleteRecord(nIndex) == 1)
                {
                    // ����ɾ����ʦ��ѡ�α�����������ļ���ļ�¼
                    unsigned int  nTeaId(nIndex)  , // ��ʦId
                                  nLesId(0)  ,        // �γ�Id
                                  nOffset(0) ,        // �ļ�ƫ��
                                  i(0) ,
                                  nCount( fi.teaSelect[nTeaId].GetSize()) ;
                    // ����ɾ����ʦѡ�α������Ϣ
                    for (; i < nCount; ++i)
                    {
                        // ȡ�õ�ǰѡ�ε��ļ�ƫ��
                        nOffset = fi.teaSelect[nTeaId][i]->GetOffset() ;
                        // delete record of teacher select lesson from dbf
                        fi.teaSelectdbf.DeleteRecord(nOffset) ;
                        // ���Կγ̺�Ϊ������������¼��ɾ����ʦ
                        fi.teaLesSelect[nLesId].Delete(nTeaId) ;
                    }
                    // ��ոý�ʦ���е�ѡ�μ�¼
                    fi.teaSelect[nTeaId].Clear() ;
                    // ɾ����ʦ����������
                    fi.teaNameIndex.Remove(szName, nIndex) ;
                    cout << "\tɾ���ɹ�" << endl ;
                } // end of if (fi.teadbf.DeleteRecord(nIndex) == 1)
                else
                {
                    cout << "\tɾ��ʧ��" << endl ;
                }
            }
        }
        else
        {
            cout << "\t����ȷѡ��" << endl ;
        }
        getchar() ;
        DeleteTeaMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : StudentManageProc
*  �������� : ѧ������������
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void StudentManageProc(FileIndex & fi)
{
    int n(0) ;
    StuManageMenu() ;
    while(cin >> n && n != 0)
    {
        switch(n)
        {
        case 1:
            StudentSelectProc(fi) ;
            break;
        case 2:
            StudentAddProc(fi) ;
            break;
        case 3:
            StudentModifiProc(fi) ;
            break;
        case 4:
            StudentDeleteProc(fi) ;
            break;
        case 5:
            StudentShowProc(fi) ;
            break ;
        default:
            cout << "\t����ȷѡ��" << endl ;
            break ;
        }
        StuManageMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : StudentSelectProc
*  �������� : ����ѧ����ѯ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void StudentSelectProc(FileIndex & fi)
{
    unsigned int i(0),
                 nSize(0) ;
    int n(0)       ,
        nOffset(0) ,
        nSelect(0) ;
    MyList * pList = NULL ;
    char buf[64] = {0} ;
    SelectStuMenu() ;
    while(cin >> n && n != 0)
    {
        fflush(stdin) ;
        // ��ѧ�Ų�ѯ
        if (n == 1)
        {
            cout << "\t������Ҫ��ѯѧ����ѧ��:" << flush ;
            cin >> nSelect ;
            fflush(stdin) ;
            if (fi.studbf.ReadRecord(nSelect - 1) == 1)
            {
                cout << fi.studbf << endl ;
            }
            else
            {
                cout << "\t�Բ��𣬲鲻����ѧ��" << endl ;
            }
        }
        // ��������ѯ
        else if (n == 2)
        {
            memset(buf, 0, 64) ;
            cout << "\t������Ҫ��ѯѧ��������:" << flush ;
            SafeInput(buf, 64) ;
            SkipSpace(buf, 64) ;
            pList = fi.stuNameIndex.Find(buf) ;
            if (pList == NULL)
            {
                cout << "\t�Բ��𣬲鲻����ѧ��" << endl ;
            }
            else
            {
                nSize = pList->GetSize() ;
                for (i = 0; i < nSize; ++i)
                {
                    nOffset = pList->operator[](i) ;
                    if (fi.studbf.ReadRecord(nOffset) == 1)
                    {
                        fi.studbf.ReadItem("name", buf) ;

                        cout << fi.studbf << endl ;
                    }
                }
            }
        }
        getchar() ;
        fflush(stdin) ;
        SelectStuMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : StudentAddProc
*  �������� : �������ѧ��
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void StudentAddProc(FileIndex & fi)
{
    int n(0) ;
    unsigned int nIndex(0) ;
    date d ;
    char buf[64] = {0} ;
    char szName[64] = {0} ;
    AddStuMenu() ;
    while(cin >> n && n != 0)
    {
        fflush(stdin) ;
        if (n == 1)
        {
            memset(buf, 0, 64) ;
            cout << "\t������Ҫ���ѧ��������: " << flush ;
            // ������󳤶�Ϊ32
            SafeInput(szName, 32) ;
            SkipSpace(szName, 32) ;
            fi.studbf.SetString("name", szName) ;

            cout << "\t������Ҫ���ѧ�����Ա�: " << flush ;
            SafeInput(buf, 2) ;
            SkipSpace(buf, 2) ;
            fi.studbf.SetString("sex", buf) ;

            cout << "\t������ѧ���ĳ�������: ��ʽ:��-��-��: " << flush ;
            scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
            while(isSuccDate(d) == 0)
            {
                cout << "\t������ѧ���ĳ�������: ��ʽ:��-��-��: " << flush ;
                scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
            }

            memset(buf, 0, 64) ;
            sprintf(buf, "%d%d%d", d.year, d.month, d.day) ;
            fi.studbf.SetString("birthday", buf) ;

            memset(buf, 0, 64 ) ;
            cout << "\t������Ҫ���ѧ���ĵ绰: " << flush ;
            SafeInput(buf, 18) ;
            while(isSuccPhoto(buf) == 0)
            {
                cout << "������Ҫ���ѧ���ĵ绰: " << flush ;
                SafeInput(buf, 18) ;
            }
            fi.studbf.SetString("telephone", buf) ;
            nIndex = fi.studbf.AddRecord() ;

            // ���������������Ϣ
            if (fi.stuNameIndex.Insert(szName, nIndex) == 1)
            {
                cout << "\t��ӳɹ�" << endl ;
            }
            else
            {
                cout << "\t���ʧ��" << endl ;
            }
            getchar() ;
            fflush(stdin) ;
        }
        AddStuMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : StudentShowProc
*  �������� : ��ʾ���е�ѧ��
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void StudentShowProc(FileIndex & fi)
{
    int i(0) ,
        state(0) ;
    system("cls") ;
    cout << "\tѧ����Ϣ�б�:" << endl ;
    for (i = 0; ; ++i)
    {
        state = fi.studbf.ReadRecord(i) ;
        if (state == -1)
        {
            break;
        }
        else if (state == 1)
        {
            cout << fi.studbf << endl ;
        }
    }
    getchar() ;
    fflush(stdin) ;
    return ;
}

/*******************************************************************************
*
*  �� �� �� : StudentModifiProc
*  �������� : �޸�ѧ����Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void StudentModifiProc(FileIndex & fi) 
{
    int n(0) ;
    unsigned int nIndex(0) ;
    char buf[32] = {0};
    char szName[32] = {0} ;
    char State(0) ;
    ModifiStuMenu();
    while(cin >> n && n != 0)
    {
        fflush(stdin) ;
        if (n == 1)
        {
            cout << "\t��������Ҫ�޸�ѧ����ID: " << flush ;
            cin >> nIndex ;
            fflush(stdin) ;
            nIndex -= 1 ;
            while ( fi.studbf.ReadRecord(nIndex) != 1)
            {
                cout << "\t�����ѧ��ID���ԣ�����������: " << flush ;
                cin >> nIndex ;
                nIndex -= 1 ;
            }
            cout << "\t��ȷ��Ҫ�޸�����ѧ������Ϣ ?" << endl;
            cout << fi.studbf << endl ;
            cout << "\t��ѡ��: Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'N' || State == 'n')
            {
                break ;
            }
            cout << "\t��Ҫ�޸�������? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'y')
            {
                memset(buf, 0, 32) ;
                fi.studbf.ReadItem("name", szName) ;
                SkipSpace(szName, 32) ;
                cout << "\t�������û�������: " << flush ;
                SafeInput(buf, 32) ;
                SkipSpace(buf, 32) ;
                // �����������ģ���ԭ���Ĳ�ͬ���͸�������
                if (stricmp(buf, szName) != 0)
                {
                    fi.studbf.SetString("name", buf) ;
                    fi.stuNameIndex.Remove(szName, nIndex) ;
                    fi.stuNameIndex.Insert(buf, nIndex) ;
                }                
            }
            cout << "\t��Ҫ�޸�ѧ�����Ա���? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'N')
            {
                memset(buf, 0, 32) ;
                cout << "\t������ͬѧ���Ժ���Ա�: " << flush ;
                SafeInput(buf, 2) ;
                fi.studbf.SetString("sex", buf) ;
            }

            cout << "\t��Ҫ�޸�ѧ����������? Y/N :" << flush ;
            cin >> State ;
            if (State == 'Y' || State == 'y') 
            {
                date d ;
                fflush(stdin) ;
                cout << "\t������ѧ���µĳ�������: ��-��-��: " << flush ;
                scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
                fflush(stdin) ;
                while(isSuccDate(d) == 0)
                {
                    cout << "������ѧ���ĳ�������: ��ʽ:��-��-��: " << flush ;
                    scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
                    fflush(stdin) ;
                }
                memset(buf, 0, 32) ;
                sprintf(buf, "%d%d%d", d.year, d.month, d.day) ;
                fi.studbf.SetString("birthday", buf) ;
            }

            cout << "\t��Ҫ�޸�ѧ���ĵ绰������? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if(State == 'Y' || State == 'y')
            {
                memset(buf, 0 , 32) ;
                cout << "\t������Ҫ�޸�ѧ���ĵ绰: " << flush ;
                SafeInput(buf, 18) ;
                while(isSuccPhoto(buf) == 0)
                {
                    cout << "\t������Ҫ�޸�ѧ���ĵ绰: " << flush ;
                    SafeInput(buf, 18) ;
                    fflush(stdin) ;
                }
                fi.studbf.SetString("telephone", buf) ;
            }
            if( fi.studbf.SaveRecord(nIndex) == 1)
            {
                cout << "�޸ĳɹ�" << endl ;
            }
            else
            {
                cout << "�޸�ʧ��" << endl ;
            }
        }// end of if
        ModifiStuMenu();
        fflush(stdin) ;
    } //enf of while
}

/*******************************************************************************
*
*  �� �� �� : StudentDeleteProc
*  �������� : ɾ��ѧ����Ϣ
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
void StudentDeleteProc(FileIndex & fi)
{
    int n(0) ;
    DeleteStuMenu() ;
    while(cin >> n && n != 0)
    {
        if (n == 1)
        {
            int nIndex(0) ;
            char State(0) ;
            char szName[64] = {0} ;

            cout << "\t������Ҫɾ��ѧ��ID : " << flush ;
            cin >> nIndex ;
            nIndex -= 1 ;
            fflush(stdin) ;
            fi.studbf.ReadRecord(nIndex) ;
            cout << fi.studbf << endl ;
            cout << "\t��ȷ��Ҫɾ����ѧ����Ϣ: Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'y' || State == 'Y')
            {
                fi.studbf.ReadItem("name", szName) ;
                SkipSpace(szName, 64) ;
				// ����Ӽ�¼����ɾ���ɹ��Ļ�
                if (fi.studbf.DeleteRecord(nIndex) == 1)
                {
                    cout << "\tɾ���ɹ�" << endl ;
                    // ɾ��ѧ������������
                    fi.stuNameIndex.Remove(szName, nIndex) ;
                    // ����ɾ��ѧ����ѡ�α�����������ļ���ļ�¼
                    unsigned int  nStuId(nIndex)  , // ѧ��Id
                         nLesId(0)  , // �γ�Id
                         nOffset(0) , // �ļ�ƫ��
                         i(0) ,
                         nCount( fi.stuSelect[nStuId].GetSize()) ;
                    for (; i < nCount; ++i)
                    {
                        // �����ļ�ƫ��
                        nOffset = fi.stuSelect[nStuId][i]->GetOffset() ;
                        nLesId = fi.stuSelect[nStuId][i]->GetData()    ;
                        // ɾ��ѧ��ѡ�������ļ���ѡ�μ�¼
                        fi.stuSlectdbf.DeleteRecord(nOffset) ;
                        // ���Կγ�Ϊ��������������ɾ��ѧ����ѡ��
                        fi.stuLesSelect[nLesId].Delete(nStuId) ;
                    }
                    // ��ѧ��ѡ���б����
                    fi.stuSelect[nStuId].Clear() ;
                }
                else
                {
                    cout << "\tɾ��ʧ��" << endl ;
                }
            }
        }
        else
        {
            cout << "\t����ȷѡ��" << endl ;
        }
        getchar() ;
        DeleteStuMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  �� �� �� : SelectStudentName
*  �������� : ��ѧ����������
*  �����б� : fi    --   �ļ�����
*  ˵    �� : 
*  ���ؽ�� : ������ҳɹ������� 1,���򷵻� 0
*
*******************************************************************************/
int SelectStudentName(FileIndex & fi)
{
    int nSize(0),
        i(0),
        nOffset(0) ;
    char buf[64] = {0} ;
    MyList *pList ;
    cout << "\t������Ҫ��ѯѧ��������:" << flush ;
    SafeInput(buf, 64) ;
    SkipSpace(buf, 64) ;
    pList = fi.stuNameIndex.Find(buf) ;
    if (pList == NULL)
    {
        cout << "\t�Բ��𣬲鲻����ѧ��" << endl ;
        return 0 ;
    }
    else
    {
        nSize = pList->GetSize() ;
        for (i = 0; i < nSize; ++i)
        {
            nOffset = pList->operator[](i) ;
            if (fi.studbf.ReadRecord(nOffset) == 1)
            {
                fi.studbf.ReadItem("name", buf) ;
                
                cout << fi.studbf << endl ;
            }
        }
    }
    return 1 ;
}

/*******************************************************************************
*
*  �� �� �� : SelectLesName
*  �������� : ͨ���γ������ҿγ�
*  �����б� : fi -- �ļ�������

*  ˵    �� : �����������ң����� 0����
*  ���ؽ�� : ����ɹ����� 1,���򷵻� 0
*
*******************************************************************************/
int SelectLesName(FileIndex & fi)
{
    char szName[48] = {0} ;
    char buf[48] = {0} ;
    MyList * pLes = NULL ;
    cout << "\t������Ҫ��ѯ�γ���: " << flush ;
    SafeInput(buf, 48) ;
    SkipSpace(buf,48) ;
    
    while ((pLes = fi.lessonNameIndex.Find(buf) )== NULL)
    {
        cout << "\t�γ�������ȷ������������: " << flush ;
        SafeInput(buf, 48) ; 
        SkipSpace(buf, 48) ;
        if (strcmp(buf,"0") == 0)
        {
            return 0 ;
        }
    }

    if (pLes == NULL)
    {
        return 0 ;
    }
    
    //ȡ��id
    int i(0) ,
        offset(0) ,
        nSize(pLes->GetSize()) ;
    memset(szName, 0, 48) ;
    if (nSize > 0)
    {
        DisplayStuSelTitle() ;
    }
    for (i = 0; i < nSize; ++i)
    {
        offset = pLes->operator [](i);
        if(fi.lessdbf.ReadRecord(offset) == 1)
        {
            fi.lessdbf.ReadItem("name", szName) ;
            SkipSpace(szName,48) ;
            if (stricmp(szName, buf) == 0)
            {
                cout << fi.lessdbf << endl ;
            }
        }
    }
    return  1;
}
