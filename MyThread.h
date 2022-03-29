#pragma once

#include <QThread>
#include <QtWidgets>
#include "IHandleImage.h"
class MyThread : public QThread
{
	Q_OBJECT

public:
	MyThread(QObject *parent = nullptr);
	~MyThread();

	void addChangeAction(IHandleImage* h);//��Ҫ����Ķ������뵽��������ȥ
	QImage getCurrentImage() ;
	void setCurrentImage(QImage val);
signals:
	void changeImageStart(const QString& str);//�ı�ͼƬ��ʼ

	void changeImageEnd();//�ı�ͼƬ����
protected:

	virtual void run() override;
private:
	QImage m_currentImage;//��ǰͼƬ��Դ

	QQueue<IHandleImage*> m_que;//�������Ķ���

	QWaitCondition m_wait;//�ȴ�����

	QMutex m_mutex;//������
};
