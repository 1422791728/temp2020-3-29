#pragma once

#include "IHandleImage.h"
#include <QtWidgets>
class HandleSpinAround : public IHandleImage
{
	Q_OBJECT

public:
	HandleSpinAround(QObject *parent = nullptr);
	~HandleSpinAround();

	virtual QImage apply(const QImage& ima) override;


	virtual QString message() override;

};
