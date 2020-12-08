#include <iostream>
#include <windows.h>
#include <time.h>
#include <iomanip>
using namespace std;

HANDLE hSemaphore;


void thread01(int** arg){
	int* mass = arg[0];  //распаковываю указатель на массив и на его размер
	int length = *arg[1];

	for (int i = 0; i < length; i++) {
		WaitForSingleObject(hSemaphore, INFINITE); //беру флаг
		
		Sleep(1000); srand(time(NULL));
		mass[i] = rand() % 501;
		
		ReleaseSemaphore(hSemaphore, 1, NULL); //отдаю
	}
}

void thread02(int** arg){
	int* mass = arg[0];
	int length = *arg[1];
	int oddCount = 0;

	for (int i = 0; i < length; i++) {
		WaitForSingleObject(hSemaphore, INFINITE); //беру
		cout << "mas[" << i << "]= " << mass[i] << endl;

		if (mass[i] % 2 == 1)
			oddCount++;

		ReleaseSemaphore(hSemaphore, 1, NULL); //отдаю
	}
	cout << "odd elements total: " << oddCount << endl;
}

int main()
{
	int n = 0;
	cout << "array size: "; cin >> n; cout << endl;
	int* mass = new int[n];

	int* argument[2] = { mass, &n }; //пакую указатель на массив и на его размер в один аргумент
	

	hSemaphore = CreateSemaphore(NULL, 1, 1, "MySemaphore"); //начальное 1, максимум 1
	if (hSemaphore == NULL) cout << "CREATE SEMAPHORE: failure"
		<< GetLastError() << endl;

	HANDLE hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, argument, 0, NULL);
	if (hTh01 == NULL) return GetLastError();

	HANDLE hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, argument, 0, NULL);
	if (hTh02 == NULL) return GetLastError();

	cin.ignore();
	cin.get();
	
	CloseHandle(hSemaphore);
	CloseHandle(hTh01);
	CloseHandle(hTh02);
	return 0;
}