#include "HandleSpinAround.h"

HandleSpinAround::HandleSpinAround(QObject *parent)
	: IHandleImage(parent)
{

}

HandleSpinAround::~HandleSpinAround()
{
}

QImage HandleSpinAround::apply(const QImage& ima)
{
	return ima.mirrored(true,false);
}

QString HandleSpinAround::message()
{
	return codec->toUnicode("ื๓ำาะýืชอ๊ณษ");
}
