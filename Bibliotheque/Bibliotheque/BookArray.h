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
	void saveFile(const char* filepath); //Запазва на ново място
	void saveFile(); //Запазва на същото място
	void printAll() const;

	void close();

	//Getter and Setter
	char* getFilepath();
	void setFilepath(const char* filepath);
	 
private:
	BooksData** arr; //Контейнер за книги
	int currentSize; 
	int currentCount; 

	char* filepath; //да запазваме вътре името на файла, който сме отворили

	//Helpers
	void copy(const BookArray& other);
	void clear();
	void init();
};

