#include <iostream>
#include "BooksData.h"

int main()
{
	BooksData a;
	BooksData b("Shakespeare", "Macbeth", "Drama", "This is a story for a girl in love!", 1789, "love, hatred, mercy", 5.60, 2359);
	//BooksData c = b
	//c.print();
	a.input();
	// TO TEST THE CONSTUCTORS!!!


	return 0;
}