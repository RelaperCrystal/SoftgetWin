#include <shlwapi.h>
#include <tchar.h>

BOOL SHDeleteFolder(LPCTSTR pstrFolder)
{
    int iPathLen = _tcslen(pstrFolder);
    TCHAR tczFolder[MAX_PATH+1];
    SHFILEOPSTRUCT FileOp; 

    if ((NULL == pstrFolder))
    {
        return FALSE;
    }


    if (iPathLen >= MAX_PATH)
    {
        return FALSE;
    }

    /*ȷ��Ŀ¼��·����2��\0��β*/
    ZeroMemory(tczFolder, (MAX_PATH+1)*sizeof(TCHAR));
    _tcscpy(tczFolder, pstrFolder);
    tczFolder[iPathLen] = _T('\0');
    tczFolder[iPathLen+1] = _T('\0');

    ZeroMemory(&FileOp, sizeof(SHFILEOPSTRUCT)); 
    FileOp.fFlags |= FOF_SILENT;            //����ʾ����
    FileOp.fFlags |= FOF_NOERRORUI;         //�����������Ϣ
    FileOp.fFlags |= FOF_NOCONFIRMATION;    //ֱ��ɾ����������ȷ��
    FileOp.hNameMappings = NULL;
    FileOp.hwnd = NULL;
    FileOp.lpszProgressTitle = NULL;
    FileOp.wFunc = FO_DELETE;
    FileOp.pFrom = tczFolder;               //Ҫɾ����Ŀ¼��������2��\0��β
    FileOp.pTo = NULL; 

    FileOp.fFlags &= ~FOF_ALLOWUNDO;       //ֱ��ɾ�������������վ

    /*ɾ��Ŀ¼*/
    if (0 == SHFileOperation(&FileOp))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int main()
{
    SHDeleteFolder("downloads");
    return 0;
}
