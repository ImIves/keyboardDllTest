#include "keyboard.h"
#include "widgets/formdigital.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QDebug>

Keyboard::Keyboard(QObject *parent) :
    QObject(parent)
    ,m_mainWidget(NULL)
{
//    m_formDigital = new FormDigital();

}

Keyboard::~Keyboard()
{
//    if(m_formDigital)
//    {
//        delete m_formDigital;
//        m_formDigital = NULL;
//    }
}

void Keyboard::showDigital()
{
    // 绑定全局改变焦点信号槽
    //disconnect(other
    connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)),
            this, SLOT(focusChanged(QWidget *, QWidget *)));

}

void Keyboard::focusChanged(QWidget *oldWidget, QWidget *newWidget)
{
    qDebug()<<"focusChanged:"<<oldWidget<<newWidget;
    if(newWidget && (newWidget->inherits("QTextEdit")
        || newWidget->inherits("QLineEdit")))
    {
        if(!m_mainWidget)
        {
            m_mainWidget = new FormDigital(newWidget->parentWidget());
            qDebug()<<"m_mainWidget Created!"<<newWidget<<newWidget->parentWidget();
        }
        else
        {
            qDebug()<<"m_mainWidget is Exist!";
        }
        FormDigital* pDigital = static_cast<FormDigital*>(m_mainWidget);
        pDigital->setInputEdit(newWidget);
    }
    else
    {
        if(m_mainWidget)
        {
            m_mainWidget->close();
            delete m_mainWidget;
            m_mainWidget = NULL;
            qDebug()<<"m_mainWidget is Deleted!";
        }
        qDebug()<<"m_mainWidget is NULL!";
        return;
    }

    //设置样式表
    QFile file(":/res/keyboard.css");
    if (file.open(QFile::ReadOnly))
    {
        QString css = QLatin1String(file.readAll());
        m_mainWidget->setStyleSheet(css);
    }
    file.close();
    //设置固定键盘高度
    int nFixHeight = 270;
    int nFixWidth = 360;
    m_mainWidget->setFixedSize(nFixWidth,nFixHeight);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    int gWidth = screenRect.width();
    int gHeight = screenRect.height();
    m_mainWidget->setGeometry(QRect(gWidth/2-nFixWidth/2,gHeight-nFixHeight,nFixWidth,nFixHeight));
    m_mainWidget->show();
}
