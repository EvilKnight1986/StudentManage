/******************************************************************************
* Copyright (c) 2009, 黄奇 ,All right reserved.
*
* 文 件 名: FileIndex.cpp
*
* 功能描述: 文件索引类，索引的创建、导入以及导出
*
* 创 建 人: 黄奇,  2009年 9月19日
*
* 创建日期: 2009.9.19
*
* 版 本 号: 1.0
*
* 修改记录: 
*
* 编绎环境：Windows XP SP2、 VC 6.0 sp6
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
*  函 数 名 : FileIndex
*  功能描述 : FileIndex类的构造函数，只能显示调用
*  参数列表 : 
*  说    明 : 初始化dbf以及调用检查索引文件
*  返回结果 : 
*
*******************************************************************************/
FileIndex::FileIndex():lessdbf(LESSONDBF),teadbf(TEACHERDBF),studbf(STUDENTDBF),\
stuSlectdbf(STUSELECTDBF),teaSelectdbf(TEASELECTDBF)
{
    CheckIndex() ;
}

/*******************************************************************************
*
*  函 数 名 : ~FileIndex
*  功能描述 : FileIndex类的析构函数
*  参数列表 : 
*  说    明 : 保存索引文件
*  返回结果 : 
*
*******************************************************************************/
FileIndex::~FileIndex()
{
    // 保存索引
    stuSelect.ExportFile(STUSELECT) ;
    stuLesSelect.ExportFile(STULESSELECT)  ;
    teaSelect.ExportFile(TEASELECT) ;
    teaLesSelect.ExportFile(TEALESSELECT) ;
    
    lessonNameIndex.ExportFile(LESSNAMEINDEX) ;
    teaNameIndex.ExportFile(TEANAMEINDEX) ;
	stuNameIndex.ExportFile(STUNAMEINDEX) ;
    cout << "\t保存索引成功.." << endl ;
}

