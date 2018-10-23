#include "Project03\Exceldb_charSt.h"
Exceldb_charSt::Exceldb_charSt()
{
}
Exceldb_charSt::~Exceldb_charSt()
 {
}
void Exceldb_charSt::SetDB()
{ 

//std::vector<std::vector<unsigned int>> chordStateList
	chordStateList = {
		{	1	,	0	,	0	,	1	,	0	},
		{	0	,	1	,	1	,	0	,	0	},
		{	1	,	0	,	0	,	0	,	1	},
		{	0	,	1	,	0	,	0	,	0	},
		{	0	,	0	,	1	,	0	,	0	},
	};
	unitName = {
		"King",
		"Queen",
		"Knight",
		"Bishop",
		"Rook"
	};
}
