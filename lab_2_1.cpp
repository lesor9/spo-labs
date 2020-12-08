#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>

using namespace std;

struct BookUnit
{
	string name;
	int date;
};

class FileClass
{
private:
	BookUnit book;
	DWORD BytesRead;
	DWORD BytesWritten;
	LPCTSTR FileName;
	HANDLE hFile;

public:
	FileClass() : BytesRead(0), BytesWritten(0) {}

	~FileClass() {CloseHandle(hFile);} //крашит

	bool Open(LPCTSTR);
	int Read();

};

bool FileClass::Open(LPCTSTR Name) {
	FileName = Name;

	hFile = CreateFile(
		Name,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	return (hFile == INVALID_HANDLE_VALUE) ? false : true;
}

int FileClass::Read() {
	SetFilePointer(hFile, 0, 0, FILE_BEGIN);
	int count = 0;

	while (ReadFile(hFile, &book, sizeof(book), &BytesRead, NULL) && BytesRead != 0) {
			cout << setw(15) << book.name << setw(30) << book.date << endl;
			count++;
	}
	return count;
}

class ProcessClass {
private:
	STARTUPINFO StartupInfo;
	PROCESS_INFORMATION ProcInfo;

public:
	ProcessClass() {
		ZeroMemory(&StartupInfo, sizeof(StartupInfo));
		ZeroMemory(&ProcInfo, sizeof(ProcInfo));
		StartupInfo.cb = sizeof(StartupInfo);
	}

	~ProcessClass() {
		CloseHandle(ProcInfo.hProcess);
		CloseHandle(ProcInfo.hThread);
	}

	bool Create(char* AppName) {
		return 
			(CreateProcess(NULL, AppName, NULL, NULL, FALSE, 0,
			NULL, NULL, &StartupInfo, &ProcInfo)) ?
		true : false;
	}

	PROCESS_INFORMATION& get_procinf() {
		return ProcInfo;
	}
};


int main() {
	char number[2];
	FileClass file;
	ProcessClass process;

	cout << "OPEN FILE: " << file.Open("NEW.FILE.txt") << '\n'<< endl;
	
	cout << "records found: " << file.Read() << endl;
	cout << "number of record to modify: "; cin >> number;
	cout << endl;

	char AppName[] = /*"C:\\Users\\user1\\source\\repos\\LAB_2_demo_part_2\\Debug\\LAB_2_demo_part_2.exe "*/
					"LAB_2_demo_part_2.exe ";
	strcat(AppName, number);

	cout << "CREATE PROCESS: " << process.Create(AppName) << '\n' << endl;

	WaitForSingleObject(process.get_procinf().hProcess, INFINITE);
	file.Read();

	system("pause");
	return 0;
}
