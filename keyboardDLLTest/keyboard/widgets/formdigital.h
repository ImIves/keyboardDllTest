#ifndef FORMDIGITAL_H
#define FORMDIGITAL_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
class FormDigital;
}

class FormDigital : public QWidget
{
    Q_OBJECT

public:
    explicit FormDigital(QWidget *parent = 0);
    ~FormDigital();
    void setInputEdit(QWidget *inputEdit);

public slots:
    void clickButton(int index);
    void showKeyboard(QPoint pt, QRect focusWidget);
    void hideKeyboard();
    bool isVisible() const;
    void pressKey(int key);
    void focusChanged(QWidget* oldWidget,QWidget* newWidget);
signals:
    void commit(QString str);
private:
    Ui::FormDigital *ui;
    QLineEdit *inputEdit;
    QWidget* m_inputEdit;
};

#endif // FORMDIGITAL_H
