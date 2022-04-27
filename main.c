#include<windows.h>
#include<stdio.h>

#define MAX_PROC 7

HANDLE procesy[MAX_PROC];

int main(int argv, char** argc)
{
	STARTUPINFO si[MAX_PROC];
	PROCESS_INFORMATION pi[MAX_PROC];

	int aktywne[MAX_PROC];
	printf_s("Ile procesow chcesz: ");
	char liczba_procesow[2];
	gets_s(liczba_procesow, 2);
	int liczProc = atoi(liczba_procesow);

	int priorytety[4] = { IDLE_PRIORITY_CLASS,
	NORMAL_PRIORITY_CLASS,
	HIGH_PRIORITY_CLASS,
	REALTIME_PRIORITY_CLASS };
	for (int i = 0; i < liczProc; i++)
	{
		aktywne[i] = 0;
	}
	while (1)
	{
		printf_s("Jaka operacje chcesz wykonac: ");
		char operacja[2];
		gets_s(operacja, 2);
		if (operacja[0] == 'c')
		{
			printf_s("Jaka priorytet maja miec procesy: ");
			char priorytet[2];
			gets_s(priorytet, 2);
			int prior = atoi(liczba_procesow);
			for (int i = 0; i < liczProc; i++)
			{
				ZeroMemory(&si[i], sizeof(si[i]));
				si[i].cb = sizeof(si[i]);
				ZeroMemory(&pi[i], sizeof(pi[i]));
				if (aktywne[i] == 0)
				{
					procesy[i] = CreateProcess(L"C:\\PR\\Lab4Thread\\Lab4CP\\x64\\Debug\\Lab4CP.exe",  
						NULL,        // Command line
						NULL,           // Process handle not inheritable
						NULL,           // Thread handle not inheritable
						FALSE,          // Set handle inheritance to FALSE
						CREATE_NEW_CONSOLE,              // No creation flags
						NULL,           // Use parent's environment block
						NULL,           // Use parent's starting directory 
						&(si[i]),            // Pointer to STARTUPINFO structure
						&(pi[i]));           // Pointer to PROCESS_INFORMATION structure
						
					if (procesy[i] == INVALID_HANDLE_VALUE)
					{
						printf_s("CreateProcess failed (%d).\n", GetLastError());
						return;
					}
					else
					{
						aktywne[i] = 1;
						SetPriorityClass(procesy[i], prior);
						printf_s("Stworzono proces\n");
					}
				}
			}
		}
		else if (operacja[0] == 'e')
		{
			break;
		}
	}
	for (int i = 0; i < liczProc; i++)
	{
		WaitForSingleObject(pi[i].hProcess, INFINITE);
	}
	for (int i = 0; i < liczProc; i++)
	{
		CloseHandle(pi[i].hProcess);
		CloseHandle(pi[i].hThread);
	}
	return 0;
}