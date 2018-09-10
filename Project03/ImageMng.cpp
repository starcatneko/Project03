#include "ImageMng.h"
#include "DxLib.h"

ImageMng *ImageMng::s_Instance = nullptr;

std::once_flag ImageMng::initFlag;

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

void ImageMng::LoadImg(std::string path, std::string name)
{
	 
	image[name] = LoadGraph(path.c_str(),0);
	printf("w");
}

void ImageMng::DrawImg(VECTOR2 pos, std::string name, int tranceflg)
{

	if (&image[name] != nullptr)
	{
		DrawGraph(pos.x,pos.y,image[name],tranceflg);
		printf("w");

	}
}


ImageMng::ImageMng()
{
}


ImageMng::~ImageMng()
{
}
