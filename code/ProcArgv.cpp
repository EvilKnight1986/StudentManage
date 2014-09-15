// ProcArgv.cpp: implementation of the ProcArgv class.
//
//////////////////////////////////////////////////////////////////////

/*******************************************************************************
*  
*  Copyright (c) all 2009 黄奇 All rights reserved
*  FileName : ProcArgv.cpp
*  D a t e  : 2009.9.20
*  功   能  : 处理用户请求
*  说   明  : 
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
*  函 数 名 : StuSelManageProc
*  功能描述 : 处理学生选课主程序
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 无
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
            // 查询学生选课
            StuSelSelectProc(fi) ;
            break;
        case 2:
            // 增加学生选课
            StuSelAddProc(fi) ;
            break;
        case 3:
            // 修改学生选课
            StuSelModifiProc(fi) ;
            break;
        case 4:
            // 删除学生选课
            StuSelDeleteProc(fi) ;
            break;
        case 5:
            // 查询课程被选的情况
            StuSelShowProc(fi) ;
            break ;
        default:
            cout << "\t请正确选择" << endl ;
        }
        StuSelManageMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : StuSelSelectProc
*  功能描述 : 用户查询学生选课处理例程
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 无
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

        // 通过学号查询
        if (n == 1)
        {
            cout << "\t请输入要查询学生的学号: " << flush ;
            cin >> id ;
        } // end of if

        // 通过姓名查询
        else if (n == 2)
        {
            if (SelectStudentName(fi) == 1)
            {
                cout << "\t请再输入您要查询学生的id: " << flush ;
                cin >> id ;
                if (id <= 0)
                {
                    cout << "\t不要徒劳寻找系统漏洞" << endl ;
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
                    cout << "\t对不起，找不到此学生" << endl ;
                    //getchar() ;
                }
                else if (nSize == 0)
                {
                    cout << "\t对不起，此学生还没有选课" << endl ;
                }
                else
                {
                    DisplayStudentTitle() ;
                    cout << fi.studbf << endl << endl;
                    cout << "\t该学生共选了" << setw(2) << nSize << "门课程" << endl ;
                    cout << endl << "\t选课列表" << endl ;
                    DisplayStuSelTitle() ;
                    for (i = 0; i < nSize; ++i)
                    {
                        if (fi.lessdbf.ReadRecord(p->operator [](i)->GetData()) == 1)
                        {
                            cout << fi.lessdbf << flush ;
                            // 读出成绩
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
            cout << "\t不要试图寻找系统的漏洞" << endl ;
        }
        fflush(stdin) ;
        getchar() ;
        SelectStuSelMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : StuSelAddProc
*  功能描述 : 添加学生选课
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入要选课学生的id: " << flush ;
            cin >> StuId ;
            while (StuId < 1  && fi.studbf.ReadRecord(StuId - 1) != 1)
            {
                cout << "\tid不正确,请重新输入" << endl ;
                cin >> StuId ;
            }

            memset(buf, 0, 16) ;
            sprintf(buf, "%10d", StuId - 1) ;
            fi.stuSlectdbf.SetString("stuId", buf) ;

            cout << "\t请输入要选的课程ID: " << flush ;
            cin >> LesId ;
            while(LesId < 1  && fi.lessdbf.ReadRecord(LesId - 1) != 1)
            {
                cout << "\t课程id不正确,请重新输入" << endl ;
                cin >> LesId ;
            }
            memset(buf, 0, 16) ;
            sprintf(buf, "%10d", LesId - 1) ;
            fi.stuSlectdbf.SetString("LesId", buf) ;

            memset(buf, 0, 16) ;

            cout << "\t是否要设置该生这门课程的分数: Y/N: " << flush ;  
            cin >> state ;

            if (state == 'y' || state == 'Y')
            {
                cout << "\t请输入成绩: " << flush ;
                cin >> grade ;
                while (grade < 0 || grade > 100)
                {
                    cout << "\t分数范围不对，请重新输入" << endl ;
                    cin >> grade ;
                }
            }

            // 默认成绩60分
            sprintf(buf, "%4d", grade) ;
            fi.stuSlectdbf.SetString("grade", buf) ;

            // 判断学生是否已经选了这门课
            if (fi.stuSelect[StuId-1].Find(LesId-1) == NULL)
            {
                offset = fi.stuSlectdbf.AddRecord() ;
                // 更新索引
                fi.stuLesSelect[LesId-1].Push(StuId-1, offset) ;
                fi.stuSelect[StuId-1].Push(LesId-1, offset) ;
                cout << "\t添加成功" << endl ;
            }
            else
            {
                cout << "\t添加失败，已经存在" << endl ;
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
*  函 数 名 : StuSelShowProc
*  功能描述 : 查询课程被选的情况
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入查询课程ID: " << flush ;
            cin >> LesId ;
            while(fi.lessdbf.ReadRecord(LesId-1) != 1)
            {
                cout << "\t课程号不正确，请重新输入: " << flush ;
                cin >> LesId ;
            }
        }
        else if (n == 2)
        {
            if (SelectLesName(fi) == 1)
            {
                cout << "\t请输入查询课程ID: " << flush ;
                cin >> LesId ;
                while(fi.lessdbf.ReadRecord(LesId-1) != 1)
                {
                    cout << "\t课程号不正确，请重新输入: " << flush ;
                    cin >> LesId ;
                    if (LesId == 0)
                    {
                        break ;
                    }
                }
            }
            else
            {
                cout << "\t输入任意字符继续" << endl ;
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
                cout << "\t选了这门课的学生共有 " << setw(2) << nSize << flush;
                cout << "位" << endl ;
                // 输出各个选课学生的姓名和学号
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
                cout << "\t对不起，这门课程没有学生选课" << endl ;
            }
        }

        if (n != 1 && n != 2)
        {
            cout << "\t请输入正确选项" << endl ;
        }

        fflush(stdin) ;
        getchar() ;
        SelectLessMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : StuSelModifiProc
*  功能描述 : 修改学生选课
*  参数列表 : fi   --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入学生id: " << flush ;
            cin >> StuId ;
            while(StuId <= 0 && fi.studbf.ReadRecord(StuId-1) != 1)
            {
                cout << "\t输入学生id不正确,请重新输入: " << flush ;
                cin >> StuId ;
            }

            cout << "\t请输入课程id: " << flush ;
            cin >> LesId ;

            while(LesId <= 0 && fi.lessdbf.ReadRecord(LesId-1) != 1)
            {
                cout << "\t输入课程id不正确,请重新输入: " << flush ;
                cin >> LesId ;
            }
            
            // 取出指定学生选课信息节点中的链表
            p = fi.stuSelect[StuId-1].Find(LesId-1) ;
            if (p != NULL)
            {
                int offset = p->GetOffset() ;
                char buf[8] = {0} ;
                
                // 读出原来的分数
                fi.stuSlectdbf.ReadRecord(offset) ;
                fi.stuSlectdbf.ReadItem("grade", buf) ;
                
                cout << "\t原分数: " << buf << endl ;
                cout << "\t请输入新的分数: " << flush ;
                cin >> grade ;
                while (grade < 0 || grade > 100)
                {
                    cout << "\t分数范围不对，请重新输入" << endl ;
                    cin >> grade ;
                }
                sprintf(buf, "%4d", grade) ;
                fi.stuSlectdbf.SetString("grade", buf) ;
                if (fi.stuSlectdbf.WriteRecord(offset) == offset)
                {
                    cout << "\t修改分数成功" << endl ;
                }
                else
                {
                    cout << "\t修改分数失败" << endl ;
                }
            }
            else
            {
                cout << "\t对不起，该生没有选修这门课程" << endl ;
            }
        }
        getchar() ;
        fflush(stdin) ;
        ModifiStuSelMenu() ;
    }

}

/*******************************************************************************
*
*  函 数 名 : StuSelDeleteProc
*  功能描述 : 删除学生选课
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入学生id: " << flush ;
            cin >> StuId ;
            while(StuId <= 0 && fi.studbf.ReadRecord(StuId-1) != 1)
            {
                cout << "\t输入学生id不正确,请重新输入: " << flush ;
                cin >> StuId ;
            }

            int i(0) ,
                nSize(fi.stuSelect[StuId-1].GetSize()) ;
            if (nSize > 0)
            {
                cout << "\t该生共选课"<< nSize << "门" << flush ;
                cout << "选课列表如下:(只显示课程id)" << endl ;
            }
            else
            {
                cout << "\t该生没有选课" << endl ;
            }
            
            cout << "\t" << flush;
            
            // 输出学生所选的课程的id
            for (; i < nSize ; ++i)
            {
                cout << fi.stuSelect[StuId-1][i]->data + 1 << " " ;
            }
            cout << endl ;
            
            cout << "\t请输入课程id: " << flush ;
            cin >> LesId ;
            while(LesId <= 0 && fi.lessdbf.ReadRecord(LesId-1) != 1)
            {
                cout << "\t输入课程id不正确,请重新输入: " << flush ;
                cin >> LesId ;
            }
            
            p = fi.stuSelect[StuId-1].Find(LesId-1) ;
            if (p != NULL)
            {
                int offset = p->GetOffset() ;
                char LessName[49] = {0};
                fi.lessdbf.ReadItem("name", LessName) ;
                SkipSpace(LessName, 48) ;
                
                cout << "\t确定要删除" << LessName << " 吗? Y/N :" << flush ;
                cin >> state ;

                if (state == 'n' || state == 'N')
                {
                    break;
                }

                if (fi.stuSlectdbf.DeleteRecord(offset) == 1)
                {
                    fi.stuSelect[StuId-1].Delete(LesId - 1) ;
                    fi.stuLesSelect[LesId-1].Delete(StuId - 1) ;
                    cout << "\t删除成功" << endl ;
                }
                else
                {
                    cout << "\t删除成功失败" << endl ;
                }
            }
            else
            {
                cout << "\t对不起，该生没有选修这门课程" << endl ;
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
*  函 数 名 : TeaSelManageProc
*  功能描述 : 老师任课管理主函数
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请正确选择" << endl ;
        }
        TeaSelManageMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : TeaSelSelectProc
*  功能描述 : 查询老师任课
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入要查询教师的工号: " << flush ;
            cin >> id ;
        } // end of if
        else if (n == 2)
        {
            memset(szName, 0, 48) ;
            cout << "\t请入要查询教师的姓名: " << flush ;
            SafeInput(szName, 48) ;
            SkipSpace(szName, 48) ;
            MyList * pNameList = NULL ;
            pNameList = fi.teaNameIndex.Find(szName) ;
            if (pNameList == NULL)
            {
                cout << "\t找不到这个教师" << endl ;
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
                cout << "\t请再输入您要查询教师的工号: " << flush ;
                cin >> id ;
                if (id <= 0)
                {
                    cout << "\t不要徒劳寻找系统漏洞" << endl ;
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
                    cout << "\t对不起，找不到此教师" << endl ;
                    //getchar() ;
                }
                else if (nSize == 0)
                {
                    cout << "\t对不起，此教师还没有选课" << endl ;
                }
                else
                {
                    DisplayTeacherTitle() ;
                    cout << fi.teadbf << endl << endl;
                    cout << "\t该教师共任" << setw(2) << nSize << "门课程" << endl ;
                    cout << endl << "\t任课列表" << endl ;
                    DisplayTeaSelTitle() ;
                    for (i = 0; i < nSize; ++i)
                    {
                        // 读出课程信息
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
            cout << "\t不要试图寻找系统的漏洞" << endl ;
        }
        fflush(stdin) ;
        getchar() ;
        SelectTeaMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : TeaSelAddProc
*  功能描述 : 增加老师任课
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入要任课教师的id: " << flush ;
            cin >> TeaId ;
            while (TeaId < 1  && fi.teadbf.ReadRecord(TeaId - 1) != 1)
            {
                cout << "\tid不正确,请重新输入" << endl ;
                cin >> TeaId ;
            }
            
            memset(buf, 0, 16) ;
            sprintf(buf, "%10d", TeaId) ;
            fi.teaSelectdbf.SetString("TeaId", buf) ;
            
            cout << "\t请输入要任的课程ID: " << flush ;
            cin >> LesId ;
            while(LesId < 1  && fi.lessdbf.ReadRecord(LesId - 1) != 1)
            {
                cout << "\t课程id不正确,请重新输入" << endl ;
                cin >> LesId ;
            }
            memset(buf, 0, 16) ;
            sprintf(buf, "%10d", LesId) ;
            fi.teaSelectdbf.SetString("LesId", buf) ;
            
            memset(buf, 0, 16) ;
            if (fi.teaSelect[TeaId-1].Find(LesId-1) == NULL)
            {
                offset = fi.teaSelectdbf.AddRecord() ;
                // 更新索引
                fi.teaLesSelect[LesId-1].Push(TeaId-1, offset) ;
                fi.teaSelect[TeaId-1].Push(LesId-1, offset) ;
                cout << "\t添加成功" << endl ;
            }
            else
            {
                cout << "\t添加失败，已经存在" << endl ;
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
*  函 数 名 : TeaSelShowProc
*  功能描述 : 显示所有老师任课
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入查询课程ID: " << flush ;
            cin >> LesId ;
            while(fi.lessdbf.ReadRecord(LesId-1) != 1)
            {
                cout << "\t课程号不正确，请重新输入: " << flush ;
                cin >> LesId ;
            }
        }
        else if (n == 2)
        {
            char buf[48] = {0} ;
            MyList * pLes = NULL ;
            cout << "\t请输入要查询课程名: " << flush ;
            SafeInput(buf, 48) ;
            SkipSpace(buf,48) ;
            
            if ((pLes = fi.lessonNameIndex.Find(buf) )== NULL)
            {
                cout << "\t课程名不正确，请重新输入: " << flush ;
                SafeInput(buf, 48) ; 
                SkipSpace(buf, 48) ;
            }

            //取出id
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
            cout << "\t请输入查询课程ID: " << flush ;
            cin >> LesId ;
            while(fi.lessdbf.ReadRecord(LesId-1) != 1)
            {
                cout << "\t课程号不正确，请重新输入: " << flush ;
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
                cout << "\t教这门课的教共有 " << setw(2) << nSize << flush;
                cout << "位" << endl ;
                // 输出各个选课学生的姓名和学号
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
                cout << "\t对不起，这门课程没有老师任课" << endl ;
            }
        }

        if (n != 1 && n != 2)
        {
            cout << "\t请输入正确选项" << endl ;
        }

        fflush(stdin) ;
        getchar() ;
        SelectLessMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : TeaSelModifiProc
*  功能描述 : 修改老师任课信息
*  参数列表 : fi    --   文件索引
*  说    明 :  因没有别的附加信息要修改，所以这里留空
*  返回结果 : 
*
*******************************************************************************/
void TeaSelModifiProc(FileIndex & fi)
{
    cout << "\t功能待定" << endl ;
    getchar() ;
}

