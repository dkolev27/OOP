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
	BookArray books; 
	UserArray users("users.txt");
	User* loggedUser = nullptr;

	do
	{
		string line;
		cout << "> ";
		getline(cin, line);
		vector<string> parts = splitLine(line);
		
		if (parts.size() == 0)
		{
			continue;
		}
		else if (parts[0] == "login") 
		{
			if (parts.size() > 1)
			{
				cout << "Too many arguments!" << endl;
			}
			else
			{
				string username;
				string password;
				if (loggedUser) //Ако опитаме да се логнем повече от 1 път
				{ 
					cout << "You are already logged in!!!" << endl;
					continue;
				}
				cout << "Username: ";
				getline(cin, username);
				cout << "Password: ";
				getline(cin, password);
				User* user = users.logInUser(username, password);
				if (user)
				{
					loggedUser = user;
					cout << "Welcome " << loggedUser->getUsername() << "!" << endl;
				}
				else
				{
					cout << "Invalid username or password!" << endl;
				}
			}
		}
		else if (parts[0] == "logout")
		{
			if (parts.size() > 1)
			{
				cout << "Too many arguments!" << endl;
			}
			else
			{
				if (loggedUser)
				{
					cout << "Goodbye " << loggedUser->getUsername() << "!" << endl;
					loggedUser = nullptr;
				}
				else
				{
					cout << "You are not logged in!" << endl;
				}
			}
		}
		else if (parts[0] == "usersAdd")
		{
			if (parts.size() > 3)
			{
				cout << "Too many arguments!" << endl;
			}
			else if (parts.size() == 3)
			{
				if (loggedUser)
				{
					if (loggedUser->getIsAdmin())
					{
						User* existingUser = users.getUser(parts[1]);
						if (existingUser)
						{
							cout << "User already exists!" << endl;
						}
						else
						{
							User newUser(parts[1], parts[2], false);
							users.addUser(newUser);
							users.saveFile();
						}
					}
					else
					{
						cout << "Only admin can add users!!!" << endl;
					}
				}
				else
				{
					cout << "You have to be logged in!" << endl;
				}
			}
			else
			{
				cout << "Please input username and password!" << endl;
			}
		}
		else if (parts[0] == "usersRemove")
		{
			if (parts.size() > 2)
			{
				cout << "Too many arguments!" << endl;
			}
			else if (parts.size() == 2)
			{
				if (loggedUser)
				{
					if (loggedUser->getIsAdmin())
					{
						if (parts[1] == loggedUser->getUsername())
						{
							cout << "Can't remove yourself!" << endl;
						}
						else
						{
							bool userRemoved = users.removeUser(parts[1]);
							if (userRemoved)
							{
								users.saveFile();
								cout << "User removed!" << endl;
							}
							else
							{
								cout << "User doesn't exist!" << endl;
							}
						}
					}
					else
					{
						cout << "Only admin can remove users!!!" << endl;
					}
				}
				else
				{
					cout << "You have to be logged in!" << endl;
				}
			}
			else
			{
				cout << "Please input username and password!" << endl;
			}
		}
		else if (parts[0] == "open")
		{
			if (parts.size() > 2)
			{
				cout << "Too many arguments!" << endl;
			}
			else if (parts.size() == 2)
			{
				books.openFile(parts[1]);
			}
			else
			{
				cout << "Please input a filename!" << endl;
			}
		}
		else if (parts[0] == "close")
		{
			if (parts.size() > 1)
			{
				cout << "Invalid command!" << endl;
			}
			else
			{
				books.close();
			}
		}
		else if (parts[0] == "save")
		{
			if (parts.size() > 1)
			{
				cout << "Invalid command!" << endl;
			}
			else
			{
				if (books.getFilepath().size())
				{
					books.saveFile();
				}
				else
				{
					cout << "Filename: ";
					getline(cin, line);
					books.saveFile(line);
				}
			}
		}
		else if (parts[0] == "saveAs")
		{
			if (parts.size() > 2)
			{
				cout << "Too many arguments!" << endl;
			}
			else if (parts.size() == 2)
			{
				books.saveFile(parts[1]);
			}
			else
			{
				cout << "Please input a filename!" << endl;
			}
		}
		else if (parts[0] == "booksAdd")
		{
			if (parts.size() > 1)
			{
				cout << "Invalid command!" << endl;
			}
			else
			{
				if (loggedUser && loggedUser->getIsAdmin())
				{
					Book book;
					book.input();
					books.addBook(book);
				}
				else
				{
					cout << "Only admin can add new books!" << endl;
				}
			}
		}
		else if (parts[0] == "booksAll")
		{
			if (parts.size() > 1)
			{
				cout << "Invalid command!" << endl;
			}
			else
			{
				if (loggedUser)
				{
					books.printAll();
				}
				else
				{
					cout << "You have to be logged in to view books!" << endl;
				}
			}
		}
		else if (parts[0] == "booksView")
		{
			if (parts.size() > 1)
			{
				cout << "Invalid command!" << endl;
			}
			else
			{
				if (loggedUser)
				{
					books.printView();
				}
				else
				{
					cout << "You have to be logged in to view books!" << endl;
				}
			}
		}
		else if (parts[0] == "booksInfo")
		{
			if (loggedUser)
			{
				if (parts.size() > 2)
				{
					cout << "Too many arguments!" << endl;
				}
				else if (parts.size() == 2)
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
					cout << "Please input a ISBN!" << endl;
				}
			}
			else
			{
				cout << "You have to be logged in to view books!" << endl;
			}
		}
		else if (parts[0] == "booksFind")
		{
			if (loggedUser)
			{
				if (parts.size() >= 3)
				{
					Book* book;
					string arg = parts[2];
					bool error = false;
					for (size_t i = 3; i < parts.size(); i++)
					{
						arg += " " + parts[i]; // Слива всички части от реда започвайки от позиция 2
					}                          
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
					else // Ако напишем нещо, което не е автор, заглавие или таг
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
			else
			{
				cout << "You have to be logged in to find books!" << endl;
			}
		}
		else if (parts[0] == "booksRemove")
		{
			if (loggedUser && loggedUser->getIsAdmin())
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
					cout << "Please input an ISBN!" << endl;
				}
			}
			else
			{
				cout << "Only admin can remove books!" << endl;
			}
		}
		else if (parts[0] == "booksSort") 
		{
			if (loggedUser)
			{
				if (books.getCount()) // Ако има книги
				{
					if (parts.size() > 3)
					{
						cout << "Too many agruments!" << endl;
					}
					else if (parts.size() >= 2)
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
							else // Когато не е валиден parts[2]
							{
								cmpFunction = nullptr; // за да не се пуска booksSort
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
				else
				{
					cout << "No books to be sorted!" << endl;
				}
			}
			else
			{
				cout << "You have to be logged in to sort books!" << endl;
			}
		}
		else if (parts[0] == "help")
		{
			if (parts.size() > 1)
			{
				cout << "Invalid command!" << endl;
			}
			else
			{
				cout << "login - logs in an user" << endl;
				cout << "logout - logs out an user" << endl;
				cout << "open <FILEPATH> - opens a book file" << endl;
				cout << "close - closes the current book file" << endl;
				cout << "save - saves the current book file" << endl;
				cout << "saveAs <FILEPATH> - saves the current book file in a new location" << endl;
				cout << "booksAdd - adds a new book" << endl;
				cout << "booksRemove <ISBN> - removes a book" << endl;
				cout << "booksAll - displays all books" << endl;
				cout << "booksView - displays detailed information of all books" << endl;
				cout << "booksInfo <ISBN> - displays book" << endl;
				cout << "booksFind <title|author|tag> <SEARCH> - finds a book" << endl;
				cout << "booksSort <title|author|year|rating> [asc|desc] - sort books" << endl;
				cout << "usersAdd <USERNAME> <PASSWORD> - adds a new user" << endl;
				cout << "usersRemove <USERNAME> - removes a user" << endl;
				cout << "help - displays all commands and their capabilities" << endl;
				cout << "exit - closes the program" << endl;
			}
		}
		else if (parts[0] == "exit")
		{
			break;
		}
		else
		{
			cout << "Invalid command!" << endl;
		}
	} 
	while (true);
}

vector<string> Manager::splitLine(string line) // Разбива реда на отделни думи
{
	vector<string> vec;
	while (line.size()) 
	{ 
		size_t pos = line.find(' ');
		while (pos == 0) // Премахва празното разстояние преди най-лявата дума от реда
		{
			line = line.substr(1); // Отзярва празното разстоянието преди текста, ако случайно има такова
			pos = line.find(' ');
		}
		if (pos == -1) // Ако няма повече празни разстояния
		{
			if (line.size()) // Ако е останало нещо в реда след премахване на празните разстояния, тогава го добавяме в масива
			{
				vec.push_back(line); // Добавя последната дума от реда в края на масива
				line.clear(); // Премахва последната дума от реда
			}
		}
		else // Ако е намерило празно разстояние след най-лявата дума
		{
			string part = line.substr(0, pos); // Взима най-лявата дума от реда
			vec.push_back(part); // Слага най-лявата дума в масива
			line = line.substr(pos + 1); // Премахва най-лявата дума от реда
		}
	}
	return vec;
}
