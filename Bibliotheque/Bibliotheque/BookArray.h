#pragma once
#include "BooksData.h"
class BookArray
{
public:
	BookArray();
	BookArray(const BookArray& other);
	BookArray& operator=(const BookArray& other);
	~BookArray();

	void addBook(const BooksData& book);
	void openFile(const char* filepath);
	void saveFile(const char* filepath); //������� �� ���� �����
	void saveFile(); //������� �� ������ �����
	void printAll() const;

	void close();

	//Getter and Setter
	char* getFilepath();
	void setFilepath(const char* filepath);
	 
private:
	BooksData** arr; //��������� �� �����
	int currentSize; 
	int currentCount; 

	char* filepath; //�� ��������� ����� ����� �� �����, ����� ��� ��������

	//Helpers
	void copy(const BookArray& other);
	void clear();
	void init();
};

