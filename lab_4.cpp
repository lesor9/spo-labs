#include <iostream>
#include <windows.h>
#include <time.h>
#include <iomanip>

using namespace std;

LONG mass[10];
int length = sizeof(mass) / sizeof(mass[0]);

void thread_1()
{
	srand(time(NULL));
	LONG random;

	while (true)
	{
		Sleep(1000);
		for (int i = 0; i < length; i++)
		{
			random = rand() % 300 - 150;
			InterlockedExchange(mass + i, random);
		}

		for (int i = 0; i < length; i++)
		{
			cout << setw(6) << mass[i];
		}
		cout << endl;
	}
}

void thread_2()
{
	while (true)
	{
		for (int i = 0; i < length; i++)
		{
			if (i % 2 == 0)
				InterlockedExchange(mass + i, 0);
		}
	}
}

int main()
{
	HANDLE hThread_1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_1, NULL, NULL, 0);
	HANDLE hThread_2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_2, NULL, NULL, 0);
	
	if (hThread_1 == NULL || hThread_2 == NULL) {
		cout << "CREATE THREAD: failure" << endl;
		return 1;
	}

	cin.get();

	TerminateThread(hThread_1, 0);
	TerminateThread(hThread_2, 0);
	CloseHandle(hThread_1);
	CloseHandle(hThread_2);
	return 0;
}