#pragma once

#include <list>
#include <memory>
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

private:
	ImageMng();
	~ImageMng();
	static std::once_flag initFlag;
	static ImageMng *s_Instance;
};

