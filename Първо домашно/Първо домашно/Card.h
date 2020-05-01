#pragma once
#include <iostream>
const int MAX_SIZE_SUIT_LETTERS = 9;
const int MAX_SIZE_RANK_SYMBOLS = 3;
const int MAX_SIZE_SERIAL_NUMBER = 16;

class Card
{
public:
	//Big 4 + param. c-tor
	Card();
	Card(const char* suit, const char* rank, const char* serialNumber);
	Card(const Card& other);
	Card& operator=(const Card& other);
	~Card();

	//Getters
	int getPoints() const;
	char* getSuit() { return suit; }
	char* getRank() { return rank; }

	friend std::ostream& operator<<(std::ostream & out, Card& card);

private:
	//Fields
	char suit[MAX_SIZE_SUIT_LETTERS];
	char rank[MAX_SIZE_RANK_SYMBOLS];
	char* serialNumber;

	void clear();
	void copy(const Card& other);
};

