#pragma once

#include "VECTOR2.h"
#include <list>
#include <memory>
#include <string>
#include <map>

class ImageMng
{
public:

	static ImageMng &GetInstance()
	{
		return *s_Instance;
	};

	void LoadImg(std::string path, std::string name);
	void DrawImg(VECTOR2 pos,std::string name,int tranceflg);
private:

	struct ImageMngDeleter
	{
		void operator ()(ImageMng* ImageMng) const
		{
			delete ImageMng;
		}
	};

	ImageMng();
	~ImageMng();
	static std::unique_ptr<ImageMng, ImageMngDeleter> s_Instance;

	// 画像のハンドルが格納される連想配列
	std::map<std::string, int> image;
};

