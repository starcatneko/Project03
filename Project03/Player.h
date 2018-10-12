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
	void SetTray();
	int GetNo();
	void SelectTray(VECTOR2 pos);
	PIECE_ST GetType();
	void DeleteTrayPiece();
private:
	int playerNo;
	static int playercnt;
	std::unique_ptr <PieceTray> pieceTray;
	PIECE_ST piecetype;
};

