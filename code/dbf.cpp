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
*  �� �� �� : dbf
*  �������� : ���캯��
*  �����б� : 
*  ˵    �� : ��
*  ���ؽ�� : ��
*
*******************************************************************************/
dbf::dbf():wfp(NULL),rfp(NULL),pFileName(NULL),pHead(NULL),pField(NULL),\
                  pBuf(NULL),nState(0),nFieldCount(0),pFreeIndexName(NULL)
{
    ReadIndex() ;
}

/*******************************************************************************
*
*  �� �� �� : dbf
*  �������� : ���캯��
*  �����б� : FileName	--	dbf�ļ���
*  ˵    �� : ͨ��GetState()��״̬��
*  ���ؽ�� : ��
*
*******************************************************************************/
dbf::dbf(const char *FileName):wfp(NULL),rfp(NULL),pFileName(NULL),pHead(NULL),\
          pField(NULL),pBuf(NULL),nState(0),nFieldCount(0),pFreeIndexName(NULL)
{
    int len((int)strlen(FileName) + sizeof(char)) ;
    // ��ʼ������ָ�룬�ֱ����������������ݺ��������
    wfp = fopen(FileName, "a+b") ;
    rfp = fopen(FileName, "r+b") ;

    if (wfp != NULL && rfp != NULL)
    {
        // ΪpFileName ����ռ䣬����ļ���
        pFileName = new char[len] ;
        if (pFileName != NULL)
        {
            memset(pFileName, 0, len) ;
            strcpy(pFileName, FileName) ;
        }

        // ���пռ������ļ���
        pFreeIndexName = new char[len + SuffixSize] ;
        if (pFreeIndexName != NULL)
        {
            memset(pFreeIndexName, 0, len + SuffixSize) ;
            strcpy(pFreeIndexName, FileName) ;
            strcat(pFreeIndexName, Suffix) ;
        }

        // ΪpHead����ռ�,����ļ�ͷ
        pHead = new DBFHead ;
        if (pHead != NULL)
        {
            memset(pHead, 0, sizeof(DBFHead)) ;
            ReadHead();
        }
    }
    nState = 1 ;

    // ����ɾ���ռ�����
    ReadIndex() ;
}

/*******************************************************************************
*
*  �� �� �� : ~dbf
*  �������� : ��������
*  �����б� : 
*  ˵    �� : �ͷ���Դ��ͬʱ������д���ļ�
*  ���ؽ�� : 
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
            // д�������־
            char end = 0x1A; 
            fseek(wfp,0, SEEK_END) ;
            fwrite(&end, sizeof(char), 1, wfp);
            fflush(rfp) ;
            fflush(wfp) ;
        }
        fclose(wfp);
        wfp = NULL ;
    }

    // ������д���ļ�
    WriteIndex() ;

    // �����Ƿֱ��ǹر��ļ����ͷ��ڴ�ռ�
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
    cout << "����" << pFileName << "���б�ɹ�" << endl ;
    if (pFileName != NULL)
    {
        delete [] pFileName ;
        pFileName = NULL ;
    }
}


/*******************************************************************************
*
*  �� �� �� : ReadHead
*  �������� : ��ͷ��Ϣ
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : ��ȡͷ��Ϣ�����ʧ�ܣ�����0,���򷵻�1
*
*******************************************************************************/
int dbf::ReadHead(void)
{
    if (rfp == NULL)
    {
        return 0 ;
    }

    // ���½��ļ�ָ�붨λ���ļ�β
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

	// ����ļ�����С��32�ֽڣ�˵������һ��������dbf�ļ�
    fseek(rfp, 0, SEEK_END) ;
    if (ftell(rfp) < 32)
    {
        return 0 ;
    }
    
    rewind(rfp) ;
    // ��ȡ�ļ�ͷ
    fread(pHead, sizeof(DBFHead), 1, rfp) ;
    
    // ��Ϣͷ������ͷ32�ֽڣ��ټ�һ��������־�����Լ�33
    nFieldCount = (pHead->headerLength-33)/32 ;
    int i(0) ;
    
    // ���pField �Ѿ������˿ռ�,�ͷ�֮
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

    // ��Ϊ��¼������һ���ֽ�Ϊ��־ɾ��λ
    if (pHead->recordLength-1 > 0)
    {
        pBuf = new char[pHead->recordLength-1] ;
        memset(pBuf, 0x20, (pHead->recordLength-1) * sizeof(char)) ;
    }
    
    // ��ȡ������־
    fgetc(rfp) ;
    return 1 ;
}

