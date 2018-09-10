#pragma once

#include "VECTOR2.h"
#include <list>
#include <memory>
#include <string>
#include <map>
#include <mutex>

class ImageMng
{
public:
	static void Create();
	static void Destroy();

	static ImageMng *GetInstance()
	{
		// mutex call_once 一度だけ呼ぶ
		std::call_once(initFlag, Create);
		Create();
		return s_Instance;
	};
	void LoadImg(std::string path, std::string name);
	void DrawImg(VECTOR2 pos,std::string name,int tranceflg);
private:

	ImageMng();
	~ImageMng();
	static std::once_flag initFlag;
	static ImageMng *s_Instance;

	// 画像のハンドルが格納される連想配列
	std::map<std::string, int> image;
};