/*******************************************************************************
*
*  函 数 名 : TeaSelDeleteProc
*  功能描述 : 删除老师任课信息
*  参数列表 : fi    --   文件索引
*  说    明 : 无
*  返回结果 : 无
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
            cout << "\t请输入教师工号: " << flush ;
            cin >> TeaId ;
            while(TeaId <= 0 && fi.teadbf.ReadRecord(TeaId-1) != 1)
            {
                cout << "\t输入教师工号不正确,请重新输入: " << flush ;
                cin >> TeaId ;
            }
            
            int i(0) ,
                nSize(fi.teaSelect[TeaId-1].GetSize()) ;
            if (nSize > 0)
            {
                cout << "\t该教师共任课"<< nSize << "门课" << flush ;
                cout << "选课列表如下:(只显示课程id)" << endl ;
            }
            else
            {
                cout << "\t该教师没有任课" << endl ;
            }
            cout << "\t" << flush;
            for (; i < nSize ; ++i)
            {
                cout << fi.teaSelect[TeaId-1][i]->data + 1 << " " ;
            }
            cout << endl ;
            
            cout << "\t请输入课程id: " << flush ;
            cin >> LesId ;
            while(LesId <= 0 && fi.lessdbf.ReadRecord(LesId-1) != 1)
            {
                cout << "\t输入课程id不正确,请重新输入: " << flush ;
                cin >> LesId ;
            }
            p = fi.teaSelect[TeaId-1].Find(LesId-1) ;
            if (p != NULL)
            {
                int offset = p->GetOffset() ;
                char LessName[49] = {0};
                fi.lessdbf.ReadItem("name", LessName) ;
                SkipSpace(LessName, 48) ;
                
                cout << "\t确定要删除" << LessName << " 吗? Y/N :" << flush ;
                cin >> state ;
                
                if (state == 'n' || state == 'N')
                {
                    break;
                }
                
                if (fi.teaSelectdbf.DeleteRecord(offset) == 1)
                {
                    fi.teaSelect[TeaId-1].Delete(LesId - 1) ;
                    fi.teaLesSelect[LesId-1].Delete(TeaId - 1) ;
                    cout << "\t删除成功" << endl ;
                }
                else
                {
                    cout << "\t删除成功失败" << endl ;
                }
            }
            else
            {
                cout << "\t对不起，该生没有选修这门课程" << endl ;
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
*  函 数 名 : LessonManageProc
*  功能描述 : 课程管理主函数
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请正确选择" << endl ;
        }
        LesManageMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : LessonSelectProc
*  功能描述 : 查询课程信息
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
        // 按课程号查询
        if (n == 1)
        {
            cout << "\t请输入要查询课程的课程号:" << flush ;
            cin >> nSelect ;
            fflush(stdin) ;
            if (fi.lessdbf.ReadRecord(nSelect - 1) == 1)
            {
                cout << fi.lessdbf << endl ;
            }
            else
            {
                cout << "\t对不起，查不到该课程" << endl ;
            }
        }
        // 按姓名查询
        else if (n == 2)
        {
            memset(buf, 0, 56) ;
            cout << "\t请输入要查询课程名:" << flush ;
            SafeInput(buf, 48) ;
            SkipSpace(buf, 48) ;
            pList = fi.lessonNameIndex.Find(buf) ;
            if (pList == NULL)
            {
                cout << "\t对不起，查不到该课程" << endl ;
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
*  函 数 名 : LessonAddProc
*  功能描述 : 增加课程信息
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入要添加的课程名: " << flush ;
            // 名字最大长度为32
            SafeInput(szName, 48) ;
            SkipSpace(szName, 48) ;
            fi.lessdbf.SetString("name", szName) ;
            
            cout << "\t请输入要添加课程的学分数: " << flush ;
            SafeInput(buf, 2) ;
            SkipSpace(buf, 2) ;
            fi.lessdbf.SetString("mark", buf) ;
            
            cout << "\t请输入要添加课程的学时数: " << flush ;
            SafeInput(buf, 4) ;
            SkipSpace(buf, 4) ;
            fi.lessdbf.SetString("period", buf) ;
            
            nIndex = fi.lessdbf.AddRecord() ;
            
            // 往索引树里添加信息
            if( fi.lessonNameIndex.Insert(szName, nIndex) == 1)
            {
                cout << "\t添加成功" << endl ;
            }
            else
            {
                cout << "\t添加失败" << endl ;
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
*  函 数 名 : LessonShowProc
*  功能描述 : 显示课程信息
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
*
*******************************************************************************/
void LessonShowProc(FileIndex & fi) 
{
    int i(0) ,
        state(0) ;
    system("cls") ;
    cout << "\t课程信息列表:" << endl ;
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
*  函 数 名 : LessonModifiProc
*  功能描述 : 修改课程信息
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入你要修改课程的ID: " << flush ;
            cin >> nIndex ;
            fflush(stdin) ;
            nIndex -= 1 ;
            while ( fi.lessdbf.ReadRecord(nIndex) != 1)
            {
                cout << "\t输入的课程ID不对，请重新输入: " << flush ;
                cin >> nIndex ;
            }
            cout << "\t您确认要修改以下课程的信息 ?" << endl;
            cout << fi.lessdbf << endl ;
            cout << "\t请选择: Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'N' || State == 'n')
            {
                break ;
            }
            cout << "\t您要修改课程名吗? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'y')
            {
                memset(buf, 0, 56) ;
                fi.lessdbf.ReadItem("name", szName) ;
                SkipSpace(szName, 48) ;
                cout << "\t请输入新课程名: " << flush ;
                SafeInput(buf, 48) ;
                SkipSpace(buf, 48) ;
                // 如果现在输入的，和原来的不同，就更新索引
                if (stricmp(buf, szName) != 0)
                {
                    fi.lessdbf.SetString("name", buf) ;
                    fi.lessonNameIndex.Remove(szName, nIndex) ;
                    fi.lessonNameIndex.Insert(buf, nIndex) ;
                }                
            }

            cout << "\t您要修改课程的学分吗? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'N')
            {
                memset(buf, 0, 4) ;
                cout << "\t请输入新的学分数: " << flush ;
                SafeInput(buf, 2) ;
                fi.lessdbf.SetString("mark", buf) ;
            }

            cout << "\t您要修改课程的学时吗? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'N')
            {
                memset(buf, 0, 8) ;
                cout << "\t请输入新的学时数: " << flush ;
                SafeInput(buf, 4) ;
                fi.lessdbf.SetString("period", buf) ;
            }
            
            if (fi.lessdbf.SaveRecord(nIndex) == 1)
            {
                cout << "修改成功" << endl ;
            }
            else
            {
                cout << "修改失败" << endl ;
            }
        }// end of if
        ModifiLesMenu();
        fflush(stdin) ;
    } //enf of while
}