/*******************************************************************************
*
*  �� �� �� : DisplayHeadInformat
*  �������� : ���ͷ��Ϣ
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : �޷���ֵ
*
*******************************************************************************/
void dbf::DisplayHeadInformat(void)
{
    if (pFileName != NULL)
    {
        cout << "�ļ���: " << pFileName << endl << endl ;;
    }

    if (pHead != NULL)
    {
        cout << "�ļ�ͷ��Ϣ:" << ends ;
        cout << "�汾��: " << int(pHead->vers) << endl ;
        cout << "��: " << int(pHead->year + 1900) << ends ;
        cout << "��: " << int(pHead->month) << ends ;
        cout << "��: " << int(pHead->day) << ends ;
        cout << "��¼����: " << pHead->numberOfRecords << endl ;
        cout << "�ļ�ͷ�ֽ���: " << pHead->headerLength << endl ;
        cout << "ÿ����¼����: " << pHead->recordLength << endl ;
        cout << endl ;
    }
}

/*******************************************************************************
*
*  �� �� �� : DisplayFieldInformat
*  �������� : �������Ϣ
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : �޷���ֵ
*
*******************************************************************************/
void dbf::DisplayFieldInformat(void)
{
    int i(0) ;
    char buf[FieldNameMaxLen + 1] = {0} ;

    cout << endl << "�ļ���Ϣ����:" << endl ;
    for (i = 0; i < nFieldCount; ++i)
    {
        cout << "��" << setw(2) << i+1 << "���ļ���Ϣ����" << endl ;
        memset(buf, 0, 12) ;
        strncpy(buf, pField[i].field_name, FieldNameMaxLen) ;
        cout << "����: " << buf << endl ;

        cout << "�洢����: " ;
        switch(pField[i].field_type)
        {
        case 'C':
            cout << "�ַ���" ;
            break ;
        case 'N':
            cout << "������" ;
            break ;
        case 'L':
            cout << "�߼���" ;
        }
        cout << ends << flush ;

        cout << "�ֶγ���: " << (int)pField[i].field_length << endl << endl ;
    }
}


/*******************************************************************************
*
*  �� �� �� : AddField
*  �������� : ����ֶ�
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : ʧ�ܷ���0, �ɹ�����1
*
*******************************************************************************/
int dbf::AddField(const char *FieldName, const char type, int nLen)
{
    if (FieldName == NULL)
    {
        return 0 ;
    }

    // �洢���͵��жϣ����ǵĳ���ֻ����������
    if (type != Character && type != Number && type != Logical)
    {
        return 0 ;
    }

    if (pHead == NULL)
    {
        CreateHead() ;
    }
    
    // ������������Ƿ����
    int nIndex(0) ;
    int Offset = GetOffset(FieldName, nIndex) ;

    // �����������������򷵻�
    if (Offset != -1)
    {
        return 0 ;
    }

    // ���������
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

    // ���¼����ļ�ͷ����
    pHead->headerLength += 32 ;
    pHead->recordLength = 0 ;
    for (int i = 0; i < nFieldCount; ++i)
    {
        pHead->recordLength += pField[i].field_length ;
    }
    // ����һ��ɾ����־
    // ÿ����¼�ĵ�һ���ֽ�Ϊɾ����־
    pHead->recordLength += 1 ;

    return 1 ;
}

/*******************************************************************************
*
*  �� �� �� : CreateHead
*  �������� : �½�һ��ͷ
*  �����б� : 
*  ˵    �� : ���ԭ����ͷ�������0
*  ���ؽ�� : ʧ�ܷ���0, �ɹ�����1
*
*******************************************************************************/
int dbf::CreateHead()
{
    // ����Ѿ������ļ�ͷ,���ԭ������Ϣ
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
    // �������Ľ�����־
    pHead->headerLength = 33 ;

    return 1 ;
}

