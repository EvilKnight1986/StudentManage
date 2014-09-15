#include "FileIndex.h"
#pragma warning(disable:4996)

static char surnamed[50][3] = {
"黄", "王", "赵", "方", "周", "李", "颜", "吴", "郑", "向",
"郭", "秦", "孟", "江", "胡", "张", "肖", "马", "刘", "陈",
"赖", "晏", "梁", "罗", "杨", "崔", "曹", "冯", "汪", "蔡",
"袁", "卢", "唐", "钱", "杜", "彭", "陆", "廖", "习", "余",
"孙", "朱", "马", "狗", "唐", "谢", "邓", "白", "包", "彭"
};

static char mind[20][3] = {
"贺", "武", "康", "夫", "清", "泉", "邱", "伟", "兄", "史",
"段", "天", "月", "水", "火", "炎", "磊", "焱", "多", "少"
};

static char name[120][3] = {
"飞", "佳", "杰", "嘉", "伟", "碧", "凤", "俊", "师", "达",
"依", "琳", "晓" ,"兴", "淋", "毅", "强", "国", "肛", "钢",
"猛", "林", "松", "慧", "志", "本", "山", "水", "田", "春",
"宇", "镇", "奥", "彬", "超", "年", "忠", "青", "红", "斯",
"特", "雄", "昊", "斯", "雅", "飞", "朋", "文", "军", "育",
"凡", "桌", "辉", "灰", "健", "宝", "东", "才", "勇", "苏",
"维", "荣", "新", "阳", "胜", "宜", "启", "明", "楼", "天",
"成", "亮", "思", "名", "铭", "振", "南", "浩", "乐", "杰",
"路", "艺", "敏", "程", "婷", "诗", "智", "彦", "秀", "萍",
"泽", "广", "斌", "礼", "峰", "锋", "子", "成", "乐", "博",
"鸿", "聪", "导", "艳", "燕", "芳", "贵", "宝", "航", "志",
"烦", "球", "猪" ,"头", "天", "向", "上", "精", "神", "好"
};

/*******************************************************************************
*
*  函 数 名 : AddData
*  功能描述 : 添加学生，老师、学生选课，老师任课测试数据
*  参数列表 : fi	--		文件索引
*  说    明 : 无添加课程信息
*  返回结果 : 无
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

    // 添加学生
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

    // 添加老师
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

    // 添加选课
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

    // 添加任课
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