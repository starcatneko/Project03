#pragma once

#include "Geometry.h"
#include "VECTOR2.h"
/*
#include <vector>
#include <list>
#include <memory>
*/
enum PIECE_ST;

class Player
{
public:
	Player();
	Player(int number);
	~Player();

	void Init();
	void Update();

	void SetPiece();
	int GetNo();
	PIECE_ST GetType();
private:
	int playerNo;
	PIECE_ST piecetype;
};