/*******************************************************************************
*
*  �� �� �� : SetHeadTime
*  �������� : ��������޸�ʱ��
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : ʧ�ܷ���0, �ɹ�����1
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
*  �� �� �� : WriteHead
*  �������� : ��ͷ��д�ļ�
*  �����б� : 
*  ˵    �� : ÿ��д�붼Ҫ�����ļ�����޸�ʱ��
*  ���ؽ�� : ʧ�ܷ���0, �ɹ�����1
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

    // �޸��ļ�ͷ��ʱ��
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
*  �� �� �� : HeadWriteToFile
*  �������� : ��ͷд���ļ�
*  �����б� : 
*  ˵    �� : �½����ݿ�ʱʹ�ã�����ͷ����д0x1A
*  ���ؽ�� : ʧ�ܷ���0, �ɹ�����1
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
*  �� �� �� : HeadWriteToFile
*  �������� : ��ͷд���ļ�
*  �����б� : 
*  ˵    �� : �½����ݿ�ʱʹ�ã�����ͷ����д0x1A
*  ���ؽ�� : ʧ�ܷ���0, �ɹ�����1
*
*******************************************************************************/
int dbf::WriteRecord(int nPosition)
{
    char ch = 0x20 ,
         state = 0x20;
    //int  nOldPosition = ftell(rfp) ;
    int  nDescPosition = pHead->headerLength + nPosition * pHead->recordLength ;

    fseek(rfp, 0, SEEK_END) ;
    // ���nPosition > nCount �Ļ���˵��ָ����λ�ù��󣬼����ļ�����
    if (nDescPosition >= ftell(rfp))
    {
        AddRecord() ;
    }
    
    // ���ָ����λ�úϷ�
    else
    {
        fseek(rfp, nDescPosition, SEEK_SET) ;

        // �ж��ǲ����޸�����
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
*  �� �� �� : ReadItem
*  �������� : ��ȡָ������Ϣ
*  �����б� : ItemName -- ����
*             Buf      -- ����buffer
*  ˵    �� : 
*  ���ؽ�� : ʧ�ܷ���-1, �ɹ�����ƫ����
*
*******************************************************************************/
int dbf::ReadItem(const char *ItemName, char *Buf)
{
    // ��¼ƫ���ֽ�
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
*  �� �� �� : GetOffset
*  �������� : ����������ƫ�ƣ��Ժ�ͨ�����������±�
*  �����б� : ItemName -- ����
*             Buf      -- ����buffer
*  ˵    �� : 
*  ���ؽ�� : ʧ�ܷ���-1, �ɹ�����ƫ����
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
        // ������ͬ
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
*  �� �� �� : GetState
*  �������� : �����ļ�״̬
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : ����dbf״̬
*
*******************************************************************************/
int dbf::GetState()
{
    return nState ;
}

/*******************************************************************************
*
*  �� �� �� : ReadString
*  �������� : ��ȡָ��������Ϣ
*  �����б� : ItemName -- ����
*             Buf     -- ����buffer
*  ˵    �� : 
*  ���ؽ�� : ʧ�ܷ���0, �ɹ�������ֵ����
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
*  �� �� �� : ReadInt
*  �������� : ��ȡָ��������Ϣ(����)
*  �����б� : ItemName -- ����
*             Result   -- ��������
*  ˵    �� : 
*  ���ؽ�� : ʧ�ܷ���-1, �ɹ�atoi���ֵ
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
*  �� �� �� : SetInt
*  �������� : ����ָ��������Ϣ(����)
*  �����б� : ItemName -- ����
*             nValue   -- ��ֵ
*  ˵    �� : 
*  ���ؽ�� : ʧ�ܷ���0, �ɹ�����1
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
*  �� �� �� : DeleteRecord
*  �������� : ����ָ����Ϣ
*  �����б� : nIndex -- ��Ϣ���ļ��еļ�¼�±�
*  ˵    �� : 
*  ���ؽ�� : ʧ�ܷ���0, �ɹ�����1
*
*******************************************************************************/
int dbf::DeleteRecord(int nIndex)
{
    // ȡ���ļ�����
    fseek(rfp, 0, SEEK_END) ;
    int nLen = ftell(rfp) ;
    
    // �ж�ָ���±��Ƿ񳬹��ļ�����
    if ((pHead->headerLength + nIndex * pHead->recordLength) < nLen)
    {
        char ch = 0x2A;
        int Offset = pHead->headerLength + nIndex * pHead->recordLength ;
        fseek(rfp, Offset, SEEK_SET) ;
        fwrite(&ch, sizeof(char), 1, rfp) ;
        pHead->numberOfRecords--;
        WriteHead();
        Submit() ;

        // ����ɾ���ռ��±�Ž����б�
        pFree.InsertLast(nIndex) ;
        return 1 ;
    }
    return 0 ;
}

/*******************************************************************************
*
*  �� �� �� : SaveRecord
*  �������� : �����¼
*  �����б� : nIndex -- ��Ϣ���ļ��еļ�¼�±�
*  ˵    �� : 
*  ���ؽ�� : ʧ�ܷ��� 0, �ɹ����� 1
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
    *  �޸���:   �� ��
    *  �޸ļ�¼: 2009.9.19��
    *  ������memset((char *)pBuf+Offset, 0x20, pField[nIndex].field_length) ;
    *  ����˵�ԭ��¼���ַ����ȴ����µ�ʱ���������һЩԭ�ַ���һЩ������Ϣ
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
*  �� �� �� : Clear
*  �������� : ���dbf����
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : ��
*
*******************************************************************************/
void dbf::Clear()
{
    if (pHead == NULL)
    {
        return ;
    }

    // �����δ���뻺�棬����֮
    if (pBuf == NULL && pHead->recordLength - 1 > 0)
    {
        pBuf = new char[pHead->recordLength - 1] ;
    }

    memset(pBuf, 0x20, pHead->recordLength - 1) ;
}

/*******************************************************************************
*
*  �� �� �� : WriteEndState
*  �������� : ���ļ�ĩд�Ͻ�����־
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : ��
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
*  �� �� �� : Submit
*  �������� : ˢ��wfp��rfp�ļ�ָ�룬
*  �����б� : 
*  ˵    �� : �ļ�ָ��ͬ��
*  ���ؽ�� : ��
*
*******************************************************************************/
void dbf::Submit()
{
    fflush(wfp) ;
    fflush(rfp);
}

/*******************************************************************************
*
*  �� �� �� : MoveToFirst
*  �������� : ��ָ���ƶ�����һ����¼��
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : �ɹ�����1, ʧ�ܷ���0
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
*  �� �� �� : ReadRecord
*  �������� : ���ļ��ж���¼
*  �����б� : nIndex -- ��¼���ļ��е�ƫ����(�ڶ�������¼)
*  ˵    �� : 
*  ���ؽ�� : �����ļ�β���� -1,��¼��ɾ������ 0���ɹ����� 1
*
*******************************************************************************/
int dbf::ReadRecord(int nIndex)
{
    int nResult = 0 ;
    int nPosition = pHead->headerLength + nIndex * pHead->recordLength ;
    int nOldPosition = ftell(rfp) ;
    int nCount = 0 ;
    char state(0) ;

    // ����ļ�����
    fseek(rfp, 0, SEEK_END) ;
    nCount = ftell(rfp) ;

    // ������ļ�¼�Ѿ������ļ������ˣ����� -1
    if (nPosition >= nCount)
    {
        fseek(rfp, nOldPosition, SEEK_SET) ;
        return -1 ;
    }

    // �����ǰ��¼��Ч������1
    fseek(rfp, nPosition, SEEK_SET) ;
    if (( state = fgetc(rfp)) == 0x20)
    {
        nResult = 1 ;
    }
    // �����ǰ��¼��ɾ��������0
    else if (state == 0x2A)
    {
        nResult = 0 ;
    }

    // ����¼д��pBuf��ȥ
    fread(pBuf, pHead->recordLength - 1,1, rfp) ;

    // ָ��ָ��ԭ���ĵط�
    fseek(rfp, nOldPosition, SEEK_SET) ;

    Submit() ;
    
    return nResult ;
}

/*******************************************************************************
*
*  �� �� �� : ReadNextRecord
*  �������� : ��ȡ��һ����¼
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : �ɹ�����1, ʧ�ܷ���0
*
*******************************************************************************/
int dbf::ReadNextRecord()
{
    int nTag = 0 ;
    int nPosition = ftell(rfp) ;
    int nCount = 0 ;
    
    // ����ļ�����
    fseek(rfp, 0, SEEK_END) ;
    nCount = ftell(rfp) ;
    
    if (nCount - nPosition <= pHead->recordLength)
    {
        // ָ�븴λ
        fseek(rfp, nPosition, SEEK_SET) ;
        return 0 ;
    }

    // һֱ����һ����Ч�ļ�¼Ϊֹ���������β���򷵻� 0
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

// ������������
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
*  �� �� �� : GetItemCount
*  �������� : ȡ�������
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : ���������
*
*******************************************************************************/
int dbf::GetItemCount()
{
    return nFieldCount ;
}

/*******************************************************************************
*
*  �� �� �� : GetRecordCount
*  �������� : ȡ���ļ���¼����
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : �����ļ���¼���������ļ�ͷ��Ϊ׼
*
*******************************************************************************/
int dbf::GetRecordCount()
{
    return pHead->numberOfRecords ;
}

/*******************************************************************************
*
*  �� �� �� : WriteIndex
*  �������� : �����пռ�����д���ļ�
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : �ɹ�����1, ʧ�ܷ���0
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
        cout << "�ļ��򿪳���" << endl ;
    #endif
        return 0 ;
    }

    // ȡ������ĳ���
    n = pFree.GetSize() ;
    
    // ������д���ļ�
    fwrite(&n, sizeof(int), 1, Freefp) ;

    // ���ν�ÿ��Ԫ��д���ļ�
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
*  �� �� �� : ReadIndex
*  �������� : ������
*  �����б� : 
*  ˵    �� : ����������
*  ���ؽ�� : �ɹ�����1, ʧ�ܷ���0
*
*******************************************************************************/
int dbf::ReadIndex()
{
    FILE *Freefp = NULL ;

    // ��������ļ�û�еĻ�,����
    if (pFreeIndexName != NULL && _access(pFreeIndexName,0) == -1)
    {
        FILE *fp = fopen(pFreeIndexName, "w+b") ;
        fclose(fp) ;
        return 0 ;
    }

    int n(0) , // ����
        i(0) , // ����ѭ��
        t(0) ; // �洢��ʱ����

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
*  �� �� �� : AddRecord
*  �������� : ��Ӽ�¼
*  �����б� : 
*  ˵    �� : ������пռ��пյĻ�������ȥ������׷�����ļ�β
*  ���ؽ�� : ���ز������ļ�ƫ����
*
*******************************************************************************/
int dbf::AddRecord()
{
    // ��������ǿյĻ���׷�ӵ��ļ�β
    if (pFree.IsEmpty())
    {
        int  nIndex(0) ;
        char ch = 0x20 ;
        // ����ԭ�����ļ�ָ��ƫ��
        int  nOldPosition = ftell(rfp) ;
        
        // ����0x1A
        fseek(rfp, -1, SEEK_END) ;
        
        // ���������λ�ǽ�����־
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
    // ������ӵ��ļ�ĩβ
    else
    {
        return WriteRecord(pFree.Pop()) ;
    }
}

/*******************************************************************************
*
*  �� �� �� : InitFileSize
*  �������� : ��ʼ���ļ���С
*  �����б� : 
*  ˵    �� : 
*  ���ؽ�� : ���󷵻� 0, ��ȷ���� 1
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
    // ���ļ�ָ���Ƶ��ļ�ͷ����
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
*  �� �� �� : FileIncrease
*  �������� : �ļ�����
*  �����б� : 
*  ˵    �� : nPercentΪ�ٷֱȣ��ٷֺ�ǰ�����������
*  ���ؽ�� : ���󷵻� 0, ��ȷ���� 1
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
