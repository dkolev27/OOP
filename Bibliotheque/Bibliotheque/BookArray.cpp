#include <fstream>
#include "BookArray.h"

BookArray::BookArray()
{
	init();
}

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

void BookArray::addBook(const BooksData& book)
{
	if (currentCount == currentSize)
	{
		currentSize *= 2;
		BooksData** newArr;
		newArr = new BooksData * [currentSize];
		for (int i = 0; i < currentCount; i++)
		{
			newArr[i] = arr[i];
		}
		delete[] arr;
		arr = newArr;
	}

	arr[currentCount] = new BooksData(book);
	currentCount++;
}

void BookArray::openFile(const char* filepath)
{
	std::ifstream file(filepath);
	if (file)
	{
		clear();
		init();
		setFilepath(filepath); 
		while (!file.eof())
		{
			BooksData book;
			file >> book; 
			if (book.getAuthor() == nullptr) 
			{
				if (currentCount == 0)
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

void BookArray::saveFile(const char* filepath)
{
	std::ofstream file(filepath);
	if (file)
	{
		for (int i = 0; i < currentCount; i++)
		{
			file << *arr[i];
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
	for (int i = 0; i < currentCount; i++)
	{
		arr[i]->print();
	}
}

void BookArray::close()
{
	clear();
}

char* BookArray::getFilepath()
{
	return filepath;
}

void BookArray::setFilepath(const char* filepath)
{
	if (this->filepath)
	{
		delete[] this->filepath;
	}
	this->filepath = new char[strlen(filepath) + 1];
	strcpy(this->filepath, filepath);
}

void BookArray::copy(const BookArray& other)
{
	currentSize = other.currentSize;
	currentCount = other.currentCount;
	arr = new BooksData* [currentSize];
	for (int i = 0; i < currentCount; i++)
	{
		arr[i] = new BooksData(*other.arr[i]); 
	}
	if (other.filepath)
	{
		setFilepath(other.filepath);
	}
}

void BookArray::clear()
{
	for (int i = 0; i < currentCount; i++)
	{
		delete arr[i];
	}
	currentCount = 0;
	currentSize = 0;
	delete[] arr;
	arr = nullptr;
	delete[] filepath;
	filepath = nullptr;
}

void BookArray::init()
{
	currentSize = 2;
	currentCount = 0;
	arr = new BooksData * [currentSize];
	filepath = nullptr;
}
