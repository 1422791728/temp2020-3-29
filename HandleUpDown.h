#pragma once

#include "IHandleImage.h"
#include <QtWidgets>
class HandleUpDown : public IHandleImage
{
	Q_OBJECT

public:
	HandleUpDown(QObject *parent = nullptr);
	~HandleUpDown();

	virtual QImage apply(const QImage& ima) override;


	virtual QString message() override;

};
