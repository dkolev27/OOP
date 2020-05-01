#pragma once
class BooksData
{
public:
	//Big four
	BooksData();
	BooksData(const BooksData& other);
	BooksData(const char* author, const char* title, const char* genre, const char* short_discription ,unsigned year, const char* keywords, float rating, int bibliotheque_unique_number);
	BooksData& operator=(const BooksData& other);
	~BooksData();

	void input();
	void print();

private:
	//Fields
	char* author;
	char* title;
	char* genre;
	char* short_discription;
	unsigned year;
	char* keywords;
	float rating;
	int bibliotheque_unique_number;

	//Helper methods
	void clear();
	void copy(const BooksData& other);
};

