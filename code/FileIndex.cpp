/******************************************************************************
* Copyright (c) 2009, ���� ,All right reserved.
*
* �� �� ��: FileIndex.cpp
*
* ��������: �ļ������࣬�����Ĵ����������Լ�����
*
* �� �� ��: ����,  2009�� 9��19��
*
* ��������: 2009.9.19
*
* �� �� ��: 1.0
*
* �޸ļ�¼: 
*
* ���ﻷ����Windows XP SP2�� VC 6.0 sp6
* 
*******************************************************************************/

#include "FileIndex.h"
#if _MSC_VER >= 1400
  #pragma warning(disable:4996)
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*******************************************************************************
*
*  �� �� �� : FileIndex
*  �������� : FileIndex��Ĺ��캯����ֻ����ʾ����
*  �����б� : 
*  ˵    �� : ��ʼ��dbf�Լ����ü�������ļ�
*  ���ؽ�� : 
*
*******************************************************************************/
FileIndex::FileIndex():lessdbf(LESSONDBF),teadbf(TEACHERDBF),studbf(STUDENTDBF),\
stuSlectdbf(STUSELECTDBF),teaSelectdbf(TEASELECTDBF)
{
    CheckIndex() ;
}

/*******************************************************************************
*
*  �� �� �� : ~FileIndex
*  �������� : FileIndex�����������
*  �����б� : 
*  ˵    �� : ���������ļ�
*  ���ؽ�� : 
*
*******************************************************************************/
FileIndex::~FileIndex()
{
    // ��������
    stuSelect.ExportFile(STUSELECT) ;
    stuLesSelect.ExportFile(STULESSELECT)  ;
    teaSelect.ExportFile(TEASELECT) ;
    teaLesSelect.ExportFile(TEALESSELECT) ;
    
    lessonNameIndex.ExportFile(LESSNAMEINDEX) ;
    teaNameIndex.ExportFile(TEANAMEINDEX) ;
	stuNameIndex.ExportFile(STUNAMEINDEX) ;
    cout << "\t���������ɹ�.." << endl ;
}

/*******************************************************************************
*
*  �� �� �� : CheckIndex
*  �������� : ��������ļ�
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : �ɹ����� 1, ʧ�ܷ��� 0
*
*******************************************************************************/
int FileIndex::CheckIndex()
{
    // �ȼ��ѧ����������
    // ����Ҳ��������ļ����򴴽���������
    if (_access(STUNAMEINDEX, 0) == -1)
    {
        cout << "\t�Ҳ����������轨��ѧ������..." << endl ;
        CreateNameIndex("student") ;
    }
    else
    {
        // ���������Ч��������
        if (CheckIndexSucc(STUNAMEINDEX) == 1)
        {
            // ��������
            stuNameIndex.ImportFile(STUNAMEINDEX) ;
            // ��������Ч
            SetIndexInvalida(STUNAMEINDEX) ;
        }
        else
        {
            cout << "\t���������˳������ؽ�ѧ������..." << endl ;
            CreateNameIndex("student") ;
          #ifdef _DEBUG
            Sleep(500) ;
          #endif
        }
    }


    // �����ʦ��������
    if (_access(TEANAMEINDEX, 0) == -1)
    {
        cout << "\t�Ҳ����������轨����ʦ����..." << endl ;
        CreateNameIndex("teacher") ;
    }
    else
    {
        // ���������Ч��������
        if (CheckIndexSucc(TEANAMEINDEX) == 1)
        {
            // ��������
            teaNameIndex.ImportFile(TEANAMEINDEX) ;
            // ��������Ч
            SetIndexInvalida(TEANAMEINDEX) ;
        }
        else
        {
            cout << "\t���������˳������ؽ���ʦ����..." << endl ;
            CreateNameIndex("teacher") ;
          #ifdef _DEBUG
            Sleep(500) ;
          #endif
        }
    }

    // ���γ�������
    if (_access(LESSNAMEINDEX, 0) == -1)
    {
        cout << "\t�Ҳ����������轨���γ�����..." << endl ;
        CreateNameIndex("lesson") ;
    }
    else
    {
        // ���������Ч��������
        if (CheckIndexSucc(LESSNAMEINDEX) == 1)
        {
            // ��������
            lessonNameIndex.ImportFile(LESSNAMEINDEX) ;
            // ��������Ч
            SetIndexInvalida(LESSNAMEINDEX) ;
        }
        else
        {
            cout << "\t���������˳������ؽ��γ�����..." << endl ;
            CreateNameIndex("lesson") ;
          #ifdef _DEBUG
            Sleep(500) ;
          #endif
        }
    }


    // ���ѡ������
    if ((_access(STUSELECT, 0) == -1) || (_access(STULESSELECT, 0) == -1))
    {
        cout << "\t�Ҳ����������轨��ѧ��ѡ������..." << endl ;
        CreateSelectIndex("stuLesson") ;
    }
    else
    {
        if (CheckIndexSucc(STUSELECT) == 1 && CheckIndexSucc(STULESSELECT) == 1)
        {
            stuSelect.ImportFile(STUSELECT) ;
            stuLesSelect.ImportFile(STULESSELECT) ;
            // ��������Ч
            SetIndexInvalida(STUSELECT) ;
            SetIndexInvalida(STULESSELECT) ;
        }
        else
        {
            cout << "\t���������˳������ؽ�ѧ��ѡ������..." << endl ;
            CreateSelectIndex("stuLesson") ;
          #ifdef _DEBUG
            Sleep(500) ;
          #endif
        }
    }

    // �����ʦ�ο�����
    if ((_access(TEASELECT, 0) == -1) || (_access(TEALESSELECT, 0) == -1))
    {
        cout << "\t�Ҳ����������轨����ʦ�ο�����..." << endl ;
        CreateSelectIndex("teaLesson") ;
    }
    else
    {
        if (CheckIndexSucc(TEASELECT) == 1 && CheckIndexSucc(TEALESSELECT) == 1)
        {
            teaSelect.ImportFile(TEASELECT) ;
            teaLesSelect.ImportFile(TEALESSELECT) ;
            // ��������Ч
            SetIndexInvalida(TEASELECT) ;
            SetIndexInvalida(TEALESSELECT) ;
        }
        else
        {
            cout << "\t���������˳������ؽ���ʦ�ο�����..." << endl ;
            CreateSelectIndex("teaLesson") ;
          #ifdef _DEBUG
            Sleep(500) ;
          #endif
        }
    }

    return 1 ;
}

