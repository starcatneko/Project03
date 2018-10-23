#pragma once
#include <vector>
#include <list>
#include <memory>

class Exceldb_charSt
{
public:

	Exceldb_charSt();
	~Exceldb_charSt();

	std::vector<std::vector<unsigned int>> chordStateList;
	std::vector<std::string> unitName;

	void SetDB();
	
};