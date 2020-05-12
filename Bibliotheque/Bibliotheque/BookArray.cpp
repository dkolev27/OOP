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

Book* BookArray::getByTitle(const string& title) const
{
	for(size_t i = 0; i < books.size(); i++)
	{
		if (title == books[i]->getTitle())
		{
			return books[i];
		}
	}
	return nullptr;
}

Book* BookArray::getByAuthor(const string& author) const
{
	for (size_t i = 0; i < books.size(); i++)
	{
		if (author == books[i]->getAuthor())
		{
			return books[i];
		}
	}
	return nullptr;
}

Book* BookArray::getByTag(const string& tag) const
{
	for (size_t i = 0; i < books.size(); i++)
	{
		string keywords = books[i]->getKeywords();
		size_t pos = keywords.find(tag);
		// (намерено     (в начало || space преди намереното  ) && (стига до края                  || има запетая след намереното))   
		if (pos != -1 && (pos == 0 || keywords[pos - 1] == ' ') && (pos + tag.size() == tag.size() || keywords[pos + tag.size()] == ','))
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

void BookArray::booksSort(bool (*cmpFunction)(const Book* a, const Book* b), bool desc)
{
	//Bubble sort
	for (size_t i = 0; i < books.size(); i++)
	{
		for (size_t j = 0; j < books.size() - 1; j++)
		{
			Book* a = books[j];
			Book* b = books[j + 1];
			bool aIsGreater = cmpFunction(a, b); 
			//false && !(15 > 10) || !false && (15 > 10) - ще се разменят
			//true  && !(15 > 10) || !true  && (15 > 10) - няма да се разменят
			//false && !(10 > 15) || !false && (10 > 15) - няма да се разменят
			//true  && !(10 > 15) || !true  && (10 > 15) - ще се разменят
			//false && !(10 > 10) || !false && (10 > 10) - няма да се разменят
			//true  && !(10 > 10) || !true  && (10 > 10) - ще се разменят
			if ((desc && !aIsGreater) || (!desc && aIsGreater)) 
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