/*******************************************************************************
*
*  �� �� �� : CreateNameIndex
*  �������� : ������������ļ�
*  �����б� : szName   ---   ��������ѧ�����ʦ
*  ˵    �� : 
*  ���ؽ�� : �ɹ����� 1, ʧ�ܷ��� 0
*
*******************************************************************************/
int FileIndex::CreateNameIndex(const char * szName)
{
    if (szName == NULL)
    {
        return 0 ;
    }

    // ����ѧ������
    if (stricmp(szName, "student") == 0)
    {
        CreateRBTIndex(studbf, stuNameIndex) ;
    }
    else if (stricmp(szName, "teacher") == 0)
    {
        CreateRBTIndex(teadbf,teaNameIndex) ;
    }
    else
    {
        CreateRBTIndex(lessdbf,lessonNameIndex) ;
    }
    return 1 ;
}

/*******************************************************************************
*
*  �� �� �� : CreateSelectIndex
*  �������� : ����ѡ���ο�����
*  �����б� : szName   ---   ��������ѧ�����ʦ
*  ˵    �� : 
*  ���ؽ�� : �ɹ����� 1, ʧ�ܷ��� 0
*
*******************************************************************************/
int FileIndex::CreateSelectIndex(const char *szName)
{
    if (szName == NULL)
    {
        return 0 ;
    }

    int i(0)     ,
        state(0) ,
        StuId(0) ,
        LesId(0) ,
        TeaId(0) ;
    char buf[32] = {0} ;
    // ����ѧ��ѡ��
    if (stricmp(szName, "stuLesson") == 0)
    {
        for (i = 0; ; ++i)
        {
            state = stuSlectdbf.ReadRecord(i) ;
            // ��������ļ�β��
            if (state == -1)
            {
                break ;
            }
            // �����������
            else if (state == 1)
            {
                memset(buf, 0, sizeof(char) * 32) ;
                stuSlectdbf.ReadItem("stuId", buf) ;
                StuId = atoi(buf) ;
                memset(buf, 0, 32) ;
                stuSlectdbf.ReadItem("lesId", buf) ;
                LesId = atoi(buf) ;
                stuSelect[StuId].Push(LesId, i) ;
                stuLesSelect[LesId].Push(StuId, i) ;
            }
        }
    }
    // ������ʦ�Ͽ�
    else if (stricmp(szName, "teaLesson") == 0)
    {
        for (i = 0; ; ++i)
        {
            state = teaSelectdbf.ReadRecord(i) ;
            if (state == -1)
            {
                break ;
            }
            else if (state == 1)
            {
                memset(buf, 0, sizeof(char) * 32) ;
                teaSelectdbf.ReadItem("teaId", buf) ;
                TeaId = atoi(buf) ;
                TeaId -= 1 ;

                memset(buf, 0, sizeof(char) * 32) ;
                teaSelectdbf.ReadItem("lesId", buf) ;
                LesId = atoi(buf) ;
                LesId -= 1 ;

                teaSelect[TeaId].Push(LesId,    i) ;
                teaLesSelect[LesId].Push(TeaId, i) ;
            }
        }
    }
    return 1 ;
}

