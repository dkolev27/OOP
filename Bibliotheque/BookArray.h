#pragma once
#include "Book.h"
#include <string>
#include <vector>

using namespace std;

class BookArray
{
public:
	BookArray();
	BookArray(const BookArray& other);
	BookArray& operator=(const BookArray& other);
	~BookArray();

	void addBook(const Book& book);
	void openFile(const string& filepath);
	void saveFile(const string& filepath); //������� �� ���� �����
	void saveFile(); //������� �� ������ �����
	void printAll() const;

	void close();

	//Getter and Setter
	string getFilepath() const;
	void setFilepath(const string& filepath);
	 
private:
	std::vector<Book*> books;

	string filepath; //�� ��������� ����� ����� �� �����, ����� ��� ��������

	//Helpers
	void copy(const BookArray& other);
	void clear();
};

