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

    /*确保目录的路径以2个\0结尾*/
    ZeroMemory(tczFolder, (MAX_PATH+1)*sizeof(TCHAR));
    _tcscpy(tczFolder, pstrFolder);
    tczFolder[iPathLen] = _T('\0');
    tczFolder[iPathLen+1] = _T('\0');

    ZeroMemory(&FileOp, sizeof(SHFILEOPSTRUCT)); 
    FileOp.fFlags |= FOF_SILENT;            //不显示进度
    FileOp.fFlags |= FOF_NOERRORUI;         //不报告错误信息
    FileOp.fFlags |= FOF_NOCONFIRMATION;    //直接删除，不进行确认
    FileOp.hNameMappings = NULL;
    FileOp.hwnd = NULL;
    FileOp.lpszProgressTitle = NULL;
    FileOp.wFunc = FO_DELETE;
    FileOp.pFrom = tczFolder;               //要删除的目录，必须以2个\0结尾
    FileOp.pTo = NULL; 

    FileOp.fFlags &= ~FOF_ALLOWUNDO;       //直接删除，不放入回收站

    /*删除目录*/
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
