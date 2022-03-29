#pragma once

#include <QtWidgets>
#include "ui_QtGuiApplication2.h"
#include "IHandleImage.h"
#include "MyThread.h"

class QtGuiApplication2 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication2(QWidget *parent = Q_NULLPTR);


private:
	Ui::QtGuiApplication2Class ui;



public slots:
	void openFile();//��

	bool saveFile();//����

	bool saveAsFile();//���Ϊ

	void upsideDownImage();//���·�ת

	void spinAroudImage();//���·�ת

	void resizeImage();//����ͼƬ

	void monochromeImage();//��ɫͼƬ

	void aboutQt();//����QT

	void doAllChangeAction();//���ڴ������ж���

private:
	bool okToContinue();//�Ƿ����ִ��

	void loadFile(const QString& str);//�����ļ�

	bool saveCurrentFile(const QString& str);//�����ļ�

	void setCurrentFile(const QString& str);//���õ�ǰ�ļ���

	void addChangeAction(IHandleImage * h);//����ͼƬת���Ķ���

	QString strippedFileName(const QString &fullFilename);//ȡ���ļ���

	
	QLabel* ptr_imageLabel = nullptr;//����Ҫչʾ��ͼƬ������

	QString m_currentFile;//��ǰ�򿪵�ͼƬ������

	MyThread m_thread;//�߳�ת������

	QByteArray m_format;//ͼƬ����
	QTextCodec* codec = QTextCodec::codecForName("GBK");
};
