#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum ReadingStatus { NOT_STARTED = 0, READING = 1, FINISHED = 2 };
enum PurchaseStatus { OWNED = 0, WISHLIST = 1 };

struct Book
{
	string title;
	string author;
	ReadingStatus readingStatus;
	PurchaseStatus purchaseStatus;
};

string ReadingStatusString(ReadingStatus rs)
{
	if (rs == NOT_STARTED)
	{
		return "Not Started";
	}
	else if (rs == READING)
	{
		return "Reading";
	}
	else if (rs == FINISHED)
	{
		return "Finished";
	}
	else
	{
		return "?";
	}
}

string PurchaseStatusString(PurchaseStatus ps)
{
	if (ps == OWNED)
	{
		return "Owned";
	}
	else if (ps == WISHLIST)
	{
		return "Wishlist";
	}
	else
	{
		return "?";
	}
}

void SetBook(Book& book, string title, string author, PurchaseStatus ps, ReadingStatus rs)
{
	book.title = title;
	book.author = author;
	book.purchaseStatus = ps;
	book.readingStatus = rs;
}

void DisplayBook(Book book)
{
	cout << book.title << " by " << book.author << endl;
	cout << "\t" << "Purchase: " << PurchaseStatusString(book.purchaseStatus)
		<< ", Reading: " << ReadingStatusString(book.readingStatus) << endl;
}

void DisplayBookList(Book books[100], int bookCount)
{
	for (int i = 0; i < bookCount; i++)
	{
		cout << i << ". ";
		DisplayBook(books[i]);
	}
	cout << endl;
}

int GetValidInput(int min, int max)
{
	int choice = 0;
	do
	{
		cout << ">> ";
		cin >> choice;
		if (choice < min || choice > max)
		{
			cout << "Error: Invalid choice!" << endl;
		}
	} while (choice < min || choice > max);
	cin.ignore();
	cout << endl;
	return choice;
}

void UpdateBookMenu(Book books[100], int& bookCount)
{
	DisplayBookList(books, bookCount);
	cout << "What book do you want to update?: ";
	int index = GetValidInput(0, bookCount);
	string title = books[index].title;
	string author = books[index].author;
	int ps = books[index].purchaseStatus;
	int rs = books[index].readingStatus;
	DisplayBook(books[index]);
	cout << "1. Update title." << endl;
	cout << "2. Update author." << endl;
	cout << "3. Update purchase status." << endl;
	cout << "4. Update reading status." << endl;
	switch (GetValidInput(1, 4))
	{
	case 1:
		//Title
		cout << "Enter new title: ";
		getline(cin, title);
		SetBook(books[index], title, author, (PurchaseStatus)ps, (ReadingStatus)rs);
		break;
	case 2:
		//Author
		cout << "Enter new author: ";
		getline(cin, author);
		SetBook(books[index], title, author, (PurchaseStatus)ps, (ReadingStatus)rs);
		break;
	case 3:
		//Purchase status
		cout << "\t" << OWNED << ". " << PurchaseStatusString(OWNED) << endl;
		cout << "\t" << WISHLIST << ". " << PurchaseStatusString(WISHLIST) << endl;
		cout << "Enter new purchase status: ";
		ps = GetValidInput(OWNED, WISHLIST);
		SetBook(books[index], title, author, (PurchaseStatus)ps, (ReadingStatus)rs);
		break;
	case 4:
		//Reading status
		cout << "\t" << NOT_STARTED << ". " << ReadingStatusString(NOT_STARTED) << endl;
		cout << "\t" << READING << ". " << ReadingStatusString(READING) << endl;
		cout << "\t" << FINISHED << ". " << ReadingStatusString(FINISHED) << endl;
		cout << "Enter new reading status: ";
		rs = GetValidInput(NOT_STARTED, FINISHED);
		SetBook(books[index], title, author, (PurchaseStatus)ps, (ReadingStatus)rs);
		break;
	}
}

