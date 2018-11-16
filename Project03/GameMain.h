#pragma once
#include <memory>
#include <vector>
#include <array>
#include <list>
#include "GameState.h"
#include "MouseCtr.h"
#include "OPRT_Base.h"
#include "Player.h"


class GameBoard;
class MouseCtr;
class GamePiece;
typedef std::shared_ptr<GameBoard> Board_ptr;
typedef std::array<std::shared_ptr<MouseCtr>, static_cast<int>(PIECE_ST::MAX)> MOUSE_BASE;

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

	void Init();
	Board_ptr MainBoard;

	// 盤面操作用のマウスポインタ
	MOUSE_BASE Mouse;
	std::array<OPRT_TYPE, static_cast<int>(PIECE_ST::MAX)> oprt_tbl;
	std::array<std::unique_ptr<OPRT_Base>(), static_cast<int>(OPRT_TYPE::MAX)> oprt_ptr;
};

