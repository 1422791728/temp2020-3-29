#include "HandleResize.h"
//tempceshi
HandleResize::HandleResize(QSize& size ,QObject *parent)
	: IHandleImage(parent)
{
	m_size = size;
	int temp = 1;
}

HandleResize::~HandleResize()
{
}

QImage HandleResize::apply(const QImage& ima)
{
	return ima.scaled(m_size.width(), m_size.height());
}

QString HandleResize::message()
{
	return codec->toUnicode("Ëõ·ÅÍê³É");
}
