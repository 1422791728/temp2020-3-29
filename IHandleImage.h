#pragma once

#include <QObject>
#include <QtWidgets>
class IHandleImage : public QObject
{
	Q_OBJECT

public:
	IHandleImage(QObject *parent);
	~IHandleImage();
	virtual QImage apply(const QImage& ima) = 0;//�ӿڷ��� �Ѵ�����ͼƬ�����Ҫ��ͼƬ;
	virtual QString message() = 0; //�ӿڷ����Ѵ���������Ϣ���͵�״̬����
protected:
	QTextCodec* codec = QTextCodec::codecForName("GBK");
};
