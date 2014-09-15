#include "FileIndex.h"
#pragma warning(disable:4996)

static char surnamed[50][3] = {
"��", "��", "��", "��", "��", "��", "��", "��", "֣", "��",
"��", "��", "��", "��", "��", "��", "Ф", "��", "��", "��",
"��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
"Ԭ", "¬", "��", "Ǯ", "��", "��", "½", "��", "ϰ", "��",
"��", "��", "��", "��", "��", "л", "��", "��", "��", "��"
};

static char mind[20][3] = {
"��", "��", "��", "��", "��", "Ȫ", "��", "ΰ", "��", "ʷ",
"��", "��", "��", "ˮ", "��", "��", "��", "��", "��", "��"
};

static char name[120][3] = {
"��", "��", "��", "��", "ΰ", "��", "��", "��", "ʦ", "��",
"��", "��", "��" ,"��", "��", "��", "ǿ", "��", "��", "��",
"��", "��", "��", "��", "־", "��", "ɽ", "ˮ", "��", "��",
"��", "��", "��", "��", "��", "��", "��", "��", "��", "˹",
"��", "��", "�", "˹", "��", "��", "��", "��", "��", "��",
"��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
"ά", "��", "��", "��", "ʤ", "��", "��", "��", "¥", "��",
"��", "��", "˼", "��", "��", "��", "��", "��", "��", "��",
"·", "��", "��", "��", "��", "ʫ", "��", "��", "��", "Ƽ",
"��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
"��", "��", "��", "��", "��", "��", "��", "��", "��", "־",
"��", "��", "��" ,"ͷ", "��", "��", "��", "��", "��", "��"
};

/*******************************************************************************
*
*  �� �� �� : AddData
*  �������� : ���ѧ������ʦ��ѧ��ѡ�Σ���ʦ�οβ�������
*  �����б� : fi	--		�ļ�����
*  ˵    �� : ����ӿγ���Ϣ
*  ���ؽ�� : ��
*
*******************************************************************************/
void AddData(FileIndex & fi)
{
    int nIndex(0) ;
    int i(0), j(0), k(0);
    char buf[32] = {0} ;
    char buffer[48] = {0} ;
    char day[7] = "198583" ;
    char tele[12] = "87818781" ;

    // ���ѧ��
    for (i = 0; i < 50; ++i)
    {
        for (j = 0; j < 20; ++j)
        {
            for (k = 0; k < 120; ++k)
            {
                memset(buf, 0, 32) ;
                strcpy(buf, surnamed[i]) ;
                strcat(buf, mind[j]) ;
                strcat(buf, name[k]) ;
                fi.studbf.SetString("name", buf) ;
                fi.studbf.SetString("sex", (k/2==0)?"M":"F") ;
                fi.studbf.SetString("birthday", day) ;
                fi.studbf.SetString("telephone", tele) ;
                nIndex = fi.studbf.AddRecord() ;
                fi.stuNameIndex.Insert(buf, nIndex) ;
            }
        }
    }

    // �����ʦ
    for (i = 0; i < 50; ++i)
    {
        for (j = 10; j < 20; ++j)
        {
            for (k = 0; k < 110; ++k)
            {
                memset(buf, 0, 32) ;
                strcpy(buf, surnamed[i]) ;
                strcat(buf, mind[j]) ;
                strcat(buf, name[k]) ;
                fi.teadbf.SetString("name", buf) ;
                fi.teadbf.SetString("sex", (k/2==0)?"M":"F") ;
                fi.teadbf.SetString("birthday", day) ;
                fi.teadbf.SetString("telephone", tele) ;
                nIndex = fi.teadbf.AddRecord() ;
                fi.teaNameIndex.Insert(buf, nIndex) ;
            }
        }
    }

    // ���ѡ��
    for (i = 1; i < 55000; i += 5)
    {
        for (j = 1 ; j <= 2; ++j)
        {
            memset(buf, 0, 10) ;
            sprintf(buf, "%10d", i) ;
            fi.stuSlectdbf.SetString("stuId", buf) ;
            
            memset(buf, 0, 10) ;
            sprintf(buf, "%10d", j) ;
            fi.stuSlectdbf.SetString("LesId", buf) ;
            memset(buf, 0, 10) ;
            sprintf(buf, "%4d", 90) ;
            fi.stuSlectdbf.SetString("grade", buf) ;

            nIndex = fi.stuSlectdbf.AddRecord() ;
            fi.stuLesSelect[j-1].Push(i-1, nIndex) ;
            fi.stuSelect[i-1].Push(j-1, nIndex) ;
        }
    }

    // ����ο�
    memset(buf, 0, 32) ;
    for (i = 1; i < 55000; i += 8)
    {
        for (j = 1 ; j <= 2; ++j)
        {
            memset(buf, 0, 10) ;
            sprintf(buf, "%10d", i) ;
            fi.teaSelectdbf.SetString("TeaId", buf) ;

            memset(buf, 0, 10) ;
            sprintf(buf, "%10d", j) ;
            fi.teaSelectdbf.SetString("LesId", buf) ;

            nIndex = fi.teaSelectdbf.AddRecord() ;
            fi.teaLesSelect[j-1].Push(i-1, nIndex) ;
            fi.teaSelect[i-1].Push(j-1, nIndex) ;
        }
    }
}

int TestCollide(RedBlackTree & T)
{
	return 1 ;
}