#include <iostream>
#include <cstring>
#include "BooksData.h"

BooksData::BooksData()
{
	author = nullptr;
	title = nullptr;
	genre = nullptr;
	short_discription = nullptr;
	year = 0;
	keywords = nullptr;
	rating = 0;
	bibliotheque_unique_number = 0;
}

BooksData::BooksData(const BooksData& other)
{
	copy(other);
}

BooksData::BooksData(const char* author, const char* title, const char* genre, const char* short_discription, unsigned year, const char* keywords, float rating, int bibliotheque_unique_number)
{
	this->author = new char[strlen(author) + 1];
	strcpy(this->author, author);
	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
	this->genre = new char[strlen(genre) + 1];
	strcpy(this->genre, genre);
	this->short_discription = new char[strlen(short_discription) + 1];
	strcpy(this->short_discription, short_discription);
	this->keywords = new char[strlen(keywords) + 1];
	strcpy(this->keywords, keywords);

	this->year = year;
	this->rating = rating;
	this->bibliotheque_unique_number = bibliotheque_unique_number;
}

BooksData& BooksData::operator=(const BooksData& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

BooksData::~BooksData()
{
	clear();
}

void BooksData::input()
{
	const int MAX_LINE_LEN = 128;
	char line[MAX_LINE_LEN];

	std::cout << "Enter the author of the book: ";
	std::cin.getline(line, MAX_LINE_LEN);
	setAuthor(line);

	std::cout << "Enter the title of the book: ";
	std::cin.getline(line, MAX_LINE_LEN);
	setTitle(line);

	std::cout << "Enter the genre of the book: ";
	std::cin.getline(line, MAX_LINE_LEN);
	setGenre(line);

	std::cout << "Enter a short discription about the book: ";
	std::cin.getline(line, MAX_LINE_LEN);
	setShortDiscription(line);

	int year;
	std::cout << "When was the book published? ";
	std::cin >> year;
	setYear(year);
	std::cin.getline(line, MAX_LINE_LEN);

	std::cout << "Enter some keywords related to the book: ";
	std::cin.getline(line, MAX_LINE_LEN);
	setKeywords(line);
	
	float rating;
	std::cout << "Enter the rating of the book: ";
	std::cin >> rating;
	setRating(rating);
	std::cin.getline(line, MAX_LINE_LEN);

	int bibliotheque_unique_number;
	std::cout << "Enter the unique bibliotheque number: ";
	std::cin >> bibliotheque_unique_number;
	setBibliothequeUniqueNumber(bibliotheque_unique_number);
	std::cin.getline(line, MAX_LINE_LEN);
}

void BooksData::print()
{
	if (author)
	{
		std::cout << title << " - " << author << " - " << genre << " - " << bibliotheque_unique_number << std::endl;
	}
	else
	{
		std::cout << "NO BOOK!" << std::endl;
	}
}

void BooksData::setAuthor(const char* author)
{
	if (this->author)
	{
		delete[] this->author;
	}
	this->author = new char[strlen(author) + 1];
	strcpy(this->author, author);
}

char* BooksData::getAuthor() const
{
	return author;
}

void BooksData::setTitle(const char* title)
{
	if (this->title)
	{
		delete[] this->title;
	}
	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
}

char* BooksData::getTitle() const
{
	return title;
}

void BooksData::setGenre(const char* genre)
{
	if (this->genre)
	{
		delete[] this->genre;
	}
	this->genre = new char[strlen(genre) + 1];
	strcpy(this->genre, genre);
}

char* BooksData::getGenre() const
{
	return genre;
}

void BooksData::setShortDiscription(const char* short_discription)
{
	if (this->short_discription)
	{
		delete[] this->short_discription;
	}
	this->short_discription = new char[strlen(short_discription) + 1];
	strcpy(this->short_discription, short_discription);
}

char* BooksData::getShortDiscription() const
{
	return short_discription;
}

void BooksData::setYear(unsigned year)
{
	this->year = year;
}

unsigned BooksData::getYear() const
{
	return year;
}

void BooksData::setKeywords(const char* keywords)
{
	if (this->keywords)
	{
		delete[] this->keywords;
	}
	this->keywords = new char[strlen(keywords) + 1];
	strcpy(this->keywords, keywords);
}

char* BooksData::getKeywords() const
{
	return keywords;
}

void BooksData::setRating(float rating)
{
	this->rating = rating;
}

float BooksData::getRating() const
{
	return rating;
}

void BooksData::setBibliothequeUniqueNumber(int bibliotheque_unique_number)
{
	this->bibliotheque_unique_number = bibliotheque_unique_number;
}

int BooksData::getBibliothequeUniqueNumberr() const
{
	return bibliotheque_unique_number;
}

void BooksData::clear()
{
	delete[] author;
	author = nullptr;
	delete[] title;
	title = nullptr;
	delete[] genre;
	genre = nullptr;
	delete[] short_discription;
	short_discription = nullptr;
	delete[] keywords;
	keywords = nullptr;
}

void BooksData::copy(const BooksData& other)
{
	this->author = new char[strlen(other.author) + 1];
	strcpy(this->author, other.author);
	this->title = new char[strlen(other.title) + 1];
	strcpy(this->title, other.title);
	this->genre = new char[strlen(other.genre) + 1];
	strcpy(this->genre, other.genre);
	this->short_discription = new char[strlen(other.short_discription) + 1];
	strcpy(this->short_discription, other.short_discription);
	this->keywords = new char[strlen(other.keywords) + 1];
	strcpy(this->keywords, other.keywords);

	this->year = other.year;
	this->rating = other.rating;
	this->bibliotheque_unique_number = other.bibliotheque_unique_number;
}

std::istream& operator>>(std::istream& in, BooksData& book)
{
	const int MAX_LINE_LEN = 128;
	char line[MAX_LINE_LEN];

	do //Skips empty lines in file
	{
		in.getline(line, MAX_LINE_LEN); //Read the author from file 
		if (in.eof())
		{
			return in;
		}
	} while (strlen(line) == 0);
	book.setAuthor(line);

	in.getline(line, MAX_LINE_LEN); //Read the title from file 
	book.setTitle(line);

	in.getline(line, MAX_LINE_LEN); //Read the genre from file 
	book.setGenre(line);

	in.getline(line, MAX_LINE_LEN); //Read the short discription from file 
	book.setShortDiscription(line);

	int year;
	in >> year;
	book.setYear(year);
	in.getline(line, MAX_LINE_LEN); //Skips \0 after the year

	in.getline(line, MAX_LINE_LEN); //Read the keywords from file 
	book.setKeywords(line);

	float rating;
	in >> rating;
	book.setRating(rating);
	in.getline(line, MAX_LINE_LEN); //Skips \0 after the rating

	int bibliotheque_unique_number;
	in >> bibliotheque_unique_number;
	book.setBibliothequeUniqueNumber(bibliotheque_unique_number);
	in.getline(line, MAX_LINE_LEN); //Skips \0 after the bibliotheque_unique_number

	return in;
}

std::ostream& operator<<(std::ostream& out, BooksData& book)
{
	out
		<< book.author << std::endl
		<< book.title << std::endl
		<< book.genre << std::endl
		<< book.short_discription << std::endl
		<< book.year << std::endl
		<< book.keywords << std::endl
		<< book.rating << std::endl
		<< book.bibliotheque_unique_number << std::endl;
	return out;
}
