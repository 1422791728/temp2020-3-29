#include "MyThread.h"

MyThread::MyThread(QObject *parent)
	: QThread(parent)
{
	start();
}

MyThread::~MyThread()
{
	{
		//��ס���߳�
		QMutexLocker locker(&m_mutex);
		//����һ����ֹ��
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
	//��������
	IHandleImage* change = nullptr;
	//Ҫ�ı��ͼƬ��ʲô
	QImage oldImage;
	for (;;)
	{
		//��ס����������Ϊm_que���ٽ���Դ��m_currentImageҲ���ٽ�
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
