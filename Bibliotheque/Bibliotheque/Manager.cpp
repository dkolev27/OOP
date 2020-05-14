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
	UserArray users("users.txt");
	User* user = nullptr;
	string command;

	do
	{
		cout << "> ";
		getline(cin, line);
		vector<string> parts = splitLine(line);
		
		if (parts.size() == 0)
		{
			continue;
		}
		else if (parts[0] == "login")
		{
			string username;
			string password;
			cout << "Username: ";
			getline(cin, username);
			cout << "Password: ";
			getline(cin, password);
			User* newUser = users.logInUser(username, password);
			if (newUser)
			{
				user = newUser;
				cout << "Welcome " << user->getUsername() << "!" << endl;
			}
			else
			{
				cout << "Invalid username or password!" << endl;
			}
		}
		else if (parts[0] == "logout")
		{
			if (user)
			{
				cout << "Goodbye " << user->getUsername() << "!" << endl;
				user = nullptr;
			}
			else
			{
				cout << "You are not logged in!" << endl;
			}
		}
		else if (parts[0] == "usersAdd")
		{
			if (parts.size() >= 3)
			{
				if (user)
				{
					if (user->getIsAdmin())
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
			if (parts.size() >= 2)
			{
				if (user)
				{
					if (user->getIsAdmin())
					{
						if (parts[1] == user->getUsername())
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
			if (parts.size() >= 2)
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
				cout << "Filename: ";
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
				cout << "Please input a filename!" << endl;
			}
		}
		else if (parts[0] == "booksAdd")
		{
			if (user && user->getIsAdmin())
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
		else if (parts[0] == "booksAll")
		{
			if (user)
			{
				books.printAll();
			}
			else
			{
				cout << "You have to be logged in to view books!" << endl;
			}
		}
		else if (parts[0] == "booksView")
		{
			if (user)
			{
				books.printView();
			}
			else
			{
				cout << "You have to be logged in to view books!" << endl;
			}
		}
		else if (parts[0] == "booksInfo")
		{
			if (user)
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
			if (user)
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
			else
			{
				cout << "You have to be logged in to find books!" << endl;
			}
		}
		else if (parts[0] == "booksRemove")
		{
			if (user && user->getIsAdmin())
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
					cout << "Please input a ISBN!" << endl;
				}
			}
			else
			{
				cout << "Only admin can remove books!" << endl;
			}
		}
		else if (parts[0] == "booksSort")
		{
			if (user)
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
				cout << "You have to be logged in to sort books!" << endl;
			}
		}
		else if (parts[0] == "help")
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

vector<string> Manager::splitLine(string line)
{
	vector<string> vec;
	while (line.size())
	{
		size_t pos = line.find(' ');
		while (pos == 0)
		{
			line = line.substr(1); //Отзярва разтоянието преди текста
			pos = line.find(' ');
		}
		if (pos == -1)
		{
			vec.push_back(line);
			line.clear();
		}
		else
		{
			string part = line.substr(0, pos); // Взима line от началото до празното разтояние
			"red blue";
			vec.push_back(part);
			line = line.substr(pos + 1); //Взимаме от празното разтояние до края
		}
	}
	return vec;
}
