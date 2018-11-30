#pragma once
#include "GameState.h"
#include <memory>
#include <vector>
#include <list>

class GameBoard;
class MouseCtr;
class GamePiece;
#include "Player.h"
typedef std::shared_ptr<GameBoard> Board_ptr;


class GameMain :
	public GameState
{
public:
	GameMain();
	~GameMain();

	state_ptr Update(state_ptr pt);
	void Draw();	
	void CurrentPlayerChange();
private:
	void AddPlayer();
	Board_ptr MainBoard;
	// AIがプログラム上で盤面のシミュレートをする際に使うBoard
	// 盤面をMainBoardからコピーし、実際における場所に駒の置いた際に
	// 盤面がどのような状態になるかを比較する
	Board_ptr AIBoard;
	void setNextPlayer();
};

