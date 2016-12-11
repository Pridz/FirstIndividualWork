/*
Mateusz Szychowski
6/10
Chce informacje zwrotna
Zgadzam sie na uzycie mojego kodu jako przykladow na szkoleniach

Szczegoly implementacyjne:
- Linia w stylu: obiekt.metoda(); //wywolujemy metode
  jest liczona zarowno do linii z komentarzami jak i linii z kodem
- Cos takiego:*/
/* 1 linia
   2 linia
   3 linia
   4 linia*/
/* bedzie liczone jako 4 linie*/

/*Launch parameters
  arg 1 - path to directory with code
  arg 2..n - file extensions to look for

  arg 1 should be in quotation makrs (ex. "C:\Users\wat\my code")

  ZadanieKNWO.exe "C:\Users\wat\my code" c cpp h hpp
  */

// ZadanieKNWO.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>

#include "LineCounter.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 3) //argv[0] - binary name
	{
		cout << "Not enough arguments, arg1 - path, arg2..n - extensions" << endl;
		return 0;
	}

	vector<string> extList;
	for (int i = 2; i < argc; i++)
		extList.push_back(argv[i]);

	LineCounter lineCounter;
	LinesSummary summary = lineCounter.countLinesAndGetSummary(argv[1], extList);

	cout << "-----SCAN FINISHED-----" <<
		"\nFound " << summary.fileCount << " files" <<
		"\nAll lines: " << summary.allLines <<
		"\nEmpty lines: " << summary.emptyLines <<
		"\nSource lines: " << summary.sourceLines <<
		"\nComments lines: " << summary.commentsLines <<
		"\nLines per file: " << summary.allLines / summary.fileCount <<
		"\nComment lines per file: " << summary.commentsLines / summary.fileCount <<
		"\nEmpty lines per file: " << summary.emptyLines / summary.fileCount << 
		"\n----------------------\n";
	
	return 0;
}

