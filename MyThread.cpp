#include "MyThread.h"

MyThread::MyThread(QObject *parent)
	: QThread(parent)
{
	start();
}

MyThread::~MyThread()
{
	{
		//锁住该线程
		QMutexLocker locker(&m_mutex);
		//加入一个终止符
		m_que.enqueue(nullptr);
		//
		m_wait.notify_one();
	}
	wait();
}

void MyThread::addChangeAction(IHandleImage* h)
{
	QMutexLocker locker(&m_mutex);
	m_que.enqueue(h);
	m_wait.notify_one();
}

QImage MyThread::getCurrentImage() 
{
	QMutexLocker locker(&m_mutex);
	return m_currentImage;
}

void MyThread::setCurrentImage(QImage val)
{
	m_currentImage = val;
}

void MyThread::run()
{
	//动作对象
	IHandleImage* change = nullptr;
	//要改变的图片是什么
	QImage oldImage;
	for (;;)
	{
		//锁住互斥量，因为m_que是临界资源且m_currentImage也是临界
		{
			QMutexLocker locker(&m_mutex);
			if (m_que.empty())
			{
				m_wait.wait(&m_mutex);
			}
			change = m_que.dequeue();
			if (change == nullptr)
			{
				break;
			}
			oldImage = m_currentImage;
		}
		emit changeImageStart(change->message());
		m_currentImage = change->apply(oldImage);
		delete change;
		{
			QMutexLocker locker(&m_mutex);
			if (m_que.isEmpty())
			{
				emit changeImageEnd();

			}
		}
	}
}
