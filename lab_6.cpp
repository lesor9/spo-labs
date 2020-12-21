#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <time.h>
#include <iomanip>
using namespace std;

HANDLE hSemaphore;


void thread01(int** arg){
	int* mass = arg[0];
	int length = *arg[1];

	for (int i = 0; i < length; i++) {
		WaitForSingleObject(hSemaphore, INFINITE);
		
		Sleep(1000); srand(time(NULL));
		mass[i] = rand() % 501;
		
		ReleaseSemaphore(hSemaphore, 1, NULL);
	}
}

void thread02(int** arg){
	int* mass = arg[0];
	int length = *arg[1];
	int oddCount = 0;

	for (int i = 0; i < length; i++) {
		WaitForSingleObject(hSemaphore, INFINITE);
		cout << "mas[" << i << "]= " << mass[i] << endl;

		if (mass[i] % 2 == 1)
			oddCount++;

		ReleaseSemaphore(hSemaphore, 1, NULL);
	}
	cout << endl << "odd elements total: " << oddCount << endl << endl;
	Sleep(1000);
}

void thread03(int** arg){
	int* mass = arg[0];
	int length = *arg[1];
	int evenCount = 0;

	for (int i = 0; i < length; i++) {
		WaitForSingleObject(hSemaphore, INFINITE);

		if (mass[i] % 2 == 0)
			evenCount++;

		ReleaseSemaphore(hSemaphore, 1, NULL);
	}
	
	cout << "even elements total: " << evenCount << endl << endl;
	Sleep(1000);
}

void thread04(int** arg){
	int* mass = arg[0];
	int length = *arg[1];
	int maxOddNumber = 0;

	for (int i = 0; i < length; i++) {
		WaitForSingleObject(hSemaphore, INFINITE);

		if (mass[i] % 2 == 1 && mass[i] > maxOddNumber)
			maxOddNumber = mass[i];

		ReleaseSemaphore(hSemaphore, 1, NULL);
	}
	
	cout << "maxOddNumber: " << maxOddNumber << endl << endl;
}

int main()
{
	int n = 3;
	cout << "array size: " << n << endl;
	int* mass = new int[n];

	int* argument[2] = { mass, &n };
	

	hSemaphore = CreateSemaphore(NULL, 1, 1, _T("MySemaphore"));
	if (hSemaphore == NULL) cout << "CREATE SEMAPHORE: failure"
		<< GetLastError() << endl;

	HANDLE hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, argument, 0, NULL);
	if (hTh01 == NULL) return GetLastError();

	HANDLE hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, argument, 0, NULL);
	if (hTh02 == NULL) return GetLastError();

    HANDLE hTh03 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread03, argument, 0, NULL);
	if (hTh03 == NULL) return GetLastError();
	
	HANDLE hTh04 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread04, argument, 0, NULL);
	if (hTh04 == NULL) return GetLastError();

	cin.ignore();
	cin.get();
	
	CloseHandle(hSemaphore);
	CloseHandle(hTh01);
	CloseHandle(hTh02);
    CloseHandle(hTh03);
	CloseHandle(hTh04);
	return 0;
}