#include "formdigital.h"
#include "ui_formdigital.h"
#include <QSignalMapper>
#include <QKeyEvent>
#include <QDebug>
#include <QDesktopWidget>

FormDigital::FormDigital(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDigital),m_inputEdit(NULL)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowDoesNotAcceptFocus | Qt::FramelessWindowHint |
                       Qt::WindowStaysOnTopHint | Qt::Tool | Qt::X11BypassWindowManagerHint);

    inputEdit = new QLineEdit(this);
    inputEdit->hide();

    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_1, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_2, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_3, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_4, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_5, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_6, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_7, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_8, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->pushButton_9, SIGNAL(clicked()), signalMapper, SLOT(map()));

    signalMapper->setMapping(ui->pushButton_0, 0);
    signalMapper->setMapping(ui->pushButton_1, 1);
    signalMapper->setMapping(ui->pushButton_2, 2);
    signalMapper->setMapping(ui->pushButton_3, 3);
    signalMapper->setMapping(ui->pushButton_4, 4);
    signalMapper->setMapping(ui->pushButton_5, 5);
    signalMapper->setMapping(ui->pushButton_6, 6);
    signalMapper->setMapping(ui->pushButton_7, 7);
    signalMapper->setMapping(ui->pushButton_8, 8);
    signalMapper->setMapping(ui->pushButton_9, 9);

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(clickButton(int)));

    int nCount = ui->gridLayout->columnCount();
    nCount = ui->gridLayout->rowCount();
    for(int i=1; i < 4;i++) {
        ui->gridLayout->setColumnMinimumWidth(i,72);
    }
}

FormDigital::~FormDigital()
{
    delete ui;
}

void FormDigital::clickButton(int index)
{
    QKeyEvent *keyPressEvent = NULL;

    if (index >=0 && index < 10)
    {
        /* 0-9 */
        QString text;
        text.sprintf("%d", index);
        keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_0 + index,
                                      Qt::NoModifier, text);
    }
    else if (index == 10)
    {
        /* dot */
        keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Period,
                                      Qt::NoModifier, ".");
    }
    else if (index == 11)
    {
        /* minus */
        keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Minus,
                                      Qt::NoModifier, "-");
    }
    else if (index == 12)
    {
        /* backspace */
        keyPressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace,
                                      Qt::NoModifier);
    }
    else if (index == 13)
    {
        /* enter */
        QString str = inputEdit->text();
        emit commit(str);
        inputEdit->setText("");
        hide();
    }
    QString str = QString("%1").arg(index);
    QInputMethodEvent event;
    event.setCommitString(str);
//    QObject *focusObject = focusWidget();
//    QGuiApplication::sendEvent(focusObject, &event);
    if(m_inputEdit)
        QGuiApplication::sendEvent(m_inputEdit, &event);

    if (keyPressEvent != NULL)
    {
        QGuiApplication::postEvent(inputEdit, keyPressEvent);
    }
}

void FormDigital::pressKey(int key)
{
    QKeyEvent *keyPressEvent = NULL;
    QString text;

    qDebug() << "press key " << key << endl;

    if (key >= Qt::Key_0 && key <= Qt::Key_9)
    {
        /* 0-9 */
        text.sprintf("%d", key - Qt::Key_0);
    }
    else if (key == Qt::Key_Period)
    {
        /* dot */
        text = QString(".");
    }
    else if (key == Qt::Key_Minus)
    {
        /* minus */
        text = QString("-");
    }
    else if (key == Qt::Key_Return)
    {
        /* enter */
        qDebug() << "enter pressed" << endl;
        QString str = inputEdit->text();
        emit commit(str);
        inputEdit->setText("");
        hide();
        return;
    }
    else if (key != Qt::Key_Backspace)
    {
        return;
    }

    keyPressEvent = new QKeyEvent(QEvent::KeyPress, key,
                                  Qt::NoModifier, text);
    if (keyPressEvent != NULL)
    {
        QGuiApplication::postEvent(inputEdit, keyPressEvent);
    }

}

void FormDigital::focusChanged(QWidget *oldWidget, QWidget *newWidget)
{
    qDebug()<<"focusChanged:"<<oldWidget<<newWidget;
    if(newWidget && (newWidget->inherits("QTextEdit")
        || newWidget->inherits("QLineEdit")))
        m_inputEdit = newWidget;
    else
        m_inputEdit = NULL;
    setVisible(m_inputEdit);
}

void FormDigital::setInputEdit(QWidget *inputEdit)
{
    m_inputEdit = inputEdit;
}

void FormDigital::showKeyboard(QPoint pt, QRect focusWidget)
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect kbRect = QWidget::rect();
    QRect screenRect = desktopWidget->screenGeometry();

    qDebug() << "FormDigital show" << endl;
    qDebug() << pt.x() << " " << pt.y() << endl;

    pt.setY(pt.y() + focusWidget.height());

    QWidget::move(pt);
    QWidget::show();
}

void FormDigital::hideKeyboard()
{
    qDebug() << "FormDigital hide" << endl;
    QWidget::hide();
}

bool FormDigital::isVisible() const
{
    return QWidget::isVisible();
}
