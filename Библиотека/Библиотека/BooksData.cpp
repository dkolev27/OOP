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
	std::cout << "Enter the author of the book: ";
	std::cin.getline(author, '/0');
	std::cout << this->author << std::endl;
	std::cout << "Enter the title of the book: ";
	std::cin.getline(title, '/0');
	std::cout << this->title << std::endl;
	std::cout << "Enter the genre of the book: ";
	std::cin.getline(genre, '/0');
	std::cout << this->genre << std::endl;
	std::cout << "Enter a short discription about the book: ";
	std::cin.getline(short_discription, '/0');
	std::cout << this->short_discription << std::endl;
	std::cout << "When was the book published? ";
	std::cin >> year;
	std::cout << this->year << std::endl;
	std::cout << "Enter some keywords related to the book: ";
	std::cin.getline(keywords, '/0');
	std::cout << this->keywords << std::endl;
	std::cout << "Enter the rating of the book: ";
	std::cin >> rating;
	std::cout << this->rating << std::endl;
	std::cout << "Enter the unique bibliotheque number: ";
	std::cin >> bibliotheque_unique_number;
	std::cout << this->bibliotheque_unique_number << std::endl;
}

void BooksData::print()
{
	std::cout
		<< author << std::endl
		<< title << std::endl
		<< genre << std::endl
		<< short_discription << std::endl
		<< year << std::endl
		<< keywords << std::endl
		<< rating << std::endl
		<< bibliotheque_unique_number << std::endl;
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
	this-> bibliotheque_unique_number = other.bibliotheque_unique_number;
}
