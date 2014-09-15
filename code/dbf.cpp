// .cpp: implementation of the  class.
//
//////////////////////////////////////////////////////////////////////

#include "dbf.h"
#include <io.h>

const char Suffix[] = ".free";
const int  SuffixSize =  sizeof(Suffix);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#if _MSC_VER >= 1400 
#pragma warning(disable:4996)
#endif

/*******************************************************************************
*
*  函 数 名 : dbf
*  功能描述 : 构造函数
*  参数列表 : 
*  说    明 : 无
*  返回结果 : 无
*
*******************************************************************************/
dbf::dbf():wfp(NULL),rfp(NULL),pFileName(NULL),pHead(NULL),pField(NULL),\
                  pBuf(NULL),nState(0),nFieldCount(0),pFreeIndexName(NULL)
{
    ReadIndex() ;
}

/*******************************************************************************
*
*  函 数 名 : dbf
*  功能描述 : 构造函数
*  参数列表 : FileName	--	dbf文件名
*  说    明 : 通过GetState()得状态，
*  返回结果 : 无
*
*******************************************************************************/
dbf::dbf(const char *FileName):wfp(NULL),rfp(NULL),pFileName(NULL),pHead(NULL),\
          pField(NULL),pBuf(NULL),nState(0),nFieldCount(0),pFreeIndexName(NULL)
{
    int len((int)strlen(FileName) + sizeof(char)) ;
    // 初始化二个指针，分别用来读、更新数据和添加数据
    wfp = fopen(FileName, "a+b") ;
    rfp = fopen(FileName, "r+b") ;

    if (wfp != NULL && rfp != NULL)
    {
        // 为pFileName 申请空间，存放文件名
        pFileName = new char[len] ;
        if (pFileName != NULL)
        {
            memset(pFileName, 0, len) ;
            strcpy(pFileName, FileName) ;
        }

        // 空闲空间索引文件名
        pFreeIndexName = new char[len + SuffixSize] ;
        if (pFreeIndexName != NULL)
        {
            memset(pFreeIndexName, 0, len + SuffixSize) ;
            strcpy(pFreeIndexName, FileName) ;
            strcat(pFreeIndexName, Suffix) ;
        }

        // 为pHead申请空间,存放文件头
        pHead = new DBFHead ;
        if (pHead != NULL)
        {
            memset(pHead, 0, sizeof(DBFHead)) ;
            ReadHead();
        }
    }
    nState = 1 ;

    // 读已删除空间索引
    ReadIndex() ;
}

/*******************************************************************************
*
*  函 数 名 : ~dbf
*  功能描述 : 析构函数
*  参数列表 : 
*  说    明 : 释放资源，同时将索引写入文件
*  返回结果 : 
*
*******************************************************************************/
dbf::~dbf()
{
    if (wfp != NULL && rfp != NULL)
    {
        fseek(rfp, -1, SEEK_END ) ;
        if(fgetc(rfp) != 0x1a)
        {
            //char end = InforEnd ;
            // 写入结束标志
            char end = 0x1A; 
            fseek(wfp,0, SEEK_END) ;
            fwrite(&end, sizeof(char), 1, wfp);
            fflush(rfp) ;
            fflush(wfp) ;
        }
        fclose(wfp);
        wfp = NULL ;
    }

    // 将索引写入文件
    WriteIndex() ;

    // 以下是分别是关闭文件与释放内存空间
    if (rfp != NULL)
    {
        fclose(rfp) ;
        rfp = NULL ;
    }
    
    if (pFreeIndexName != NULL)
    {
        delete [] pFreeIndexName ;
        pFreeIndexName = NULL ;
    }

    if (pHead != NULL)
    {
        delete pHead ;
        pHead = NULL ;
    }

    if (pField != NULL)
    {

        delete [] pField ;
        pField = NULL ;
    }

    if (pBuf != NULL)
    {
        delete [] pBuf ;
        pBuf = NULL ;
    }
    cout << "保存" << pFileName << "空闲表成功" << endl ;
    if (pFileName != NULL)
    {
        delete [] pFileName ;
        pFileName = NULL ;
    }
}