/*******************************************************************************
*
*  函 数 名 : LessonDeleteProc
*  功能描述 : 删除课程信息
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            
            cout << "\t请输入要删除课程的课程号 : " << flush ;
            cin >> nIndex ;
            nIndex -= 1 ;
            fflush(stdin) ;
            State = fi.lessdbf.ReadRecord(nIndex) ;
            while (State == 0)
            {
                cout << "\t请重新输入课程号: " << flush ;
                cin >> nIndex ;
                nIndex -= 1 ;
                State = fi.lessdbf.ReadRecord(nIndex) ;
            }
            if (State == -1)
            {
                return  ;
            }

            cout << fi.studbf << endl ;
            cout << "\t您确认要删除此课程信息: Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'y' || State == 'Y')
            {
                fi.lessdbf.ReadItem("name", szName) ;
                SkipSpace(szName, 64) ;
                if (fi.lessdbf.DeleteRecord(nIndex) == 1)
                {
                    // 依次删除学生在选课表里的索引与文件里的记录
                    unsigned int  nStuId(0)  , // 学生Id
                        nTeaId(0) ,
                        nLesId(nIndex)  , // 课程Id
                        nOffset(0) , // 文件偏移
                        i(0) ,
                        nCount( fi.stuLesSelect[nLesId].GetSize()) ;
                    // 先删除选了这门课的学生记录
                    for (; i < nCount; ++i)
                    {
                        // 弹出文件偏移
                        nOffset = fi.stuLesSelect[nLesId][i]->GetOffset() ;
                        nStuId = fi.stuLesSelect[nLesId][i]->GetData() ;
                        // delete student select lesson record from dbf
                        fi.stuSlectdbf.DeleteRecord(nOffset) ;
                        fi.stuLesSelect[nLesId].Delete(nStuId) ;
                        fi.stuSelect[nStuId].Delete(nLesId) ;
                    }
                    nCount = fi.teaLesSelect[nLesId].GetSize() ;    
                    // 先删除选了这门课的老师记录
                    for (i = 0; i < nCount; ++i)
                    {
                        // 弹出文件偏移
                        nOffset = fi.teaLesSelect[nLesId][i]->GetOffset() ;
                        nTeaId = fi.teaLesSelect[nLesId][i]->GetData() ;
                        // delete student select lesson record from dbf
                        fi.teaSelectdbf.DeleteRecord(nOffset) ;
                        fi.teaLesSelect[nLesId].Delete(nTeaId) ;
                        fi.teaSelect[nTeaId].Delete(nLesId) ;
                    }
                    // 最后再将这门课从课程名索引里面删除
                    fi.lessonNameIndex.Remove(szName, nIndex) ;
                    cout << "\t删除成功" << endl ;
                } // end of if (fi.lessdbf.DeleteRecord(nIndex) == 1)
                else
                {
                    cout << "\t删除失败" << endl ;
                }
            }
        }// end of if (State == 'y' || State == 'Y')
        else
        {
            cout << "\t请正确选择" << endl ;
        }
        getchar() ;
        DeleteLesMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : TeacherManageProc
*  功能描述 : 老师信息主函数
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请正确选择" << endl ;
        }
        TeaManageMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : TeacherSelectProc
*  功能描述 : 处理查询教师信息
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
        // 按学号查询
        if (n == 1)
        {
            cout << "\t请输入要查询老师的工号:" << flush ;
            cin >> nSelect ;
            fflush(stdin) ;
            if (fi.teadbf.ReadRecord(nSelect - 1) == 1)
            {
                cout << fi.teadbf << endl ;
            }
            else
            {
                cout << "\t对不起，查不到该老师" << endl ;
            }
        }
        // 按姓名查询
        else if (n == 2)
        {
            memset(buf, 0, 64) ;
            cout << "\t请输入要查询老师的姓名:" << flush ;
            SafeInput(buf, 64) ;
            SkipSpace(buf, 64) ;
            pList = fi.teaNameIndex.Find(buf) ;
            if (pList == NULL)
            {
                cout << "\t对不起，查不到该老师" << endl ;
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
*  函 数 名 : TeacherAddProc
*  功能描述 : 处理添加老师信息
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入要添加老师的名字: " << flush ;
            // 名字最大长度为32
            SafeInput(szName, 32) ;
            SkipSpace(szName, 32) ;
            fi.teadbf.SetString("name", szName) ;
            
            cout << "\t请输入要添加老师的性别: " << flush ;
            SafeInput(buf, 2) ;
            SkipSpace(buf, 2) ;
            fi.teadbf.SetString("sex", buf) ;
            
            cout << "\t请输入要添加老师的出生日期: 格式:年-月-日: " << flush ;
            scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
            while(isSuccDate(d) == 0)
            {
                cout << "\t请输入要添加老师的出生日期: 格式:年-月-日: " << flush ;
                scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
            }
            memset(buf, 0, 64) ;
            sprintf(buf, "%d%d%d", d.year, d.month, d.day) ;
            fi.teadbf.SetString("birthday", buf) ;
            
            memset(buf, 0, 64 ) ;
            cout << "\t请输入要添加老师的电话: " << flush ;
            SafeInput(buf, 18) ;
            while(isSuccPhoto(buf) == 0)
            {
                cout << "请输入要添加老师的电话: " << flush ;
                SafeInput(buf, 18) ;
            }
            fi.teadbf.SetString("telephone", buf) ;
            nIndex = fi.teadbf.AddRecord() ;
            
            // 往索引树里添加信息
            if (fi.teaNameIndex.Insert(szName, nIndex) == 1)
            {
                cout << "\t添加成功" << endl ;
            }
            else
            {
                cout << "\t添加失败" << endl ;
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
*  函 数 名 : TeacherShowProc
*  功能描述 : 显示所有老师信息
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
*
*******************************************************************************/
void TeacherShowProc(FileIndex & fi)
{
    int i(0) ,
        state(0) ;
    system("cls") ;
    cout << "\t老师信息列表:" << endl ;
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
*  函 数 名 : TeacherModifiProc
*  功能描述 : 修改老师信息
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入你要修改老师的ID: " << flush ;
            cin >> nIndex ;
            fflush(stdin) ;
            nIndex -= 1 ;
            while ( fi.teadbf.ReadRecord(nIndex) != 1)
            {
                cout << "\t输入的老师ID不对，请重新输入: " << flush ;
                cin >> nIndex ;
            }
            cout << "\t您确认要修改以下老师的信息 ?" << endl;
            cout << fi.teadbf << endl ;
            cout << "\t请选择: Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'N' || State == 'n')
            {
                break ;
            }
            cout << "\t您要修改姓名吗? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'y')
            {
                memset(buf, 0, 32) ;
                fi.teadbf.ReadItem("name", szName) ;
                SkipSpace(szName, 32) ;
                cout << "\t请输入用户新名字: " << flush ;
                SafeInput(buf, 32) ;
                SkipSpace(buf, 32) ;
                // 如果现在输入的，和原来的不同，就更新索引
                if (stricmp(buf, szName) != 0)
                {
                    fi.teadbf.SetString("name", buf) ;
                    fi.teaNameIndex.Remove(szName, nIndex) ;
                    fi.teaNameIndex.Insert(buf, nIndex) ;
                }                
            }
            cout << "\t您要修改老师的性别吗? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'N')
            {
                memset(buf, 0, 32) ;
                cout << "\t请输入老师变性后的性别: " << flush ;
                SafeInput(buf, 2) ;
                fi.teadbf.SetString("sex", buf) ;
            }
            
            cout << "\t您要修改老师的生日吗? Y/N :" << flush ;
            cin >> State ;
            if (State == 'Y' || State == 'y') 
            {
                date d ;
                fflush(stdin) ;
                cout << "\t请输入老师新的出生日期: 年-月-日: " << flush ;
                scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
                fflush(stdin) ;
                while(isSuccDate(d) == 0)
                {
                    cout << "请输入老师的出生日期: 格式:年-月-日: " << flush ;
                    scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
                    fflush(stdin) ;
                }
                memset(buf, 0, 32) ;
                sprintf(buf, "%d%d%d", d.year, d.month, d.day) ;
                fi.teadbf.SetString("birthday", buf) ;
            }
            
            cout << "\t您要修改老师的电话号码吗? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if(State == 'Y' || State == 'y')
            {
                memset(buf, 0 , 32) ;
                cout << "\t请输入要修改老师的电话: " << flush ;
                SafeInput(buf, 18) ;
                while(isSuccPhoto(buf) == 0)
                {
                    cout << "\t请输入要修改老师的电话: " << flush ;
                    SafeInput(buf, 18) ;
                    fflush(stdin) ;
                }
                fi.teadbf.SetString("telephone", buf) ;
            }
            if (fi.teadbf.SaveRecord(nIndex) == 1)
            {
                cout << "修改成功" << endl ;
            }
            else
            {
                cout << "修改失败" << endl ;
            }
        }// end of if
        ModifiTeaMenu();
        fflush(stdin) ;
    } //enf of while
}

