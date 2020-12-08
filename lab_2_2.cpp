#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct BookUnit
{
	string name;
	int date;
};

int main(int argc, char** argv) {

	cout << "amount of arguments: " << argc << endl;
	cout << "first frgument: " << argv[0] << endl << "second argument: " << argv[1] << endl;
	
	BookUnit book;
	DWORD BytesRead;
	DWORD BytesWritten;
	HANDLE hFile = CreateFile(
		/*"C:\\Users\\user1\\source\\repos\\LAB_2_demo\\Debug\\NEW.FILE.txt"*/ 
		"NEW.FILE.txt",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	
	(hFile != INVALID_HANDLE_VALUE) ?
		cout << "OPEN FILE: 1 \n" << endl:
		cout << "OPEN FILE: 0 \n" << endl;

	SetFilePointer(hFile,
		(atoi(argv[1]) - 1) * sizeof(book), NULL, FILE_BEGIN);
	
	ReadFile(hFile, &book, sizeof(book), &BytesRead, NULL) ?
		cout << "READ FILE: 1 \n" << endl : cout << "READ FILE: 0 \n" << endl;
	SetFilePointer(hFile, (-1) * (int)sizeof(book), NULL, FILE_CURRENT);

	cout << "	change: \n" << setw(15) << book.name << setw(30) << book.date << endl;
	cout << "	to: \n";
	cout << "book name: ";
	getline(cin, book.name);
	cout << "book date: "; cin >> book.date;
	cout << endl;

	WriteFile(hFile, &book, sizeof(book), &BytesWritten, NULL) ?
		cout << "WRITE FILE: 1 \n":
		cout << "WRITE FILE: 0 \n";

	FlushFileBuffers(hFile);
	
	system("pause");
	return 0;
}