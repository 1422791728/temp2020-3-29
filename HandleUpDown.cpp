#include "HandleUpDown.h"

HandleUpDown::HandleUpDown(QObject *parent)
	: IHandleImage(parent)
{
}

HandleUpDown::~HandleUpDown()
{
}

QImage HandleUpDown::apply(const QImage& ima)
{
	return ima.mirrored(false, true);
}

QString HandleUpDown::message()
{
	return codec->toUnicode("上下旋转完成");
}
