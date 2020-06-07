#pragma once
#include <string>

using namespace std;

class User
{
public:
	// Голяма четворка + параметризиран конструктор
	User();
	User(const string& username, const string& password, bool isAdmin);
	User(const User& other);
	User& operator=(const User& other);
	~User();

	// Приятелски функции, които четат и записват във файл
	friend std::istream& operator>>(std::istream& in, User& user);
	friend std::ostream& operator<<(std::ostream& out, User& user);

	// Селектори и мутатори
	void setUsername(const string& username);
	string getUsername() const;
	void setPassword(const string& password);
	string getPassword() const;
	void setIsAdmin(bool isAdmin);
	bool getIsAdmin() const;

	void print() const;

private:
	// Член данни
	string username;
	string password;
	bool isAdmin;

	// Помощни функции
	void copy(const User& other);
	void clear();
};

