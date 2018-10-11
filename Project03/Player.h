#pragma once

#include "VECTOR2.h"

#include <vector>
#include <list>
#include <memory>

enum PIECE_ST;
class PieceTray;

class Player
{
public:
	Player();
	~Player();
	void Update();
	int GetNo();
	PIECE_ST GetType();
private:
	int playerNo;
	static int playercnt;
	std::unique_ptr <PieceTray> pieceTray;
	PIECE_ST piecetype;
};

