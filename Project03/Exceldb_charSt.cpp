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
		{	Worp	,	WTurn	,	LTurn	,	Quick	,	Barrier	}, // 	
		{	1	,	0	,	0	,	1	,	0	}, // 	King
		{	0	,	1	,	1	,	0	,	0	}, // 	Queen
		{	1	,	0	,	0	,	0	,	1	}, // 	Knight
		{	0	,	1	,	0	,	0	,	0	}, // 	Bishop
		{	0	,	0	,	1	,	0	,	0	}, // 	Rook
		{	0	,	0	,	0	,	0	,	0	} // 	キャラクター名
	};
}
