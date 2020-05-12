#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "Manager.h"
#include "Book.h"
#include "BookArray.h"
#include "UserArray.h"

using namespace std;

void Manager::commands()
{
	string line;
	BookArray books; 
	string command;

	do
	{
		std::cout << "> ";
		getline(cin, line);
		vector<string> parts = splitLine(line);
		
		if (parts.size() == 0)
		{
			continue;
		}
		else if (parts[0] == "open")
		{
			if (parts.size() >= 2)
			{
				books.openFile(parts[1]);
			}
			else
			{
				cout << "Please input a filename!" << std::endl;
			}
		}
		else if (parts[0] == "close")
		{
			books.close();
		}
		else if (parts[0] == "save")
		{
			if (books.getFilepath().size())
			{
				books.saveFile(); 
			}
			else
			{
				std::cout << "Filename: ";
				getline(cin,line);
				books.saveFile(line);
			}
		}
		else if (parts[0] == "saveAs")
		{
			if (parts.size() >= 2)
			{
				books.saveFile(parts[1]);
			}
			else
			{
				std::cout << "Please input a filename!" << std::endl;
			}
		}
		else if (parts[0] == "booksAdd")
		{
			Book book;
			book.input();
			books.addBook(book);
		}
		else if (parts[0] == "booksAll")
		{
			books.printAll();
		}
		else if (parts[0] == "booksView")
		{
				books.printView();
		}
		else if (parts[0] == "booksInfo")
		{
			if (parts.size() >= 2)
			{
				int isbn = atoi(parts[1].c_str());
				Book* book = books.getByISBN(isbn);
				if (book)
				{
					cout << *book;
				}
				else
				{
					cout << "Book not found!" << endl;
				}
			}
			else
			{
				std::cout << "Please input a ISBN!" << std::endl;
			}
		}
		else if (parts[0] == "booksFind")
		{
			if (parts.size() >= 3)
			{
				Book* book;
				string arg = parts[2];
				for (size_t i = 3; i < parts.size(); i++)
				{
					arg += " " + parts[i];
				}
				bool error = false;
				if (parts[1] == "title")
				{
					book = books.getByTitle(arg);
				}
				else if (parts[1] == "author")
				{
					book = books.getByAuthor(arg);
				}
				else if (parts[1] == "tag")
				{
					book = books.getByTag(arg);
				}
				else
				{
					error = true;
					cout << "Invalid search criteria!" << endl;
				}

				if (!error)
				{
					if (book)
					{
						book->print();
					}
					else
					{
						cout << "Book not found!" << endl;
					}
				}
			}
			else
			{
				cout << "Not enough agruments!" << endl;
			}
		}
		else if (parts[0] == "booksRemove")
		{
			if (parts.size() >= 2)
			{
				int isbn = atoi(parts[1].c_str());
				bool isRemoved = books.removeByISBN(isbn);
				if (isRemoved)
				{
					cout << "Book removed!" << endl;
				}
				else
				{
					cout << "Book not found!" << endl;
				}
			}
			else
			{
				std::cout << "Please input a ISBN!" << std::endl;
			}
		}
		else if (parts[0] == "booksSort")
		{
			if (parts.size() >= 2)
			{
				bool (*cmpFunction)(const Book * a, const Book * b) = nullptr;
				if (parts[1] == "title")
				{
					cmpFunction = booksTitleCmp;
				}
				else if (parts[1] == "author")
				{
					cmpFunction = booksAuthorCmp;
				}
				else if (parts[1] == "year")
				{
					cmpFunction = booksYearCmp;
				}
				else if (parts[1] == "rating")
				{
					cmpFunction = booksRatingCmp;
				}

				bool desc = false;
				if (parts.size() >= 3)
				{
					if (parts[2] == "asc")
					{
						desc = false;
					}
					else if (parts[2] == "desc")
					{
						desc = true;
					}
					else 
					{
						cmpFunction = nullptr; // �� �� �� �� ����� booksSort
					}
				}
				if (cmpFunction)
				{
					books.booksSort(cmpFunction, desc);
					cout << "Books sorted!" << endl;
				}
				else
				{
					cout << "Not a valid sorting method!" << endl;
				}
			}
			else
			{
				cout << "Please choose sorting method!" << endl;
			}
		}
		else if (parts[0] == "help")
		{
			std::cout << "open <FILEPATH> - opens a book file" << std::endl;
			std::cout << "close - closes the current book file" << std::endl; 
			std::cout << "save - saves the current book file" << std::endl; 
			std::cout << "saveAs <FILEPATH> - saves the current book file in a new location" << std::endl; 
			std::cout << "booksAdd - adds a new book" << std::endl; 
			std::cout << "booksRemove <ISBN> - removes a book" << std::endl; 
			std::cout << "booksAll - displays all books" << std::endl; 
			std::cout << "booksView - displays detailed information of all books" << std::endl; 
			std::cout << "booksInfo <ISBN> - displays book" << std::endl; 
			std::cout << "booksFind <title|author|tag> <SEARCH> - finds a book" << std::endl; 
			std::cout << "booksSort <title|author|year|rating> [asc|desc] - sort books" << std::endl; 
			std::cout << "help - displays all commands and their capabilities" << std::endl; 
			std::cout << "exit - closes the program" << std::endl; 
		}
		else if (parts[0] == "exit")
		{
			break;
		}
		else
		{
			std::cout << "Invalid command!" << std::endl;
		}
	} 
	while (true);
}

vector<string> Manager::splitLine(string line)
{
	vector<string> vec;
	while (line.size())
	{
		size_t pos = line.find(' ');
		while (pos == 0)
		{
			line = line.substr(1); //������� ����������� ����� ������
			pos = line.find(' ');
		}
		if (pos == -1)
		{
			vec.push_back(line);
			line.clear();
		}
		else
		{
			string part = line.substr(0, pos); // ����� line �� �������� �� �������� ���������
			"red blue";
			vec.push_back(part);
			line = line.substr(pos + 1); //������� �� �������� ��������� �� ����
		}
	}
	return vec;
}
