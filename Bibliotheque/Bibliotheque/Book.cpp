#include <iostream>
#include <cstring>
#include <string>
#include "Book.h"

using namespace std;

Book::Book(const string& author, const string& title, const string& genre, const string& short_discription, unsigned year, const string& keywords, float rating, int bibliotheque_unique_number)
{
	this->author = author;
	this->title = title;
	this->genre = genre;
	this->short_discription = short_discription;
	this->year = year;
	this->keywords = keywords;
	this->rating = rating;
	this->bibliotheque_unique_number = bibliotheque_unique_number;
}

Book::Book(const Book& other)
{
	copy(other);
}

Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

Book::~Book()
{
	clear();
}

void Book::input()
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

void Book::print()
{
	if (author.size())
	{
		std::cout << title << " - " << author << " - " << genre << " - " << bibliotheque_unique_number << std::endl;
	}
	else
	{
		std::cout << "NO BOOK!" << std::endl;
	}
}

void Book::setAuthor(const string& author)
{
	this->author = author;
}

string Book::getAuthor() const
{
	return author;
}

void Book::setTitle(const string& title)
{
	this->title = title;
}

string Book::getTitle() const
{
	return title;
}

void Book::setGenre(const string& genre)
{
	this->genre = genre;
}

string Book::getGenre() const
{
	return genre;
}

void Book::setShortDiscription(const string& short_discription)
{
	this->short_discription = short_discription;
}

string Book::getShortDiscription() const
{
	return short_discription;
}

void Book::setYear(unsigned year)
{
	this->year = year;
}

unsigned Book::getYear() const
{
	return year;
}

void Book::setKeywords(const string& keywords)
{
	this->keywords = keywords;
}

string Book::getKeywords() const
{
	return keywords;
}

void Book::setRating(float rating)
{
	this->rating = rating;
}

float Book::getRating() const
{
	return rating;
}

void Book::setBibliothequeUniqueNumber(int bibliotheque_unique_number)
{
	this->bibliotheque_unique_number = bibliotheque_unique_number;
}

int Book::getBibliothequeUniqueNumberr() const
{
	return bibliotheque_unique_number;
}

void Book::clear()
{
	author.clear();
	title.clear();
	genre.clear();
	short_discription.clear();	
	keywords.clear();
}

void Book::copy(const Book& other)
{
	this->author = other.author;
	this->title = other.title;
	this->genre = other.genre;
	this->short_discription = other.short_discription;
	this->year = other.year;
	this->keywords = other.keywords;
	this->rating = other.rating;
	this->bibliotheque_unique_number = other.bibliotheque_unique_number;
}

std::istream& operator>>(std::istream& in, Book& book)
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

std::ostream& operator<<(std::ostream& out, Book& book)
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

bool booksYearCmp(const Book* a, const Book* b)
{
	return a->getYear() > b->getYear();
}

bool booksAuthorCmp(const Book* a, const Book* b)
{
	return a->getAuthor() > b->getAuthor();
}

bool booksTitleCmp(const Book* a, const Book* b)
{
	return a->getTitle() > b->getTitle();
}

bool booksRatingCmp(const Book* a, const Book* b)
{
	return a->getRating() > b->getRating();
}