/*******************************************************************************
*
*  函 数 名 : ReadHead
*  功能描述 : 读头信息
*  参数列表 : 
*  说    明 : 
*  返回结果 : 读取头信息，如果失败，返回0,否则返回1
*
*******************************************************************************/
int dbf::ReadHead(void)
{
    if (rfp == NULL)
    {
        return 0 ;
    }

    // 重新将文件指针定位到文件尾
    fseek(rfp, -1, SEEK_END);

    if (pHead == NULL)
    {
        pHead = new DBFHead ;
        if (pHead == NULL)
        {
            return 0 ;
        }
        memset(pHead, 0, sizeof(DBFHead)) ;        
    }

	// 如果文件长度小于32字节，说明不是一个完整的dbf文件
    fseek(rfp, 0, SEEK_END) ;
    if (ftell(rfp) < 32)
    {
        return 0 ;
    }
    
    rewind(rfp) ;
    // 读取文件头
    fread(pHead, sizeof(DBFHead), 1, rfp) ;
    
    // 信息头个数，头32字节，再加一个结束标志，所以减33
    nFieldCount = (pHead->headerLength-33)/32 ;
    int i(0) ;
    
    // 如果pField 已经申请了空间,释放之
    if (pField != NULL)
    {
        delete [] pField ;
		pField = NULL ;
    }
    if (nFieldCount > 0)
    {
        pField = new DBFField[nFieldCount];
    }
    
    if (pField == NULL)
    {
        return 0 ;
    }
    
    fread(pField, sizeof(DBFField), nFieldCount, rfp) ;

    // 因为记录长度有一个字节为标志删除位
    if (pHead->recordLength-1 > 0)
    {
        pBuf = new char[pHead->recordLength-1] ;
        memset(pBuf, 0x20, (pHead->recordLength-1) * sizeof(char)) ;
    }
    
    // 读取结束标志
    fgetc(rfp) ;
    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : DisplayHeadInformat
*  功能描述 : 输出头信息
*  参数列表 : 
*  说    明 : 
*  返回结果 : 无返回值
*
*******************************************************************************/
void dbf::DisplayHeadInformat(void)
{
    if (pFileName != NULL)
    {
        cout << "文件名: " << pFileName << endl << endl ;;
    }

    if (pHead != NULL)
    {
        cout << "文件头信息:" << ends ;
        cout << "版本号: " << int(pHead->vers) << endl ;
        cout << "年: " << int(pHead->year + 1900) << ends ;
        cout << "月: " << int(pHead->month) << ends ;
        cout << "日: " << int(pHead->day) << ends ;
        cout << "记录条数: " << pHead->numberOfRecords << endl ;
        cout << "文件头字节数: " << pHead->headerLength << endl ;
        cout << "每条记录长度: " << pHead->recordLength << endl ;
        cout << endl ;
    }
}

/*******************************************************************************
*
*  函 数 名 : DisplayFieldInformat
*  功能描述 : 输出项信息
*  参数列表 : 
*  说    明 : 
*  返回结果 : 无返回值
*
*******************************************************************************/
void dbf::DisplayFieldInformat(void)
{
    int i(0) ;
    char buf[FieldNameMaxLen + 1] = {0} ;

    cout << endl << "文件信息描述:" << endl ;
    for (i = 0; i < nFieldCount; ++i)
    {
        cout << "第" << setw(2) << i+1 << "项文件信息描述" << endl ;
        memset(buf, 0, 12) ;
        strncpy(buf, pField[i].field_name, FieldNameMaxLen) ;
        cout << "项名: " << buf << endl ;

        cout << "存储类型: " ;
        switch(pField[i].field_type)
        {
        case 'C':
            cout << "字符型" ;
            break ;
        case 'N':
            cout << "数字型" ;
            break ;
        case 'L':
            cout << "逻辑型" ;
        }
        cout << ends << flush ;

        cout << "字段长度: " << (int)pField[i].field_length << endl << endl ;
    }
}


/*******************************************************************************
*
*  函 数 名 : AddField
*  功能描述 : 添加字段
*  参数列表 : 
*  说    明 : 
*  返回结果 : 失败返回0, 成功返回1
*
*******************************************************************************/
int dbf::AddField(const char *FieldName, const char type, int nLen)
{
    if (FieldName == NULL)
    {
        return 0 ;
    }

    // 存储类型的判断，我们的程序只接受这三种
    if (type != Character && type != Number && type != Logical)
    {
        return 0 ;
    }

    if (pHead == NULL)
    {
        CreateHead() ;
    }
    
    // 查找这个项名是否存在
    int nIndex(0) ;
    int Offset = GetOffset(FieldName, nIndex) ;

    // 如果存在这个项名，则返回
    if (Offset != -1)
    {
        return 0 ;
    }

    // 项个数自增
    ++nFieldCount ;
    if (pField == NULL)
    {
        pField = new DBFField[nFieldCount] ;
        memset(pField, 0, sizeof(DBFField) * nFieldCount) ;
    }
    else
    {
        DBFField * p = new DBFField[nFieldCount] ;
        memset(p, 0, sizeof(DBFField) * nFieldCount) ;
        memcpy(p, pField, sizeof(DBFField) * (nFieldCount-1) ) ;
        DBFField * tmp = pField ;
        pField = p ;
        delete [] tmp ;
    }

    strncpy(pField[nFieldCount-1].field_name, FieldName, FieldNameMaxLen) ;
    pField[nFieldCount-1].field_type = type ;
    pField[nFieldCount-1].field_length = nLen ;

    // 重新计算文件头长度
    pHead->headerLength += 32 ;
    pHead->recordLength = 0 ;
    for (int i = 0; i < nFieldCount; ++i)
    {
        pHead->recordLength += pField[i].field_length ;
    }
    // 加上一个删除标志
    // 每条记录的第一个字节为删除标志
    pHead->recordLength += 1 ;

    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : CreateHead
*  功能描述 : 新建一个头
*  参数列表 : 
*  说    明 : 清除原来的头，并填充0
*  返回结果 : 失败返回0, 成功返回1
*
*******************************************************************************/
int dbf::CreateHead()
{
    // 如果已经有了文件头,清除原来的信息
    if (pHead != NULL)
    {
        pHead->vers = 0x3 ;
        SetHeadTime() ;
        pHead->headerLength = 33 ;
        pHead->numberOfRecords = 0 ;
        pHead->recordLength = 0 ;
        return 0 ;
    }

    pHead = new DBFHead;
    if (pHead == NULL)
    {
        return 0 ;
    }

    memset(pHead, 0, sizeof(DBFHead)) ;

    pHead->vers = 0x3 ;
    SetHeadTime() ;
    // 加上最后的结束标志
    pHead->headerLength = 33 ;

    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : SetHeadTime
*  功能描述 : 设置最后修改时间
*  参数列表 : 
*  说    明 : 
*  返回结果 : 失败返回0, 成功返回1
*
*******************************************************************************/
void dbf::SetHeadTime()
{
    SYSTEMTIME sysTime ; 
    GetLocalTime(&sysTime) ; 

    pHead->year = sysTime.wYear - 1900 ;
    pHead->month = (unsigned char) sysTime.wMonth ;
    pHead->day = (unsigned char) sysTime.wDay ;
}

/*******************************************************************************
*
*  函 数 名 : WriteHead
*  功能描述 : 将头重写文件
*  参数列表 : 
*  说    明 : 每次写入都要更新文件最后修改时间
*  返回结果 : 失败返回0, 成功返回1
*
*******************************************************************************/
int dbf::WriteHead()
{
    if (rfp == NULL)
    {
        return 0 ;
    }

    char End = 0x0D ;
    Submit() ;
    rewind(rfp) ;

    // 修改文件头的时间
    SetHeadTime() ;

    fseek(rfp, 0,  SEEK_SET) ;
    fwrite(pHead,  sizeof(DBFHead), 1, rfp) ;
    fwrite(pField, sizeof(DBFField), nFieldCount, rfp) ;
    fwrite(&End,   sizeof(char), 1, rfp) ;
    Submit() ;

    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : HeadWriteToFile
*  功能描述 : 将头写入文件
*  参数列表 : 
*  说    明 : 新建数据库时使用，会在头后面写0x1A
*  返回结果 : 失败返回0, 成功返回1
*
*******************************************************************************/
int dbf::HeadWriteToFile()
{
    if (wfp != NULL)
    {
        WriteHead() ;
        fputc(0x1A, wfp) ;
        Submit() ;
        return 1;
    }
    return 0 ;
}

/*******************************************************************************
*
*  函 数 名 : HeadWriteToFile
*  功能描述 : 将头写入文件
*  参数列表 : 
*  说    明 : 新建数据库时使用，会在头后面写0x1A
*  返回结果 : 失败返回0, 成功返回1
*
*******************************************************************************/
int dbf::WriteRecord(int nPosition)
{
    char ch = 0x20 ,
         state = 0x20;
    //int  nOldPosition = ftell(rfp) ;
    int  nDescPosition = pHead->headerLength + nPosition * pHead->recordLength ;

    fseek(rfp, 0, SEEK_END) ;
    // 如果nPosition > nCount 的话，说明指定的位置过大，加在文件后面
    if (nDescPosition >= ftell(rfp))
    {
        AddRecord() ;
    }
    
    // 如果指定的位置合法
    else
    {
        fseek(rfp, nDescPosition, SEEK_SET) ;

        // 判断是不是修改数据
        state = fgetc(rfp) ;
        //fseek(rfp, -1, SEEK_CUR) ;
        fseek(rfp, nDescPosition, SEEK_SET) ;
        fwrite(&ch, sizeof(char), 1, rfp) ;
        fflush(rfp);
        Submit() ;
 
        SetInt("id", nPosition+1) ;
  
        fwrite(pBuf, pHead->recordLength - 1, 1 , rfp) ;
        Submit() ;
        if (state == 0x2A)
        {
            pHead->numberOfRecords++;
        }
    } // end of else
    memset(pBuf, 0x20, pHead->recordLength - 1) ;
    //fseek(rfp, nOldPosition, SEEK_SET ) ;
    WriteHead();

    return nPosition;
}

/*******************************************************************************
*
*  函 数 名 : ReadItem
*  功能描述 : 读取指定项信息
*  参数列表 : ItemName -- 项名
*             Buf      -- 接收buffer
*  说    明 : 
*  返回结果 : 失败返回-1, 成功返回偏移量
*
*******************************************************************************/
int dbf::ReadItem(const char *ItemName, char *Buf)
{
    // 记录偏移字节
    int offset(0) ,
        i(0);

    if (ItemName == NULL || Buf == NULL)
    {
        return 0;
    }
    
    offset = GetOffset(ItemName, i);
    
    if (offset != -1)
    {
        memcpy(Buf, ((char *)pBuf + offset), pField[i].field_length) ;
    }
    return -1 ;
}

/*******************************************************************************
*
*  函 数 名 : GetOffset
*  功能描述 : 返回项名的偏移，以后通过变量返回下标
*  参数列表 : ItemName -- 项名
*             Buf      -- 接收buffer
*  说    明 : 
*  返回结果 : 失败返回-1, 成功返回偏移量
*
*******************************************************************************/
int dbf::GetOffset(const char *ItemName, int &nIndex)
{
    int Offset(0) ;
        nIndex = 0;
    if (ItemName == NULL)
    {
        return -1 ;
    }

    for (; nIndex < nFieldCount; ++nIndex)
    {
        // 项名相同
        if (strcmpi(ItemName, pField[nIndex].field_name) == 0)
        {
            return Offset ;
        }
        Offset += pField[nIndex].field_length ;
    }
    return -1 ;
}

/*******************************************************************************
*
*  函 数 名 : GetState
*  功能描述 : 返回文件状态
*  参数列表 : 
*  说    明 : 
*  返回结果 : 返回dbf状态
*
*******************************************************************************/
int dbf::GetState()
{
    return nState ;
}

/*******************************************************************************
*
*  函 数 名 : ReadString
*  功能描述 : 读取指定项名信息
*  参数列表 : ItemName -- 项名
*             Buf     -- 接收buffer
*  说    明 : 
*  返回结果 : 失败返回0, 成功返回项值长度
*
*******************************************************************************/
int dbf::ReadString(const char *ItemName, char *Buf)
{
    int nIndex(0) ,
        Offset(0),
        nLen(0);

    Offset = GetOffset(ItemName, nIndex) ;
    nLen = pField[nIndex].field_length ;

    if (Offset != -1)
    {
        memcpy(Buf, &((char *)pBuf)[Offset], nLen) ;
        return nLen ;
    }
    return 0;
}

/*******************************************************************************
*
*  函 数 名 : ReadInt
*  功能描述 : 读取指定项名信息(整型)
*  参数列表 : ItemName -- 项名
*             Result   -- 保存数据
*  说    明 : 
*  返回结果 : 失败返回-1, 成功atoi后的值
*
*******************************************************************************/
int dbf::ReadInt(const char *ItemName, int &Result)
{
    int tmp(0) ;
    char buf[16] = {0} ;
    ReadString(ItemName, buf) ;
    tmp = atoi(buf) ;
    return Result = tmp ;
}

/*******************************************************************************
*
*  函 数 名 : SetInt
*  功能描述 : 设置指定项名信息(整型)
*  参数列表 : ItemName -- 项名
*             nValue   -- 新值
*  说    明 : 
*  返回结果 : 失败返回0, 成功返回1
*
*******************************************************************************/
int dbf::SetInt(const char *ItemName, int nValue)
{
    int Offset(0) ,
        nIndex(0),
        len(0);
    char szFormat[16] = {0} ;
    char szBuf[16] = {0} ;

    if (ItemName == NULL)
    {
        return 0 ;
    }

    Offset= GetOffset(ItemName, nIndex) ;

    if (Offset != -1)
    {
        len = pField[nIndex].field_length ;
        sprintf(szFormat, "%%%dd", len);
        sprintf(szBuf, szFormat, nValue);
        memcpy(((char *)pBuf) + Offset, szBuf, len) ;
        return 1 ;
    }
    return 0 ;
}

/*******************************************************************************
*
*  函 数 名 : DeleteRecord
*  功能描述 : 设置指定信息
*  参数列表 : nIndex -- 信息在文件中的记录下标
*  说    明 : 
*  返回结果 : 失败返回0, 成功返回1
*
*******************************************************************************/
int dbf::DeleteRecord(int nIndex)
{
    // 取得文件长度
    fseek(rfp, 0, SEEK_END) ;
    int nLen = ftell(rfp) ;
    
    // 判断指定下标是否超过文件长度
    if ((pHead->headerLength + nIndex * pHead->recordLength) < nLen)
    {
        char ch = 0x2A;
        int Offset = pHead->headerLength + nIndex * pHead->recordLength ;
        fseek(rfp, Offset, SEEK_SET) ;
        fwrite(&ch, sizeof(char), 1, rfp) ;
        pHead->numberOfRecords--;
        WriteHead();
        Submit() ;

        // 将已删除空间下标放进空闲表
        pFree.InsertLast(nIndex) ;
        return 1 ;
    }
    return 0 ;
}

/*******************************************************************************
*
*  函 数 名 : SaveRecord
*  功能描述 : 保存记录
*  参数列表 : nIndex -- 信息在文件中的记录下标
*  说    明 : 
*  返回结果 : 失败返回 0, 成功返回 1
*
*******************************************************************************/
int dbf::SaveRecord(int nIndex)
{
    return WriteRecord(nIndex) ;
}

int dbf::SetString(const char *ItemName, const char *Buf)
{
    if (Buf == NULL || ItemName == NULL)
    {
        return 0 ;
    }

    int nIndex(0) ;
    int Offset = GetOffset(ItemName, nIndex) ;
    int i(0) ;
    if (Offset == -1)
    {
        return 0 ;
    }
    /***************************************************************************
    *
    *  修改人:   黄 奇
    *  修改记录: 2009.9.19日
    *  增加了memset((char *)pBuf+Offset, 0x20, pField[nIndex].field_length) ;
    *  解决了当原记录中字符长度大于新的时，里面出现一些原字符的一些遗留信息
    *
    ***************************************************************************/
    memset((char *)pBuf+Offset, 0x20, pField[nIndex].field_length) ;

    if (strlen(Buf) < pField[nIndex].field_length)
    {
        strcpy(((char *)pBuf + Offset), Buf) ;
    }
    else
    {
        memcpy(((char *)pBuf + Offset), Buf, pField[nIndex].field_length) ;
    }
    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : Clear
*  功能描述 : 清空dbf缓存
*  参数列表 : 
*  说    明 : 
*  返回结果 : 无
*
*******************************************************************************/
void dbf::Clear()
{
    if (pHead == NULL)
    {
        return ;
    }

    // 如果还未申请缓存，申请之
    if (pBuf == NULL && pHead->recordLength - 1 > 0)
    {
        pBuf = new char[pHead->recordLength - 1] ;
    }

    memset(pBuf, 0x20, pHead->recordLength - 1) ;
}

/*******************************************************************************
*
*  函 数 名 : WriteEndState
*  功能描述 : 在文件末写上结束标志
*  参数列表 : 
*  说    明 : 
*  返回结果 : 无
*
*******************************************************************************/
void dbf::WriteEndState()
{
    if (wfp == NULL)
    {
        return ;
    }
    char ch(-1) ;
    fseek(wfp, -1, SEEK_END) ;
    ch = fgetc(wfp) ;
    if (ch != 0x1a)
    {
        //fputc(0x1A, fp);
        ch = 0x1A;
        fwrite(&ch, sizeof(char), 1, wfp) ;
        Submit() ;
    }
    return ;
}

/*******************************************************************************
*
*  函 数 名 : Submit
*  功能描述 : 刷新wfp与rfp文件指针，
*  参数列表 : 
*  说    明 : 文件指针同步
*  返回结果 : 无
*
*******************************************************************************/
void dbf::Submit()
{
    fflush(wfp) ;
    fflush(rfp);
}

/*******************************************************************************
*
*  函 数 名 : MoveToFirst
*  功能描述 : 将指针移动到第一条记录处
*  参数列表 : 
*  说    明 : 
*  返回结果 : 成功返回1, 失败返回0
*
*******************************************************************************/
int dbf::MoveToFirst()
{
    if (rfp == NULL)
    {
        return 0 ;
    }

    fseek(rfp, pHead->headerLength, SEEK_SET);
    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : ReadRecord
*  功能描述 : 在文件中读记录
*  参数列表 : nIndex -- 记录在文件中的偏移数(第多少条记录)
*  说    明 : 
*  返回结果 : 读到文件尾返回 -1,记录已删除返回 0，成功返回 1
*
*******************************************************************************/
int dbf::ReadRecord(int nIndex)
{
    int nResult = 0 ;
    int nPosition = pHead->headerLength + nIndex * pHead->recordLength ;
    int nOldPosition = ftell(rfp) ;
    int nCount = 0 ;
    char state(0) ;

    // 求出文件长度
    fseek(rfp, 0, SEEK_END) ;
    nCount = ftell(rfp) ;

    // 如果读的记录已经超过文件长度了，返回 -1
    if (nPosition >= nCount)
    {
        fseek(rfp, nOldPosition, SEEK_SET) ;
        return -1 ;
    }

    // 如果当前记录有效，返回1
    fseek(rfp, nPosition, SEEK_SET) ;
    if (( state = fgetc(rfp)) == 0x20)
    {
        nResult = 1 ;
    }
    // 如果当前记录已删除，返回0
    else if (state == 0x2A)
    {
        nResult = 0 ;
    }

    // 将记录写到pBuf里去
    fread(pBuf, pHead->recordLength - 1,1, rfp) ;

    // 指针指回原来的地方
    fseek(rfp, nOldPosition, SEEK_SET) ;

    Submit() ;
    
    return nResult ;
}

/*******************************************************************************
*
*  函 数 名 : ReadNextRecord
*  功能描述 : 读取下一条记录
*  参数列表 : 
*  说    明 : 
*  返回结果 : 成功返回1, 失败返回0
*
*******************************************************************************/
int dbf::ReadNextRecord()
{
    int nTag = 0 ;
    int nPosition = ftell(rfp) ;
    int nCount = 0 ;
    
    // 求出文件长度
    fseek(rfp, 0, SEEK_END) ;
    nCount = ftell(rfp) ;
    
    if (nCount - nPosition <= pHead->recordLength)
    {
        // 指针复位
        fseek(rfp, nPosition, SEEK_SET) ;
        return 0 ;
    }

    // 一直读到一条有效的记录为止，如果读到尾，则返回 0
    while((nTag = fgetc(rfp)) && fread(pBuf, pHead->recordLength - 1, 1, rfp))
    {
        if (nTag == 0x20)
        {
            return 1 ;
        }
    }
    memset(pBuf, 0x20, pHead->recordLength - 1) ;
    return 0 ;
}

// 重载输出运算符
ostream & operator << (ostream &os, const dbf & obj)
{
    int i = 0;
    char buf[128] = {0} ;
    for (; i < obj.nFieldCount; ++i)
    {
        memset(buf, 0, 128) ;
        //((class dbf &)obj).ReadItem(obj.pField[i].field_name, buf) ;
        ((class dbf &)obj).ReadString(obj.pField[i].field_name, buf) ;
        os << setw(obj.pField[i].field_length) << buf << " "<< flush ;
    }
    return os;
}

/*******************************************************************************
*
*  函 数 名 : GetItemCount
*  功能描述 : 取得项个数
*  参数列表 : 
*  说    明 : 
*  返回结果 : 返回项个数
*
*******************************************************************************/
int dbf::GetItemCount()
{
    return nFieldCount ;
}

/*******************************************************************************
*
*  函 数 名 : GetRecordCount
*  功能描述 : 取得文件记录条数
*  参数列表 : 
*  说    明 : 
*  返回结果 : 返回文件记录条数、以文件头的为准
*
*******************************************************************************/
int dbf::GetRecordCount()
{
    return pHead->numberOfRecords ;
}

/*******************************************************************************
*
*  函 数 名 : WriteIndex
*  功能描述 : 将空闲空间索引写入文件
*  参数列表 : 
*  说    明 : 
*  返回结果 : 成功返回1, 失败返回0
*
*******************************************************************************/
int dbf::WriteIndex()
{
    FILE * Freefp = NULL ;
    if (pFreeIndexName == NULL)
    {
        return 0 ;
    }

    int i(0) ,
        n(0) ,
        t(0) ;

    Freefp = fopen(pFreeIndexName, "wb");
    if (Freefp == NULL)
    {
    #ifdef _DEBUG
        cout << "文件打开出错" << endl ;
    #endif
        return 0 ;
    }

    // 取得链表的长度
    n = pFree.GetSize() ;
    
    // 将长度写入文件
    fwrite(&n, sizeof(int), 1, Freefp) ;

    // 依次将每个元素写入文件
    for (i = 0; i < n; ++i)
    {
        //t = pFree[i] ;
        t = pFree.Pop() ;
        fwrite(&t, sizeof(int), 1, Freefp) ;
    }
    
    if (Freefp != NULL)
    {
        fclose(Freefp) ;
        Freefp = NULL ;
    }
    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : ReadIndex
*  功能描述 : 读索引
*  参数列表 : 
*  说    明 : 读空闲索引
*  返回结果 : 成功返回1, 失败返回0
*
*******************************************************************************/
int dbf::ReadIndex()
{
    FILE *Freefp = NULL ;

    // 如果索引文件没有的话,则建立
    if (pFreeIndexName != NULL && _access(pFreeIndexName,0) == -1)
    {
        FILE *fp = fopen(pFreeIndexName, "w+b") ;
        fclose(fp) ;
        return 0 ;
    }

    int n(0) , // 条数
        i(0) , // 用于循环
        t(0) ; // 存储临时变量

    Freefp = fopen(pFreeIndexName, "r+b") ;

	fseek(rfp, 0, SEEK_SET) ;
    fread(&n, sizeof(int), 1, Freefp) ;

    for (i = 0; i < n; ++i)
    {
        fread(&t, sizeof(int), 1, Freefp) ;
        pFree.InsertLast(t) ;
    }

    if (Freefp != NULL)
    {
        fclose(Freefp) ;
        Freefp = NULL ;
    }
    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : AddRecord
*  功能描述 : 添加记录
*  参数列表 : 
*  说    明 : 如果空闲空间有空的话，填充过去，否则追加在文件尾
*  返回结果 : 返回插入后的文件偏移量
*
*******************************************************************************/
int dbf::AddRecord()
{
    // 如果链表是空的话，追加到文件尾
    if (pFree.IsEmpty())
    {
        int  nIndex(0) ;
        char ch = 0x20 ;
        // 保存原来的文件指针偏移
        int  nOldPosition = ftell(rfp) ;
        
        // 跳过0x1A
        fseek(rfp, -1, SEEK_END) ;
        
        // 如果后面那位是结束标志
        if ((ch = fgetc(rfp))  == 0x1A)
        {
            ch = 0x20 ;
            fseek(rfp, -1, SEEK_END) ;
            fwrite(&ch, sizeof(char), 1, rfp) ;
        }
        else
        {
            ch = 0x20 ;
            fseek(wfp, 0, SEEK_END) ;
            fwrite(&ch, sizeof(char), 1, wfp) ;
        }

        fseek(wfp, 0, SEEK_END) ;
        nIndex = (ftell(wfp) - pHead->headerLength) / pHead->recordLength + 1;

        SetInt("id", nIndex) ;
        fwrite(pBuf, pHead->recordLength - 1, 1 , wfp) ;

        ch = 0x1a ;
        fwrite(&ch, sizeof(char), 1, wfp) ;
        pHead->numberOfRecords++;
        Submit() ;

        WriteHead();
        fseek(rfp, nOldPosition, SEEK_SET ) ;
        
        return nIndex - 1;
    }
    // 否则添加到文件末尾
    else
    {
        return WriteRecord(pFree.Pop()) ;
    }
}

/*******************************************************************************
*
*  函 数 名 : InitFileSize
*  功能描述 : 初始化文件大小
*  参数列表 : 
*  说    明 : 
*  返回结果 : 错误返回 0, 正确返回 1
*
*******************************************************************************/
int dbf::InitFileSize(unsigned int nSize)
{
    char *buf = new char[pHead->recordLength] ;
    unsigned int i(0) ;
    if (nSize <= pHead->headerLength)
    {
        return 0 ;
    }
    char ch = 0x2A ;
    nSize -= pHead->headerLength ;
    nSize /= pHead->recordLength ;
    ++nSize ;

    Submit() ;
    // 将文件指针移到文件头后面
    fseek( wfp, pHead->headerLength, SEEK_SET) ;
    memset(buf, 0x2A, pHead->recordLength) ;
    for (i = 0; i < nSize; ++i)
    {
        fwrite(buf, pHead->recordLength, sizeof(char), wfp) ;
    }
    
    ch = 0x1A;
    fwrite(&ch, sizeof(char), 1, wfp) ;
    Submit() ;

    for (i = 0; i < nSize; ++i)
    {
        pFree.InsertLast(i) ;
    }

    if (buf)
    {
        delete [] buf ;
        buf = NULL ;
    }
    return 1 ;
}

/*******************************************************************************
*
*  函 数 名 : FileIncrease
*  功能描述 : 文件增长
*  参数列表 : 
*  说    明 : nPercent为百分比，百分号前面的整数部分
*  返回结果 : 错误返回 0, 正确返回 1
*
*******************************************************************************/
int dbf::FileIncrease(unsigned int nPercent)
{
    unsigned int i(0) ;
    char *buf = new char[pHead->recordLength] ;
    memset(buf, 0x2a, pHead->recordLength) ;
    if (nPercent < 10)
    {
        return 0 ;
    }

    char ch = 0x20 ;
    unsigned int nOffset = pHead->headerLength + \
                                 pHead->recordLength * pHead->numberOfRecords ;
    unsigned int nSize = pHead->numberOfRecords * nPercent ;
    nSize /= 100 ;
    ++nSize ;

    Submit() ;
    fseek(wfp, nOffset, SEEK_SET) ;
    for (i = 0; i < nSize; ++i)
    {
        fwrite(buf, pHead->recordLength, sizeof(char), wfp) ;
    }
    ch = 0x1A ;
    fwrite(&ch, sizeof(char), 1, wfp) ;
    Submit() ;

    nSize += pHead->numberOfRecords ;
    for (i = pHead->numberOfRecords; i < nSize; ++i)
    {
        pFree.InsertLast(i) ;
    }
    return 1 ;
}
