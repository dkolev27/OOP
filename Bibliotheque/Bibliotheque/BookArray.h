#pragma once
#include "Book.h"
#include <string>
#include <vector>

using namespace std;

class BookArray
{
public:
	// Голяма четворка
	BookArray();
	BookArray(const BookArray& other);
	BookArray& operator=(const BookArray& other);
	~BookArray();

	// Методи
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
	void booksSort(bool (*cmpFunction)(const Book* a, const Book* b), bool desc = false); // Тази функция не е измислена и писана от мен, както и цялата логика, свързана с нея
	void close();

	// Селектори и мутатори
	string getFilepath() const;
	int getCount() const;
	void setFilepath(const string& filepath);
	 
private:
	// Член данни
	vector<Book*> books;
	string filepath; //да запазваме вътре името на файла, който сме отворили

	// Помощни функции
	void copy(const BookArray& other);
	void clear();
};

