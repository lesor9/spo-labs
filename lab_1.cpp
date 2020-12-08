#include "Header.h"
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
	FileClass() : BytesRead(0), BytesWritten(0) {}//default constructor
	~FileClass() { CloseHandle(hFile); }		 //destructor

	bool Create(LPCTSTR);							
	void Write(BookUnit&);
	void Read(int);

};

bool FileClass::Create(LPCTSTR Name) {
	FileName = Name;

	hFile = CreateFile(
		Name,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	return (hFile == INVALID_HANDLE_VALUE) ? false : true;
}

void FileClass::Write(BookUnit& book) {
	WriteFile(hFile, &book, sizeof(book), &BytesWritten, NULL);
	FlushFileBuffers(hFile);
}

void FileClass::Read(int year) {
	SetFilePointer(hFile, 0, 0, FILE_BEGIN);

	while (ReadFile(hFile, &book, sizeof(book), &BytesRead, NULL) && BytesRead != 0) {
		if (book.date >= year)
			cout << setw(15) << book.name << setw(30) << book.date << endl;
	}
}

int main()
{
	int menu();
	void add(FileClass&);
	void read(FileClass&);
	void sort(FileClass&);
	FileClass file;

	LPCTSTR FileName = "NEW.FILE.txt";
	(file.Create(FileName)) ? cout << "Create/open file: success \n" :
							  cout << "Create/open file: failure \n";
	while (true) {
		switch (menu())
		{
		case 1: add(file);  break;
		case 2: read(file); break;
		case 3: sort(file); break;
		case 4: return 0;
		default: cout << "between 1-4 \n";
		}
		system("pause");
		system("cls");
	}

	//system("pause");
	return 0;
}

void add(FileClass& file) {
	BookUnit book;
	cin.ignore();
	cout << "Book name: "; getline(cin, book.name);
	cout << "Book date: "; cin >> book.date;
	file.Write(book);

}

void read(FileClass& file) {
	file.Read(0);
}

void sort(FileClass& file) {
	int year;
	cout << "Year to sort list after \n";
	cin >> year;
	file.Read(year);
}

int menu() {
	int answer;
	cout << "1. Add a book to the list \n";
	cout << "2. Read book list from file \n";
	cout << "3. Read list after selected year \n";
	cout << "4. Exit \n";
	cin >> answer;
	return answer;
}