int AddBookMenu(Book books[100], int& bookCount)
{
	string title, author;
	int ps, rs;
	cout << "Enter title: ";
	getline(cin, title);
	cout << "Enter Author: ";
	getline(cin, author);
	cout << "Purchase Status:" << endl;
	cout << "\t" << OWNED << ". " << PurchaseStatusString(OWNED) << endl;
	cout << "\t" << WISHLIST << ". " << PurchaseStatusString(WISHLIST) << endl;
	ps = GetValidInput(OWNED, WISHLIST);
	cout << "Reading Status:" << endl;
	cout << "\t" << NOT_STARTED << ". " << ReadingStatusString(NOT_STARTED) << endl;
	cout << "\t" << READING << ". " << ReadingStatusString(READING) << endl;
	cout << "\t" << FINISHED << ". " << ReadingStatusString(FINISHED) << endl;
	rs = GetValidInput(NOT_STARTED, FINISHED);

	SetBook(books[bookCount], title, author, (PurchaseStatus)ps, (ReadingStatus)rs);
	bookCount++;
}

void DisplayStats(Book books[100], int bookCount)
{
	int totalFinished = 0;
	int totalReading = 0;
	int totalUnstarted = 0;

	for (int i = 0; i < bookCount; i++)
	{
		if (books[i].readingStatus = NOT_STARTED)
		{
			totalUnstarted++;
		}
		else if (books[i].readingStatus = READING)
		{
			totalReading++;
		}
		else if (books[i].readingStatus = FINISHED)
		{
			totalFinished++;
		}
	}
	cout << "Not started: " << totalUnstarted << " Reading: " << totalReading
		<< " Finished: " << totalFinished << endl;
}

void SaveList(Book books[100], int bookCount)
{
	ofstream output("booklist.txt");
	for (int i = 0; i < bookCount; i++)
	{
		output << "BOOK_" << i << endl
			<< books[i].title << endl
			<< books[i].author << endl
			<< books[i].purchaseStatus << endl
			<< books[i].readingStatus << endl;
	}
	output.close();
	cout << "Save complete!" << endl;
}

void LoadList(Book books[100], int& bookCount)
{
	ifstream input("booklist.txt");
	bookCount = 0;
	string title, status, author, buffer;
	int rs, ps;
	while (input >> buffer)
	{
		input.ignore();
		getline(input, title);
		getline(input, author);
		input >> ps;
		input >> rs;
		SetBook(books[bookCount], title, author, (PurchaseStatus)ps, (ReadingStatus)rs);
		bookCount++;
	}
}

void ExportCsv(Book books[100], int& bookCount)
{
	ofstream output("booklist.csv");

	output << "TITLE,AUTHOR,READING?,OWNED?" << endl;

	for (int i = 0; i < bookCount; i++)
	{
		output << books[i].title << ","
			<< books[i].author << ","
			<< books[i].readingStatus << ","
			<< books[i].purchaseStatus << ","
			<< endl;
	}
	output.close();
}

void ExportUnfinishedBooks(Book books[100], int& bookCount)
{
	ofstream output("booklist.csv");

	output << "TITLE,AUTHOR,READING?,OWNED?" << endl;

	for (int i = 0; i < bookCount; i++)
	{
		if (books[i].readingStatus == NOT_STARTED ||
			books[i].readingStatus == READING)
		{
			output << books[i].title << ","
				<< books[i].author << ","
				<< books[i].readingStatus << ","
				<< books[i].purchaseStatus << ","
				<< endl;
		}
	}
	output.close();
}

void MainMenu(Book books[100], int& bookCount)
{
	bool done = false;
	while (!done)
	{
		cout << "1. Add book" << endl;
		cout << "2. Update book" << endl;
		cout << "3. Display book list" << endl;
		cout << "4. Display stats" << endl;
		cout << "5. Export books" << endl;
		cout << "6. Export unfinished books" << endl;
		cout << "7. Quit" << endl;

		switch (GetValidInput(1, 7))
		{
		case 1:
			AddBookMenu(books, bookCount);
			break;
		case 2:
			UpdateBookMenu(books, bookCount);
			break;
		case 3:
			DisplayBookList(books, bookCount);
			break;
		case 4:
			DisplayStats(books, bookCount);
			break;
		case 5:
			ExportCsv(books, bookCount);
			break;
		case 6:
			ExportUnfinishedBooks(books, bookCount);
			break;
		case 7:
			SaveList(books, bookCount);
			done = true;
			break;
		}
	}
}

int main()
{
	Book books[100];
	int bookCount = 0;
	LoadList(books, bookCount);
	MainMenu(books, bookCount);

	return 0;
}
