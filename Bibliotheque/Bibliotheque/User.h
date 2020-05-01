#pragma once
class User
{
public:
	User();
	User(const char* username, const char* password, bool isAdmin);
	User(const User& other);
	User& operator=(const User& other);
	~User();

	friend std::istream& operator>>(std::istream& in, User& user);
	friend std::ostream& operator<<(std::ostream& out, User& user);

	void setUsername(const char* username);
	char* getUsername() const;
	void setPassword(const char* password);
	char* getPassword() const;
	void setIsAdmin(bool isAdmin);
	bool getIsAdmin() const;

	void print() const;

private:
	char* username;
	char* password;
	bool isAdmin;

	//Helpers
	void copy(const User& other);
	void clear();
};

