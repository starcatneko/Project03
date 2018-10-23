#include "Project03\Exceldb_charSt.h"
Exceldb_charSt::Exceldb_charSt()
{
}
Exceldb_charSt::~Exceldb_charSt()
 {
}
void Exceldb_charSt::SetDB()
{ 

	chordStateList = {
		{	1	,	0	,	0	,	1	,	0	,	0	},
		{	0	,	1	,	1	,	0	,	0	,	0	},
		{	1	,	0	,	0	,	0	,	1	,	0	},
		{	0	,	1	,	0	,	0	,	0	,	0	},
		{	0	,	0	,	1	,	0	,	0	,	0	},
		{	1	,	0	,	0	,	1	,	1	,	1	},
	};
	unitName = {
		"King",
		"Queen",
		"Knight",
		"Bishop",
		"Rook",
		"YOSHIDA_SAORI"
	};
}
