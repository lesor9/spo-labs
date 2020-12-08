#include <iostream>
#include <windows.h>
using namespace std;

void FirstThread(int& n){
	while (true) {
		n++;
		Sleep(100); 
	}
	return;
}

void SecondThread(int& n) {
	while (true) {
		n++;
		Sleep(200);
	}
	return;
}

void ThirdThread(int& n) {
	while (true) {
		n++;
		Sleep(300);
	}
	return;
}

void display(int& first, int& second, int& third) {
	cout << "First: " << first << endl;
	cout << "Second: " << second << endl;
	cout << "Third: " << third << endl;
}

void DeleteMaxThread(int& first, int& second, int& third,
					 HANDLE& hfirst, HANDLE& hsecond, HANDLE& hthird) {
	int max;
	max = max(first, second);
	max = max(max, third);
	
	max == first ? TerminateThread(hfirst, 0) :
		max == second ? TerminateThread(hsecond, 0) :
		TerminateThread(hthird, 0);
}

int menu() {
	int answer;
	cout << "1. Display states of all threads \n";
	cout << "2. Delete max thread \n";
	cout << "3. Exit \n";
	cin >> answer;
	return answer;
}

int main()
{
	HANDLE hFirstThread, hSecondThread, hThirdThread;
	DWORD idFirstThread, idSecondThread, idThirdThread;
	int first = 0, second = 0, third = 0;

	hFirstThread = CreateThread(
		NULL, 0,
		(LPTHREAD_START_ROUTINE)FirstThread,
		&first, 0,
		&idFirstThread);

	hSecondThread = CreateThread(
		NULL, 0,
		(LPTHREAD_START_ROUTINE)SecondThread,
		&second, 0,
		&idSecondThread);

	CreateThread(
		NULL, 0,
		(LPTHREAD_START_ROUTINE)ThirdThread,
		&third, 0,
		&idThirdThread);

	while (true) {
		switch (menu()) {
		case 1: display(first, second, third); break;
		case 2: DeleteMaxThread(first, second, third,
								hFirstThread, hSecondThread, hThirdThread); break;
		case 3: return 0;
		default: cout << "between 1-2 \n";
		}
		system("pause");
		system("cls");
	}

	CloseHandle(hFirstThread);
	CloseHandle(hSecondThread);
	CloseHandle(hThirdThread);
	return 0;
}