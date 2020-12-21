#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <time.h>
#include <iomanip>
using namespace std;

LONG mass[10];
int length = sizeof(mass) / sizeof(mass[0]);

void thread_1()
{
	srand(time(NULL)); LONG random;

	for (int j = 0; j < 3; j++) {
		HANDLE hMutex_1 = OpenMutex(SYNCHRONIZE, FALSE, _T("MyMutex"));
		if (hMutex_1 == NULL)
			cout << "Open mutex01 failed" << GetLastError() << endl;

		WaitForSingleObject(hMutex_1, INFINITE);

		for (int i = 0; i < length; i++)
		{
			random = rand() % 10 - 5;
			InterlockedExchange(mass + i, random);
		}

		Sleep(1000);
		cout << setw(8) << "original";
		for (int i = 0; i < length; i++)
		{
			cout << setw(6) << mass[i];
		}
		cout << endl;

		ReleaseMutex(hMutex_1);
		CloseHandle(hMutex_1);
	}
}

void thread_2()
{
	for (int j = 0; j < 3; j++) {
	
		HANDLE hMutex_2 = OpenMutex(SYNCHRONIZE, FALSE, _T("MyMutex"));
		if (hMutex_2 == NULL)
			cout << "Open mutex02 failed" << GetLastError() << endl;

		WaitForSingleObject(hMutex_2, INFINITE);

		if (mass[0] == 0) {
			LONG firstPositive;
			for (int k = 1; k < length; k++) {
				if (mass[k] > 0) {
					firstPositive = mass[k]; break;
				}
			}
			mass[0] = firstPositive;
		}
		
		Sleep(1000);
		cout << setw(8) << "altered";
		for (int i = 0; i < length; i++) {
			cout << setw(6) << mass[i];
		}
		cout << endl;

		ReleaseMutex(hMutex_2);
		CloseHandle(hMutex_2);
	}
}

void thread_3()
{
	for (int j = 0; j < 3; j++) {
	
		HANDLE hMutex_3 = OpenMutex(SYNCHRONIZE, FALSE, _T("MyMutex"));
		if (hMutex_3 == NULL)
			cout << "Open mutex03 failed" << GetLastError() << endl;

		WaitForSingleObject(hMutex_3, INFINITE);

		int positiveCount;
		for (int k = 0; k < length; k++) {
			if (mass[k] > 0) {
				positiveCount += 1;
			}
		}

		Sleep(1000);

		cout << "positive count: " << positiveCount << endl << endl;

		positiveCount = 0;

		ReleaseMutex(hMutex_3);
		CloseHandle(hMutex_3);
	}
}

int main()
{
	HANDLE hMutex = CreateMutex(NULL, FALSE, _T("MyMutex"));
	if (hMutex == NULL)
		cout << "Create mutex failed" << GetLastError() << endl;

	HANDLE hThread_1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_1, NULL, 0, NULL);
	if (hThread_1 == NULL) return GetLastError();

	HANDLE hThread_2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_2, NULL, 0, NULL);
	if (hThread_2 == NULL) return GetLastError();

	HANDLE hThread_3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_3, NULL, 0, NULL);
	if (hThread_3 == NULL) return GetLastError();

	cin.get();

	CloseHandle(hMutex);
	CloseHandle(hThread_1);
	CloseHandle(hThread_2);
	CloseHandle(hThread_3);
	return 0;
}