#pragma once

#include "IHandleImage.h"
#include <QtWidgets>

class HandleResize : public IHandleImage
{
	Q_OBJECT

public:
	HandleResize(QSize& size,QObject *parent = nullptr);
	~HandleResize();

	virtual QImage apply(const QImage& ima) override;


	virtual QString message() override;

private:
	QSize m_size;
};
