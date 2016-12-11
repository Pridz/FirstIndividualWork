#include "LineCounter.h"

#include <iostream>
#include <fstream>

using namespace std;

LineCounter::LineCounter()
{}


LineCounter::~LineCounter()
{}

LinesSummary LineCounter::countLinesAndGetSummary(string startDir, vector<string> extList)
{
	extensionsList = extList;
	searchFilesAndCountLines(startDir);
	return summary;
}

void LineCounter::searchFilesAndCountLines(string startDir)
{
	darknessNight::Filesystem::Directory dir(startDir);
	for (auto i = dir.recursiveBegin(); i != dir.recursiveEnd(); i++)
	{
		countLinesIfCorrectFile(*i);
	}
}

void LineCounter::countLinesIfCorrectFile(darknessNight::Filesystem::Entry& entry)
{
	bool isCorrectFile = entry.isFile() && hasCorrectExtension(entry.getPath());
	if (isCorrectFile)
	{
		summary.fileCount++;
		countLines(entry.getPath());
	}
}

bool LineCounter::hasCorrectExtension(string path)
{
	for (string s : extensionsList)
	{
		if (s.size() > path.size())
			continue;
		int pathCharIndex = path.size() - 1;
		for (int i = s.size() - 1; i >= 0; i--)
		{
			if (s[i] != path[pathCharIndex--])
				goto skipThisItem; //TRIGGERED!!!!!
		}
		if (path[pathCharIndex] == '.')
			return true;
	skipThisItem:
		continue;
	}
	return false;
}

void LineCounter::countLines(string path)
{
	string fileText;
	ifstream file(path, ios::in);
	if (!file.is_open())
	{
		cout << "[Error] Can't open file " << path << endl;
		return;
	}
	getline(file, fileText, '\0');
	//replace(fileText.begin(), fileText.end(), '\r', ' '); //lazy fix for \r\n line endings

	bool singleLineComment = false;
	bool multiLineComment = false;
	bool quotationOpen = false;
	bool finishedMultiLineComment = false;
	int lineNumber = 0;
	char previousChar = '\r';
	int charsInLine = 0;
	//cout << "File: " << path << endl;
	for (char c : fileText)
	{
		//cout << "LN: " << lineNumber << endl;
		string lastTwoChars;
		lastTwoChars.push_back(previousChar);
		lastTwoChars.push_back(c);

		if (!isSpace(c))
		{
			if (c == '\n')
			{
				if (singleLineComment || multiLineComment)
					summary.commentsLines++;
				else if (charsInLine > 0)
					summary.sourceLines++;
				else if (!finishedMultiLineComment)
					summary.emptyLines++;
				finishedMultiLineComment = false;
				summary.allLines++;
				singleLineComment = false;
				lineNumber++;
				charsInLine = 0;
				continue;
			}
			else if (!multiLineComment && !singleLineComment && !quotationOpen)
			{
				if (lastTwoChars == "//")
				{
					if (charsInLine > 2) //Lines with code and comment are counted to both statistics
						summary.sourceLines++;
					singleLineComment = true;
				}
				else if (lastTwoChars == "/*")
				{
					if (charsInLine > 2)
						summary.sourceLines++;
					multiLineComment++;
				}
				else if (c == '"')
					quotationOpen = true;
			}
			else if (multiLineComment)
			{
				if (lastTwoChars == "*/")
				{
					charsInLine = -1;
					summary.commentsLines++;
					multiLineComment = false;
					finishedMultiLineComment = true;
				}
			}
			else if (quotationOpen && c == '"' && lastTwoChars != "\\\"")
				quotationOpen = false;

			charsInLine++;
		}

		previousChar = c;
	}

	if (previousChar != '\n') //when file doesn't end with newline, could've been done in a nicer way
	{
		if (singleLineComment || multiLineComment)
			summary.commentsLines++;
		else if (charsInLine > 0)
			summary.sourceLines++;
		else
			summary.emptyLines++;
		summary.allLines++;
	}
}

bool LineCounter::isSpace(char c)
{
	if (c == ' ' || c == '\r' || c == '\t' || c == '\f' || c == '\v')
		return true;
	return false;
}