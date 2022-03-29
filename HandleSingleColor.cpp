#include "HandleSingleColor.h"

HandleSingleColor::HandleSingleColor(int dep, QObject *parent)
	: IHandleImage(parent)
{
	depth = dep;
}

HandleSingleColor::~HandleSingleColor()
{

}

QImage HandleSingleColor::apply(const QImage& ima)
{
	QImage::Format format;
	if(depth == 1)
	{
		format = QImage::Format_Mono;
	}
	else if (depth == 2)
	{
		format = QImage::Format_RGB666;
	}
	return ima.convertToFormat(format);
}

QString HandleSingleColor::message()
{
	return codec->toUnicode("单色转换成功");
}
