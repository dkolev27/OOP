#include <fstream>
#include "BookArray.h"

BookArray::BookArray()
{}

BookArray::BookArray(const BookArray& other)
{
	copy(other);
}

BookArray& BookArray::operator=(const BookArray& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

BookArray::~BookArray()
{
	clear();
}

void BookArray::addBook(const Book& book)
{
	books.push_back(new Book(book));
}

void BookArray::openFile(const string& filepath)
{
	std::ifstream file(filepath);
	if (file)
	{
		clear();
		setFilepath(filepath); 
		while (!file.eof())
		{
			Book book;
			file >> book; 
			if (book.getAuthor().size() == 0) 
			{
				if (books.size() == 0)
				{
					std::cout << "The file is empty!" << std::endl;
				}
				break;
			}
			addBook(book);
		}

		file.close();
	}
	else
	{
		std::cout << "Can't open file!" << std::endl;
	}
}

void BookArray::saveFile(const string& filepath)
{
	std::ofstream file(filepath);
	if (file)
	{
		for (size_t i = 0; i < books.size(); i++)
		{
			file << *books[i];
		}

		file.close();
		std::cout << "Succsessfully saved!" << std::endl;
	}
	else
	{
		std::cout << "Can't save file!" << std::endl;
	}
}

void BookArray::saveFile() // За да мога да напиша save без да пиша името на файла
{
	saveFile(filepath);
}

void BookArray::printAll() const
{
	if (books.size())
	{
		for (size_t i = 0; i < books.size(); i++)
		{
			books[i]->print();
		}
	}
	else
	{
		cout << "No books to be shown!" << endl;
	}
}

void BookArray::printView() const
{
	if (books.size())
	{
		for (size_t i = 0; i < books.size(); i++)
		{
			cout << *books[i] << endl;
		}
	}
	else
	{
		cout << "No books to be shown!" << endl;
	}
}

Book* BookArray::getByISBN(int isbn) const
{
	for (size_t i = 0; i < books.size(); i++)
	{
		if (isbn == books[i]->getBibliothequeUniqueNumberr())
		{
			return books[i];
		}
	}
	return nullptr;
}

bool BookArray::removeByISBN(int isbn)
{
	for (size_t i = 0; i < books.size(); i++)
	{
		if (isbn == books[i]->getBibliothequeUniqueNumberr())
		{
			delete books[i];
			books.erase(books.begin() + i);
			return true;
		}
	}
	return false;
}

void BookArray::booksSort(bool (*cmpFunction)(const Book* a, const Book* b))
{
	//Bubble sort
	for (size_t i = 0; i < books.size(); i++)
	{
		for (size_t j = 0; j < books.size() - 1; j++)
		{
			Book* a = books[j];
			Book* b = books[j + 1];
			if (cmpFunction(a, b))
			{
				Book* book = books[j];
				books[j] = books[j + 1];
				books[j + 1] = book;
			}
		}
	}
}

void BookArray::close()
{
	clear();
}

string BookArray::getFilepath() const
{
	return filepath;
}

void BookArray::setFilepath(const string& filepath)
{
	this->filepath = filepath;
}

void BookArray::copy(const BookArray& other)
{
	for (size_t i = 0; i < books.size(); i++)
	{
		books.push_back(new Book(*other.books[i])) ;
	}
	this->filepath = other.filepath;
}

void BookArray::clear()
{
	for (size_t i = 0; i < books.size(); i++)
	{
		delete books[i];
	}
	books.clear();
	filepath = "";
}

bool yearCmp(const Book* a, const Book* b) 
{
	return a->getYear() < b->getYear();
}