/*******************************************************************************
*
*  �� �� �� : CreateAdjIndex
*  �������� : δ���
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : 
*
*******************************************************************************/
int FileIndex::CreateAdjIndex(Adjacency &la, Adjacency &ra)
{
    return 1 ;
}

/*******************************************************************************
*
*  �� �� �� : CreateRBTIndex
*  �������� : ��������
*  �����б� : d   ---   dbf �ļ����
              T   ---   ������ľ��
*  ˵    �� : 
*  ���ؽ�� : �ɹ����� 1, ʧ�ܷ��� 0
*
*******************************************************************************/
int FileIndex::CreateRBTIndex(dbf &d, RedBlackTree &T)
{
    int i(0)     ,
        state(0) ;
    char buf[64] = {0} ;

    T.Clear() ;
    for(; ; ++i)
    {
        state = d.ReadRecord(i) ;
        if (state == -1)
        {
            break ;
        }
        /***********************************************************************
        *  �޸���: �� ��
        *  ʱ  ��: 2009.9.22
        *  ��  ��: ����else if (state)
        *          ���ؽ�������ʱ�򣬶�������¼Ϊ�յ�ʱ�䣬�����пռ��������
        *
        *          ���ԭ��ϵͳ�У������й���ʱ��ÿ�β�����д�ļ�������
        ***********************************************************************/
        // ���������¼�Ѿ�ɾ��
        else if (state == 0)
        {
            d.pFree.Push(i) ;
        }
        else if (state == 1)
        {
            d.ReadString("name", buf) ;
            SkipSpace(buf, 64) ;
            T.Insert(buf, i) ;      
        }
    }
    return 1 ;
}

