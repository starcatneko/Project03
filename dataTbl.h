#include ""
DATA_CHAR_MAX 5
DATA_STATE_MAX 5
	extern int chordStateTbl[DATA_CHAR_MAX][DATA_STATE_MAX] = {
//		{	Worp	,	WTurn	,	LTurn	,	Quick	,	Barrier	}, // 	
		{	1	,	0	,	0	,	1	,	0	}, // 	King
		{	0	,	1	,	1	,	0	,	0	}, // 	Queen
		{	1	,	0	,	0	,	0	,	1	}, // 	Knight
		{	0	,	1	,	0	,	0	,	0	}, // 	Bishop
		{	0	,	0	,	1	,	0	,	0	} // 	Rook
	};
}
