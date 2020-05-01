#pragma once
#include <iostream>
class BooksData
{
public:
	//Big four + param. c-tor
	BooksData();
	BooksData(const BooksData& other);
	BooksData(const char* author, const char* title, const char* genre, const char* short_discription, unsigned year, const char* keywords, float rating, int bibliotheque_unique_number);
	BooksData& operator=(const BooksData& other);
	~BooksData();

	void input(); 
	void print();

	friend std::istream& operator>>(std::istream& in, BooksData& book); 
	friend std::ostream& operator<<(std::ostream& out, BooksData& book); 

	//Setters & Getters
	void setAuthor(const char* author);
	char* getAuthor() const;
	void setTitle(const char* title);
	char* getTitle() const;
	void setGenre(const char* genre);
	char* getGenre() const;
	void setShortDiscription(const char* short_discription);
	char* getShortDiscription() const;
	void setYear(unsigned year);
	unsigned getYear() const;
	void setKeywords(const char* keywords);
	char* getKeywords() const;
	void setRating(float rating);
	float getRating() const;
	void setBibliothequeUniqueNumber(int bibliotheque_unique_number);
	int getBibliothequeUniqueNumberr() const;

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

