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
	void saveFile(const string& filepath); //Запазва на ново място
	void saveFile(); //Запазва на същото място
	void printAll() const;
	void printView() const;
	Book* getByISBN(int isbn) const;
	Book* getByTitle(const string& title) const;
	Book* getByAuthor(const string& author) const;
	Book* getByTag(const string& tag) const;
	bool removeByISBN(int isbn);
	void booksSort(bool (*cmpFunction)(const Book* a, const Book* b), bool desc = false);
	

	void close();

	//Getter and Setter
	string getFilepath() const;
	void setFilepath(const string& filepath);
	 
private:
	std::vector<Book*> books;

	string filepath; //да запазваме вътре името на файла, който сме отворили

	//Helpers
	void copy(const BookArray& other);
	void clear();
};

