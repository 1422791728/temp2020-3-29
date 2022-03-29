#pragma once

#include <QObject>
#include <QtWidgets>
class IHandleImage : public QObject
{
	Q_OBJECT

public:
	IHandleImage(QObject *parent);
	~IHandleImage();
	virtual QImage apply(const QImage& ima) = 0;//接口方法 把传进来图片变成想要的图片;
	virtual QString message() = 0; //接口方法把传进来的消息发送到状态框中
protected:
	QTextCodec* codec = QTextCodec::codecForName("GBK");
};
