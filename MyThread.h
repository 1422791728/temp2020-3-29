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

	void addChangeAction(IHandleImage* h);//把要处理的动作加入到队列里面去
	QImage getCurrentImage() ;
	void setCurrentImage(QImage val);
signals:
	void changeImageStart(const QString& str);//改变图片开始

	void changeImageEnd();//改变图片结束
protected:

	virtual void run() override;
private:
	QImage m_currentImage;//当前图片资源

	QQueue<IHandleImage*> m_que;//处理动作的队列

	QWaitCondition m_wait;//等待条件

	QMutex m_mutex;//互斥量
};
