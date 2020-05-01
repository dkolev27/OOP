#include <iostream>
#include <cstring>
#include <fstream>
#include "BooksData.h"
#include "Commands.h"
#include "BookArray.h"
#include "UserArray.h"

const int MAX_CMD_LINE_LEN = 128; 

void commands()
{
	char line[MAX_CMD_LINE_LEN]; 
	BookArray books; 
	char* command;

	do
	{
		std::cout << "> ";
		std::cin.getline(line, MAX_CMD_LINE_LEN);
		command = strtok(line, " "); //Функцията е взета от интернет
		if (!command)
		{
			continue;
		}
		else if (strcmp(command, "open") == 0)
		{
			char* filepath = strtok(NULL, " ");
			if (filepath)
			{
				books.openFile(filepath);
			}
			else
			{
				std::cout << "Please input a filename!" << std::endl;
			}
		}
		else if (strcmp(command, "close") == 0)
		{
			books.close();
		}
		else if (strcmp(command, "save") == 0)
		{
			if (books.getFilepath())
			{
				books.saveFile(); 
			}
			else
			{
				std::cout << "Filename: ";
				std::cin.getline(line, MAX_CMD_LINE_LEN);
				books.saveFile(line);
			}
		}
		else if (strcmp(command, "saveAs") == 0)
		{
			char* filepath = strtok(NULL, " ");
			if (filepath)
			{
				books.saveFile(filepath);
			}
			else
			{
				std::cout << "Please input a filename!" << std::endl;
			}
		}
		else if (strcmp(command, "booksAdd") == 0)
		{
			BooksData book;
			book.input();
			books.addBook(book);
		}
		else if (strcmp(command, "booksAll") == 0)
		{
			books.printAll();
		}
		else if (strcmp(command, "help") == 0)
		{
			std::cout << "open FILEPATH - opens a book file" << std::endl;
			std::cout << "close - closes the current book file" << std::endl; 
			std::cout << "save - saves the current book file" << std::endl; 
			std::cout << "saveAs FILEPATH - saves the current book file in a new location" << std::endl; 
			std::cout << "booksAdd - adds a new book" << std::endl; 
			std::cout << "booksAll - displays all books" << std::endl; 
			std::cout << "help - displays all commands and their capabilities" << std::endl; 
			std::cout << "exit - closes the program" << std::endl; 
		}
		else if (strcmp(command, "exit") == 0)
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
