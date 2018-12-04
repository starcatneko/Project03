#include "ImageMng.h"
#include "DxLib.h"

std::unique_ptr<ImageMng, ImageMng::ImageMngDeleter> ImageMng::s_Instance(new ImageMng());


void ImageMng::LoadImg(std::string path, std::string name)
{
	auto itr = image.find(name);
	if (itr != image.end())
	{
		return;
	}
	image[name] = LoadGraph(path.c_str(), 0);

	printf("w");
}

void ImageMng::DrawImg(VECTOR2 pos, std::string name, int tranceflg)
{

	if (&image[name] != nullptr)
	{
		DrawGraph(pos.x,pos.y,image[name],tranceflg);

	}
}


ImageMng::ImageMng()
{
}


ImageMng::~ImageMng()
{
}
