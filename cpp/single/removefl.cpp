#include <windows.h>
#include <iostream>
using namespace std;
#include <io.h>
void main()
{
   char source[256];//文件路径  
  cout<<"请输入要删除的文件路径:"<<endl;  
  cin>>source;  
/* _access(char *,int) 判断文件是否存在 
存在 返回0;不存在 返回-1. 
_access(const char *path,int mode) 
mode的值: 
00 是否存在 
02 写权限 
04 读权限 
06 读写权限 
*/  
  if(!_access(source,0))//如果文件存在:文件为只读无法删除  
  {  
  //去掉文件只读属性  
  SetFileAttributes(source,0);  
  if(DeleteFile(source))//删除成功  
  {  
     cout<<source<<" 已成功删除."<<endl;  
  }  
  else//无法删除:文件只读或无权限执行删除  
  {  
     cout<<source<<" 无法删除:文件为只读属性或无删除权限."<<endl;  
  }  
  }  
  else//文件不存在  
  {  
    cout<<source<<" 不存在,无法删除."<<endl;  
  }  
}
