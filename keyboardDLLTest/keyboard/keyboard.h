#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "keyboard_global.h"
#include <QWidget>
class FormDigital;

class KEYBOARDSHARED_EXPORT Keyboard:public QObject
{
    Q_OBJECT
public:
    Keyboard(QObject *parent=NULL);
    ~Keyboard();

    void showDigital();
public slots:
    void focusChanged(QWidget *oldWidget, QWidget *newWidget);
private:
    QWidget* m_mainWidget;
//    FormDigital* m_formDigital;
};

#endif // KEYBOARD_H
