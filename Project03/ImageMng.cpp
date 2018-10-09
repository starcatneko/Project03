#include "ImageMng.h"
#include "DxLib.h"

std::unique_ptr<ImageMng, ImageMng::ImageMngDeleter> ImageMng::s_Instance(new ImageMng());


void ImageMng::ImageCtr(VECTOR2 pos,std::string path)
{
	if (image[path] == 0)
	{
		LoadGraph(path.c_str(), 0);
	}
	DrawGraph(pos.x, pos.y, image[path], true);

}

void ImageMng::LoadImg(std::string path, std::string name)
{

	image[name] = LoadGraph(path.c_str(), 0);
}
void ImageMng::LoadImg(std::string path)
{

	image[path] = LoadGraph(path.c_str(), 0);
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
