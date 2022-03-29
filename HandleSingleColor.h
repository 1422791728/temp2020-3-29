#pragma once

#include "IHandleImage.h"
#include <QtWidgets>
class HandleSingleColor : public IHandleImage
{
	Q_OBJECT

public:
	HandleSingleColor(int dep,QObject *parent = nullptr);
	~HandleSingleColor();

	virtual QImage apply(const QImage& ima) override;


	virtual QString message() override;
private:
	int depth;
};
