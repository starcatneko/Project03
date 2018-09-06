#include "ImageMng.h"
#include "DxLib.h"


void ImageMng::Create()
{
	s_Instance = new ImageMng();
}

void ImageMng::Destroy()
{
	if (s_Instance)
		delete s_Instance;
	s_Instance = nullptr;

}

ImageMng::ImageMng()
{
}


ImageMng::~ImageMng()
{
}
