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
	void openFile();//打开

	bool saveFile();//保存

	bool saveAsFile();//另存为

	void upsideDownImage();//上下翻转

	void spinAroudImage();//上下翻转

	void resizeImage();//缩放图片

	void monochromeImage();//单色图片

	void aboutQt();//关于QT

	void doAllChangeAction();//对于处理所有动作

private:
	bool okToContinue();//是否继续执行

	void loadFile(const QString& str);//加载文件

	bool saveCurrentFile(const QString& str);//保存文件

	void setCurrentFile(const QString& str);//设置当前文件名

	void addChangeAction(IHandleImage * h);//加入图片转换的动作

	QString strippedFileName(const QString &fullFilename);//取得文件名

	
	QLabel* ptr_imageLabel = nullptr;//设置要展示的图片的容器

	QString m_currentFile;//当前打开的图片的名字

	MyThread m_thread;//线程转换对象

	QByteArray m_format;//图片类型
	QTextCodec* codec = QTextCodec::codecForName("GBK");
};
