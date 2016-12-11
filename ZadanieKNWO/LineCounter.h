//czemu tu byla implementacja (╯°□°）╯︵ ┻━┻ 

#pragma once
#include <string>
#include <vector>
#include "Filesystem/Directory.h"

struct LinesSummary
{
	int allLines;
	int sourceLines;
	int commentsLines;
	int emptyLines;
	int fileCount;

	LinesSummary() : allLines(0), sourceLines(0), commentsLines(0), emptyLines(0), fileCount(0) {};
};

class LineCounter
{
private:
	std::vector<std::string> extensionsList;
	LinesSummary summary;
public:
	LineCounter();
	~LineCounter();
	LinesSummary countLinesAndGetSummary(std::string startDir, std::vector<std::string> extList);
private:
	void searchFilesAndCountLines(std::string startDir);
	void countLinesIfCorrectFile(darknessNight::Filesystem::Entry& entry);
	bool hasCorrectExtension(std::string path);
	void countLines(std::string path);
	bool isSpace(char c);
};

