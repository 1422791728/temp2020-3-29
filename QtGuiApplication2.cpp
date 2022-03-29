#include "QtGuiApplication2.h"
#include "HandleSpinAround.h"
#include "HandleResize.h"
#include "HandleUpDown.h"
#include "HandleSingleColor.h"
#include "ui_resizeDialog.h"
QtGuiApplication2::QtGuiApplication2(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionAboutQt,&QAction::triggered,this,&QtGuiApplication2::aboutQt);
	connect(ui.actionExit, &QAction::triggered, this, &QtGuiApplication2::close);
	connect(ui.actionmonochorme, &QAction::triggered, this, &QtGuiApplication2::monochromeImage);
	connect(ui.actionOpen, &QAction::triggered, this, &QtGuiApplication2::openFile);
	connect(ui.actionResize, &QAction::triggered, this, &QtGuiApplication2::resizeImage);
	connect(ui.actionSave, &QAction::triggered, this, static_cast<bool (QtGuiApplication2::*)()>(&QtGuiApplication2::saveFile));
	connect(ui.actionSaveAs, &QAction::triggered, this, &QtGuiApplication2::saveAsFile);
	connect(ui.actionSpinAroud, &QAction::triggered, this, &QtGuiApplication2::spinAroudImage);
	connect(ui.actionUpsideDown, &QAction::triggered, this, &QtGuiApplication2::upsideDownImage);


	ptr_imageLabel = new QLabel;
	//设置QLabel背景
	ptr_imageLabel->setBackgroundRole(QPalette::Dark);
	ptr_imageLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	setCentralWidget(ptr_imageLabel);
	
	statusBar()->showMessage(codec->toUnicode("准备"), 2000);

	connect(&m_thread, SIGNAL(changeImageStart()), statusBar(), SLOT(showMessage()));
	connect(&m_thread, SIGNAL(changeImageEnd()), this, SLOT(doAllChangeAction()));

	setCurrentFile("");
}

void QtGuiApplication2::openFile()
{
	if (okToContinue())
	{
		QString filename = QFileDialog::getOpenFileName(this);
		if (!filename.isEmpty())
		{
			loadFile(filename);
		}

	}
}

bool QtGuiApplication2::okToContinue()
{
	if (isWindowModified())
	{
		QMessageBox::StandardButton button = QMessageBox::warning(nullptr, codec->toUnicode("图片编辑器"), 
			codec->toUnicode("图片被修改过是否保存"),QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel);
		if (button == QMessageBox::Yes)
		{
			return saveFile();
		}
		else if(button == QMessageBox::Cancel)
		{
			return false;
		}
	}
	return true;
}

void QtGuiApplication2::loadFile(const QString& str)
{
	QImage t_image;
	QApplication::setOverrideCursor(Qt::WaitCursor);
	bool loaded = t_image.load(str);
	QApplication::restoreOverrideCursor();

	if (loaded)
	{
		m_thread.setCurrentImage(t_image);
		m_format = QImageReader::imageFormat(str);

		ptr_imageLabel->setPixmap(QPixmap::fromImage(t_image));

		statusBar()->showMessage(codec->toUnicode("图片加载成功"), 3000);

		setCurrentFile(str);
	}
	else
	{
		 QMessageBox::warning(nullptr, codec->toUnicode("图片编辑器"),
			codec->toUnicode("打开的文件不是图片"));
	}
	

}

bool QtGuiApplication2::saveFile()
{
	if (m_currentFile.isEmpty())
	{
		return saveAsFile();
	}
	else
	{
		return saveCurrentFile(m_currentFile);
	}
}

bool QtGuiApplication2::saveCurrentFile(const QString& str)
{
	QImage t_image = m_thread.getCurrentImage();
	QApplication::setOverrideCursor(Qt::WaitCursor);
	bool saved = t_image.save(str);
	QApplication::restoreOverrideCursor();
	if (saved)
	{
		setCurrentFile(str);
		statusBar()->showMessage(codec->toUnicode("保存成功"), 3000);
		return true;
	}
	else
	{
		QMessageBox::warning(nullptr, codec->toUnicode("图片编辑器"),
			codec->toUnicode("图片没有保存成功"));
		return false;
	}
}

void QtGuiApplication2::setCurrentFile(const QString& str)
{
	m_currentFile = str;

	setWindowModified(false);

	bool hasImage = !str.isEmpty();
	if (hasImage)
	{
		setWindowTitle(codec->toUnicode("%1图片[*]").arg(str));
	}
	else
	{
		setWindowTitle(codec->toUnicode("未定义的"));
	}
	ui.actionSave->setEnabled(hasImage);
	ui.actionSaveAs->setEnabled(hasImage);
	ui.actionmonochorme->setEnabled(hasImage);
	ui.actionResize->setEnabled(hasImage);
	ui.actionSpinAroud->setEnabled(hasImage);
	ui.actionUpsideDown->setEnabled(hasImage);
}

void QtGuiApplication2::addChangeAction(IHandleImage* h)
{
	m_thread.addChangeAction(h);
}

QString QtGuiApplication2::strippedFileName(const QString& fullFilename)
{
	return QFileInfo(fullFilename).fileName();
}

bool QtGuiApplication2::saveAsFile()
{
	QString fileName = QFileDialog::getSaveFileName(this);
	if (QFile::exists(fileName))
	{
		QMessageBox::StandardButton button = QMessageBox::warning(nullptr, codec->toUnicode("图片编辑器"),
			codec->toUnicode("图片已经存在，是否覆盖"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		if (button == QMessageBox::Yes)
		{
			return true;
		}
		else if (button == QMessageBox::Cancel)
		{
			return false;
		}
	}
	else
	{
		saveCurrentFile(fileName);
	}
	return true;
}

void QtGuiApplication2::upsideDownImage()
{
	addChangeAction(new HandleUpDown);
}

void QtGuiApplication2::spinAroudImage()
{
	addChangeAction(new HandleSpinAround);
}

void QtGuiApplication2::resizeImage()
{
	QDialog t_dialog;
	Ui::resizeDialog t;
	t.setupUi(&t_dialog);
	t.lengthSpinBox->setValue(ptr_imageLabel->pixmap()->width());
	t.widthSpinBox->setValue(ptr_imageLabel->pixmap()->height());
	if (t_dialog.exec())
	{
		QSize newSize(t.lengthSpinBox->value(), t.widthSpinBox->value());
		addChangeAction(new HandleResize(newSize));
	}
	
}

void QtGuiApplication2::monochromeImage()
{
	addChangeAction(new HandleSingleColor(1));
}

void QtGuiApplication2::aboutQt()
{
	QApplication::aboutQt();
}

void QtGuiApplication2::doAllChangeAction()
{
	ui.actionSave->setEnabled(true);
	ui.actionSaveAs->setEnabled(true);
	ptr_imageLabel->setPixmap(QPixmap::fromImage(m_thread.getCurrentImage()));
	setWindowModified(true);
	statusBar()->showMessage(codec->toUnicode("准备"), 3000);
}