/*******************************************************************************
*
*  �� �� �� : CheckDBF
*  �������� : ��������ļ��Ƿ����
*  �����б� : 
*  ˵    �� : ��������ڵĻ����Զ�����
*  ���ؽ�� : ����ɹ�������1�����򷵻�0
*
*******************************************************************************/
int CheckDBF(void)
{
    int nState = false ;
    unsigned int nInitSize = 0 ;
    // ���ѧ��������,����Ϊ��
    FILE *fp = fopen(STUDENTDBF, "r+b") ;
    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END) ;
        if (ftell(fp) < 162)
        {
            nState = true ;
        }
        else
        {
            nState = false ;
        }
    }
    // ���ѧ�������ļ������ڻ����ļ����ȹ��̣�����֮
    if (_access(STUDENTDBF, 0) == -1 || nState)
    {
        dbf stu(STUDENTDBF) ;
        // ����DBFͷ��Ϣ
        stu.CreateHead() ;
        // �����
        stu.AddField("id",        'N', 10) ;
        stu.AddField("name",      'C', 32) ;
        stu.AddField("sex",       'C',  4) ;
        stu.AddField("birthday",  'N', 11) ;
        stu.AddField("telephone", 'N', 13) ;
        
        // Display DBF Head of Information
        stu.DisplayHeadInformat() ;
        stu.DisplayFieldInformat() ;
        
        // ��DBFͷ��Ϣд���ļ�
        stu.HeadWriteToFile() ;
        // ��ʼΪ 5M
        stu.InitFileSize(nInitSize) ;
        stu.Submit() ;
        
        if (fp != NULL)
        {
            fclose(fp) ;
            fp = NULL ;
        }
    }

    // ����γ̱�����,����Ϊ��
    nState = false ;
    fp = fopen(LESSONDBF, "r+b") ;
    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END) ;
        if (ftell(fp) < 98)
        {
            nState = true ;
        }
        else
        {
            nState = false ;
        }
    }
    
     // ����γ������ļ������ڻ����ļ����ȹ��̣�����֮
    if (_access(LESSONDBF, 0) == -1 || nState)
    {
        dbf les(LESSONDBF) ;
        les.CreateHead() ;
        les.AddField("id" ,    'N', 10) ;
        les.AddField("name",   'C', 48) ;
        les.AddField("mark",   'N',  2) ;
        les.AddField("period", 'N',  4) ;

        les.DisplayHeadInformat() ;
        les.DisplayFieldInformat() ;

        les.HeadWriteToFile() ;
        les.InitFileSize(nInitSize) ;
        les.Submit() ;

        if (fp != NULL)
        {
            fclose(fp) ;
            fp = NULL ;
        }
    }
    
    // �����ʦ������,����Ϊ��
    nState = false ;
    fp = fopen(TEACHERDBF, "r+b") ;
    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END) ;
        if (ftell(fp) < 162)
        {
            nState = true ;
        }
        else
        {
            nState = false ;
        }
    }
    if (_access(TEACHERDBF, 0) == -1 || nState)
    {
        dbf tea(TEACHERDBF);
        tea.CreateHead() ;
        tea.AddField("id",        'N', 10) ;
        tea.AddField("name",      'C', 32) ;
        tea.AddField("sex",       'C',  4) ;
        tea.AddField("birthday",  'N', 11) ;
        tea.AddField("telephone", 'N', 13) ;
        
        tea.DisplayHeadInformat() ;
        tea.DisplayFieldInformat() ;
        
        tea.HeadWriteToFile() ;
        tea.InitFileSize(nInitSize) ;
        tea.Submit() ;
        
        if (fp != NULL)
        {
            fclose(fp) ;
            fp = NULL ;
        }
    }

    // ���ѧ��ѡ�α�����,����Ϊ��
    nState = false ;
    fp = fopen(STUSELECTDBF, "r+b") ;
    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END) ;
        if (ftell(fp) < 24)
        {
            nState = true ;
        }
        else
        {
            nState = false ;
        }
    }
    if (_access(STUSELECTDBF, 0) == -1 || nState)
    {
        dbf stuSel(STUSELECTDBF);
        stuSel.CreateHead() ;
        stuSel.AddField("id",         'N', 10) ;
        stuSel.AddField("stuId",      'N', 10) ;
        stuSel.AddField("LesId",      'N', 10) ;
        stuSel.AddField("grade",      'N',  4) ;
        
        stuSel.DisplayHeadInformat() ;
        stuSel.DisplayFieldInformat() ;
        
        stuSel.HeadWriteToFile() ;
        stuSel.InitFileSize(nInitSize) ;
        stuSel.Submit() ;
        
        if (fp != NULL)
        {
            fclose(fp) ;
            fp = NULL ;
        }
    }

    // �����ʦѡ�α�����,����Ϊ��
    nState = false ;
    fp = fopen(TEASELECTDBF, "r+b") ;
    if (fp != NULL)
    {
        fseek(fp, 0, SEEK_END) ;
        if (ftell(fp) < 20)
        {
            nState = true ;
        }
        else
        {
            nState = false ;
        }
    }
    if (_access(TEASELECTDBF, 0) == -1 || nState)
    {
        dbf teaSel(TEASELECTDBF);
        teaSel.CreateHead() ;
        teaSel.AddField("id",         'N', 10) ;
        teaSel.AddField("TeaId",      'N', 10) ;
        teaSel.AddField("LesId",      'N', 10) ;
        
        teaSel.DisplayHeadInformat() ;
        teaSel.DisplayFieldInformat() ;
        
        teaSel.HeadWriteToFile() ;
        teaSel.InitFileSize(nInitSize) ;
        teaSel.Submit() ;
        
        if (fp != NULL)
        {
            fclose(fp) ;
            fp = NULL ;
        }
    }

    return 1 ;
}

/*******************************************************************************
*
*  �� �� �� : CheckIndexSucc
*  �������� : ��������ļ�����Ч
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : �����ȷ������1�����򷵻�0
*
*******************************************************************************/
int FileIndex::CheckIndexSucc(const char *FileName)
{
    FILE * fp = NULL ;
    int i(0),
        state(0) ;
    i = ~i;

    // �ڶ�֮ǰ���ж��ϴ��Ƿ�����ȷ�ر��ļ�
    fp = fopen(FileName, "rb") ;
    if (fp != NULL)
    {
        rewind(fp) ;
        fread(&state, sizeof(int), 1, fp) ;        
        fclose(fp) ;
        fp = NULL ;
        if (state == i)
        {
            return 0 ;
        }
    }
    return 1 ;
}

/*******************************************************************************
*
*  �� �� �� : SetIndexInvalida
*  �������� : �������ļ���Ϊ��Ч
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : ����ɹ�������1�����򷵻�0
*
*******************************************************************************/
int FileIndex::SetIndexInvalida(const char *FileName)
{
    int i(0) ;
    i = ~i ;

    FILE * fp = NULL ;

    fp = fopen(FileName, "wb") ;
    if (fp != NULL)
    {
        fwrite(&i, sizeof(int), 1, fp) ;
        fclose(fp) ;
        fp = NULL ;
        return 1;
    }
    return 0;
}