/*******************************************************************************
*
*  函 数 名 : CheckIndex
*  功能描述 : 检测索引文件
*  参数列表 : 
*  说    明 : 
*  返回结果 : 成功返回 1, 失败返回 0
*
*******************************************************************************/
int FileIndex::CheckIndex()
{
    // 先检测学生姓名索引
    // 如果找不到索引文件，则创建，否则导入
    if (_access(STUNAMEINDEX, 0) == -1)
    {
        cout << "\t找不到索引，需建立学生索引..." << endl ;
        CreateNameIndex("student") ;
    }
    else
    {
        // 如果索引有效，则载入
        if (CheckIndexSucc(STUNAMEINDEX) == 1)
        {
            // 载入索引
            stuNameIndex.ImportFile(STUNAMEINDEX) ;
            // 置索引无效
            SetIndexInvalida(STUNAMEINDEX) ;
        }
        else
        {
            cout << "\t因程序错误退出，需重建学生索引..." << endl ;
            CreateNameIndex("student") ;
          #ifdef _DEBUG
            Sleep(500) ;
          #endif
        }
    }


    // 检测老师姓名索引
    if (_access(TEANAMEINDEX, 0) == -1)
    {
        cout << "\t找不到索引，需建立老师索引..." << endl ;
        CreateNameIndex("teacher") ;
    }
    else
    {
        // 如果索引有效，则载入
        if (CheckIndexSucc(TEANAMEINDEX) == 1)
        {
            // 载入索引
            teaNameIndex.ImportFile(TEANAMEINDEX) ;
            // 置索引无效
            SetIndexInvalida(TEANAMEINDEX) ;
        }
        else
        {
            cout << "\t因程序错误退出，需重建教师索引..." << endl ;
            CreateNameIndex("teacher") ;
          #ifdef _DEBUG
            Sleep(500) ;
          #endif
        }
    }

    // 检测课程名索引
    if (_access(LESSNAMEINDEX, 0) == -1)
    {
        cout << "\t找不到索引，需建立课程索引..." << endl ;
        CreateNameIndex("lesson") ;
    }
    else
    {
        // 如果索引有效，则载入
        if (CheckIndexSucc(LESSNAMEINDEX) == 1)
        {
            // 载入索引
            lessonNameIndex.ImportFile(LESSNAMEINDEX) ;
            // 置索引无效
            SetIndexInvalida(LESSNAMEINDEX) ;
        }
        else
        {
            cout << "\t因程序错误退出，需重建课程索引..." << endl ;
            CreateNameIndex("lesson") ;
          #ifdef _DEBUG
            Sleep(500) ;
          #endif
        }
    }


    // 检测选课索引
    if ((_access(STUSELECT, 0) == -1) || (_access(STULESSELECT, 0) == -1))
    {
        cout << "\t找不到索引，需建立学生选课索引..." << endl ;
        CreateSelectIndex("stuLesson") ;
    }
    else
    {
        if (CheckIndexSucc(STUSELECT) == 1 && CheckIndexSucc(STULESSELECT) == 1)
        {
            stuSelect.ImportFile(STUSELECT) ;
            stuLesSelect.ImportFile(STULESSELECT) ;
            // 置索引无效
            SetIndexInvalida(STUSELECT) ;
            SetIndexInvalida(STULESSELECT) ;
        }
        else
        {
            cout << "\t因程序错误退出，需重建学生选课索引..." << endl ;
            CreateSelectIndex("stuLesson") ;
          #ifdef _DEBUG
            Sleep(500) ;
          #endif
        }
    }

    // 检测老师任课索引
    if ((_access(TEASELECT, 0) == -1) || (_access(TEALESSELECT, 0) == -1))
    {
        cout << "\t找不到索引，需建立老师任课索引..." << endl ;
        CreateSelectIndex("teaLesson") ;
    }
    else
    {
        if (CheckIndexSucc(TEASELECT) == 1 && CheckIndexSucc(TEALESSELECT) == 1)
        {
            teaSelect.ImportFile(TEASELECT) ;
            teaLesSelect.ImportFile(TEALESSELECT) ;
            // 置索引无效
            SetIndexInvalida(TEASELECT) ;
            SetIndexInvalida(TEALESSELECT) ;
        }
        else
        {
            cout << "\t因程序错误退出，需重建教师任课索引..." << endl ;
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
*  函 数 名 : CreateNameIndex
*  功能描述 : 检测姓名索引文件
*  参数列表 : szName   ---   用于区分学生或教师
*  说    明 : 
*  返回结果 : 成功返回 1, 失败返回 0
*
*******************************************************************************/
int FileIndex::CreateNameIndex(const char * szName)
{
    if (szName == NULL)
    {
        return 0 ;
    }

    // 创建学生索引
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
*  函 数 名 : CreateSelectIndex
*  功能描述 : 创建选课任课索引
*  参数列表 : szName   ---   用于区分学生或教师
*  说    明 : 
*  返回结果 : 成功返回 1, 失败返回 0
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
    // 处理学生选课
    if (stricmp(szName, "stuLesson") == 0)
    {
        for (i = 0; ; ++i)
        {
            state = stuSlectdbf.ReadRecord(i) ;
            // 如果读到文件尾了
            if (state == -1)
            {
                break ;
            }
            // 如果读出数据
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
    // 处理老师认课
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
*  函 数 名 : CreateAdjIndex
*  功能描述 : 未添加
*  参数列表 : 
*  说    明 : 
*  返回结果 : 
*
*******************************************************************************/
int FileIndex::CreateAdjIndex(Adjacency &la, Adjacency &ra)
{
    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : CreateRBTIndex
*  功能描述 : 创建索引
*  参数列表 : d   ---   dbf 文件句柄
              T   ---   红黑树的句柄
*  说    明 : 
*  返回结果 : 成功返回 1, 失败返回 0
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
        *  修改人: 黄 奇
        *  时  间: 2009.9.22
        *  修  改: 加入else if (state)
        *          当重建索引的时候，读读到记录为空的时间，往空闲空间链表加入
        *
        *          解决原来系统中，当空闲过大时，每次操作都写文件的问题
        ***********************************************************************/
        // 如果这条记录已经删除
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
*  函 数 名 : CheckDBF
*  功能描述 : 检测数据文件是否存在
*  参数列表 : 
*  说    明 : 如果不存在的话，自动创建
*  返回结果 : 如果成功，返回1，否则返回0
*
*******************************************************************************/
int CheckDBF(void)
{
    int nState = false ;
    unsigned int nInitSize = 0 ;
    // 如果学生表不存在,或者为空
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
    // 如果学生数据文件不存在或者文件长度过短，创建之
    if (_access(STUDENTDBF, 0) == -1 || nState)
    {
        dbf stu(STUDENTDBF) ;
        // 创建DBF头信息
        stu.CreateHead() ;
        // 添加项
        stu.AddField("id",        'N', 10) ;
        stu.AddField("name",      'C', 32) ;
        stu.AddField("sex",       'C',  4) ;
        stu.AddField("birthday",  'N', 11) ;
        stu.AddField("telephone", 'N', 13) ;
        
        // Display DBF Head of Information
        stu.DisplayHeadInformat() ;
        stu.DisplayFieldInformat() ;
        
        // 将DBF头信息写入文件
        stu.HeadWriteToFile() ;
        // 初始为 5M
        stu.InitFileSize(nInitSize) ;
        stu.Submit() ;
        
        if (fp != NULL)
        {
            fclose(fp) ;
            fp = NULL ;
        }
    }

    // 如果课程表不存在,或者为空
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
    
     // 如果课程数据文件不存在或者文件长度过短，创建之
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
    
    // 如果老师表不存在,或者为空
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

    // 如果学生选课表不存在,或者为空
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

    // 如果老师选课表不存在,或者为空
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
*  函 数 名 : CheckIndexSucc
*  功能描述 : 检测索引文件是有效
*  参数列表 : 
*  说    明 : 
*  返回结果 : 如果正确，返回1，否则返回0
*
*******************************************************************************/
int FileIndex::CheckIndexSucc(const char *FileName)
{
    FILE * fp = NULL ;
    int i(0),
        state(0) ;
    i = ~i;

    // 在读之前，判断上次是否是正确关闭文件
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
*  函 数 名 : SetIndexInvalida
*  功能描述 : 将索引文件置为无效
*  参数列表 : 
*  说    明 : 
*  返回结果 : 如果成功，返回1，否则返回0
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
