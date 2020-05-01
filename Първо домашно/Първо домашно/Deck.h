#pragma once
#include <cstring>
#include "Card.h"

const int MAX_SIZE_SDN = 10; //SDN = Serial Deck Number

class Deck
{
public:
	//Big 4 + 2 param. c-tors
	Deck();
	Deck(int currentCapacity);
	Deck(int currentCapacity, const char* serialDeckNumber);
	Deck(const Card& other);
	Deck& operator=(const Deck& other);
	~Deck();

	Card* draw();

	float getProbability(int playerPoints) const;
	int suit_count(const char* suit) const;
	int rank_count(const char* rank) const; 
	void swap(int idx1, int idx2);

private:
	//Fields
	Card** sequenceOfCards;
	char* serialDeckNumber;

	int maximumCapacity;
	int currentCapacity;

	int drewCards;

	//Helpers
	void copy(const Deck& other);
	void clear();
};