/*******************************************************************************
*
*  函 数 名 : TeacherDeleteProc
*  功能描述 : 删除老师信息
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            
            cout << "\t请输入要删除老师ID : " << flush ;
            cin >> nIndex ;
            nIndex -= 1 ;
            fflush(stdin) ;
            fi.teadbf.ReadRecord(nIndex) ;
            cout << fi.teadbf << endl ;
            cout << "\t您确认要删除此老师信息: Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'y' || State == 'Y')
            {
                fi.teadbf.ReadItem("name", szName) ;
                SkipSpace(szName, 64) ;
                if (fi.teadbf.DeleteRecord(nIndex) == 1)
                {
                    // 依次删除教师在选课表里的索引与文件里的记录
                    unsigned int  nTeaId(nIndex)  , // 教师Id
                                  nLesId(0)  ,        // 课程Id
                                  nOffset(0) ,        // 文件偏移
                                  i(0) ,
                                  nCount( fi.teaSelect[nTeaId].GetSize()) ;
                    // 依次删除教师选课表里的信息
                    for (; i < nCount; ++i)
                    {
                        // 取得当前选课的文件偏移
                        nOffset = fi.teaSelect[nTeaId][i]->GetOffset() ;
                        // delete record of teacher select lesson from dbf
                        fi.teaSelectdbf.DeleteRecord(nOffset) ;
                        // 从以课程号为索引的索引记录中删除教师
                        fi.teaLesSelect[nLesId].Delete(nTeaId) ;
                    }
                    // 清空该教师所有的选课记录
                    fi.teaSelect[nTeaId].Clear() ;
                    // 删除教师姓名的索引
                    fi.teaNameIndex.Remove(szName, nIndex) ;
                    cout << "\t删除成功" << endl ;
                } // end of if (fi.teadbf.DeleteRecord(nIndex) == 1)
                else
                {
                    cout << "\t删除失败" << endl ;
                }
            }
        }
        else
        {
            cout << "\t请正确选择" << endl ;
        }
        getchar() ;
        DeleteTeaMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : StudentManageProc
*  功能描述 : 学生管理主函数
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请正确选择" << endl ;
            break ;
        }
        StuManageMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : StudentSelectProc
*  功能描述 : 处理学生查询
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
        // 按学号查询
        if (n == 1)
        {
            cout << "\t请输入要查询学生的学号:" << flush ;
            cin >> nSelect ;
            fflush(stdin) ;
            if (fi.studbf.ReadRecord(nSelect - 1) == 1)
            {
                cout << fi.studbf << endl ;
            }
            else
            {
                cout << "\t对不起，查不到该学生" << endl ;
            }
        }
        // 按姓名查询
        else if (n == 2)
        {
            memset(buf, 0, 64) ;
            cout << "\t请输入要查询学生的姓名:" << flush ;
            SafeInput(buf, 64) ;
            SkipSpace(buf, 64) ;
            pList = fi.stuNameIndex.Find(buf) ;
            if (pList == NULL)
            {
                cout << "\t对不起，查不到该学生" << endl ;
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
*  函 数 名 : StudentAddProc
*  功能描述 : 处理添加学生
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入要添加学生的名字: " << flush ;
            // 名字最大长度为32
            SafeInput(szName, 32) ;
            SkipSpace(szName, 32) ;
            fi.studbf.SetString("name", szName) ;

            cout << "\t请输入要添加学生的性别: " << flush ;
            SafeInput(buf, 2) ;
            SkipSpace(buf, 2) ;
            fi.studbf.SetString("sex", buf) ;

            cout << "\t请输入学生的出生日期: 格式:年-月-日: " << flush ;
            scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
            while(isSuccDate(d) == 0)
            {
                cout << "\t请输入学生的出生日期: 格式:年-月-日: " << flush ;
                scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
            }

            memset(buf, 0, 64) ;
            sprintf(buf, "%d%d%d", d.year, d.month, d.day) ;
            fi.studbf.SetString("birthday", buf) ;

            memset(buf, 0, 64 ) ;
            cout << "\t请输入要添加学生的电话: " << flush ;
            SafeInput(buf, 18) ;
            while(isSuccPhoto(buf) == 0)
            {
                cout << "请输入要添加学生的电话: " << flush ;
                SafeInput(buf, 18) ;
            }
            fi.studbf.SetString("telephone", buf) ;
            nIndex = fi.studbf.AddRecord() ;

            // 往索引树里添加信息
            if (fi.stuNameIndex.Insert(szName, nIndex) == 1)
            {
                cout << "\t添加成功" << endl ;
            }
            else
            {
                cout << "\t添加失败" << endl ;
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
*  函 数 名 : StudentShowProc
*  功能描述 : 显示所有的学生
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
*
*******************************************************************************/
void StudentShowProc(FileIndex & fi)
{
    int i(0) ,
        state(0) ;
    system("cls") ;
    cout << "\t学生信息列表:" << endl ;
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
*  函 数 名 : StudentModifiProc
*  功能描述 : 修改学生信息
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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
            cout << "\t请输入你要修改学生的ID: " << flush ;
            cin >> nIndex ;
            fflush(stdin) ;
            nIndex -= 1 ;
            while ( fi.studbf.ReadRecord(nIndex) != 1)
            {
                cout << "\t输入的学生ID不对，请重新输入: " << flush ;
                cin >> nIndex ;
                nIndex -= 1 ;
            }
            cout << "\t您确认要修改以下学生的信息 ?" << endl;
            cout << fi.studbf << endl ;
            cout << "\t请选择: Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'N' || State == 'n')
            {
                break ;
            }
            cout << "\t您要修改姓名吗? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'y')
            {
                memset(buf, 0, 32) ;
                fi.studbf.ReadItem("name", szName) ;
                SkipSpace(szName, 32) ;
                cout << "\t请输入用户新名字: " << flush ;
                SafeInput(buf, 32) ;
                SkipSpace(buf, 32) ;
                // 如果现在输入的，和原来的不同，就更新索引
                if (stricmp(buf, szName) != 0)
                {
                    fi.studbf.SetString("name", buf) ;
                    fi.stuNameIndex.Remove(szName, nIndex) ;
                    fi.stuNameIndex.Insert(buf, nIndex) ;
                }                
            }
            cout << "\t您要修改学生的性别吗? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'Y' || State == 'N')
            {
                memset(buf, 0, 32) ;
                cout << "\t请输入同学变性后的性别: " << flush ;
                SafeInput(buf, 2) ;
                fi.studbf.SetString("sex", buf) ;
            }

            cout << "\t您要修改学生的生日吗? Y/N :" << flush ;
            cin >> State ;
            if (State == 'Y' || State == 'y') 
            {
                date d ;
                fflush(stdin) ;
                cout << "\t请输入学生新的出生日期: 年-月-日: " << flush ;
                scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
                fflush(stdin) ;
                while(isSuccDate(d) == 0)
                {
                    cout << "请输入学生的出生日期: 格式:年-月-日: " << flush ;
                    scanf("%d-%d-%d", &d.year, &d.month, &d.day) ;
                    fflush(stdin) ;
                }
                memset(buf, 0, 32) ;
                sprintf(buf, "%d%d%d", d.year, d.month, d.day) ;
                fi.studbf.SetString("birthday", buf) ;
            }

            cout << "\t您要修改学生的电话号码吗? Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if(State == 'Y' || State == 'y')
            {
                memset(buf, 0 , 32) ;
                cout << "\t请输入要修改学生的电话: " << flush ;
                SafeInput(buf, 18) ;
                while(isSuccPhoto(buf) == 0)
                {
                    cout << "\t请输入要修改学生的电话: " << flush ;
                    SafeInput(buf, 18) ;
                    fflush(stdin) ;
                }
                fi.studbf.SetString("telephone", buf) ;
            }
            if( fi.studbf.SaveRecord(nIndex) == 1)
            {
                cout << "修改成功" << endl ;
            }
            else
            {
                cout << "修改失败" << endl ;
            }
        }// end of if
        ModifiStuMenu();
        fflush(stdin) ;
    } //enf of while
}

/*******************************************************************************
*
*  函 数 名 : StudentDeleteProc
*  功能描述 : 删除学生信息
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 
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

            cout << "\t请输入要删除学生ID : " << flush ;
            cin >> nIndex ;
            nIndex -= 1 ;
            fflush(stdin) ;
            fi.studbf.ReadRecord(nIndex) ;
            cout << fi.studbf << endl ;
            cout << "\t您确认要删除此学生信息: Y/N: " << flush ;
            cin >> State ;
            fflush(stdin) ;
            if (State == 'y' || State == 'Y')
            {
                fi.studbf.ReadItem("name", szName) ;
                SkipSpace(szName, 64) ;
				// 如果从记录里面删除成功的话
                if (fi.studbf.DeleteRecord(nIndex) == 1)
                {
                    cout << "\t删除成功" << endl ;
                    // 删除学生姓名的索引
                    fi.stuNameIndex.Remove(szName, nIndex) ;
                    // 依次删除学生在选课表里的索引与文件里的记录
                    unsigned int  nStuId(nIndex)  , // 学生Id
                         nLesId(0)  , // 课程Id
                         nOffset(0) , // 文件偏移
                         i(0) ,
                         nCount( fi.stuSelect[nStuId].GetSize()) ;
                    for (; i < nCount; ++i)
                    {
                        // 弹出文件偏移
                        nOffset = fi.stuSelect[nStuId][i]->GetOffset() ;
                        nLesId = fi.stuSelect[nStuId][i]->GetData()    ;
                        // 删除学生选课数据文件的选课记录
                        fi.stuSlectdbf.DeleteRecord(nOffset) ;
                        // 从以课程为主键的索引表中删除学生的选课
                        fi.stuLesSelect[nLesId].Delete(nStuId) ;
                    }
                    // 将学生选课列表清空
                    fi.stuSelect[nStuId].Clear() ;
                }
                else
                {
                    cout << "\t删除失败" << endl ;
                }
            }
        }
        else
        {
            cout << "\t请正确选择" << endl ;
        }
        getchar() ;
        DeleteStuMenu() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : SelectStudentName
*  功能描述 : 按学生姓名查找
*  参数列表 : fi    --   文件索引
*  说    明 : 
*  返回结果 : 如果查找成功，返回 1,否则返回 0
*
*******************************************************************************/
int SelectStudentName(FileIndex & fi)
{
    int nSize(0),
        i(0),
        nOffset(0) ;
    char buf[64] = {0} ;
    MyList *pList ;
    cout << "\t请输入要查询学生的姓名:" << flush ;
    SafeInput(buf, 64) ;
    SkipSpace(buf, 64) ;
    pList = fi.stuNameIndex.Find(buf) ;
    if (pList == NULL)
    {
        cout << "\t对不起，查不到该学生" << endl ;
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
*  函 数 名 : SelectLesName
*  功能描述 : 通过课程名查找课程
*  参数列表 : fi -- 文件索引类

*  说    明 : 如果不想继续找，输入 0结束
*  返回结果 : 如果成功返回 1,否则返回 0
*
*******************************************************************************/
int SelectLesName(FileIndex & fi)
{
    char szName[48] = {0} ;
    char buf[48] = {0} ;
    MyList * pLes = NULL ;
    cout << "\t请输入要查询课程名: " << flush ;
    SafeInput(buf, 48) ;
    SkipSpace(buf,48) ;
    
    while ((pLes = fi.lessonNameIndex.Find(buf) )== NULL)
    {
        cout << "\t课程名不正确，请重新输入: " << flush ;
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
    
    //取出id
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
