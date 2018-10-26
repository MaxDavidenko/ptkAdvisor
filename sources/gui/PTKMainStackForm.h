#ifndef PTKMAINSTACKFORM_H
#define PTKMAINSTACKFORM_H

#include <QWidget>

namespace Ui {
class PTKMainStackForm;
}

class PTKMainStackForm : public QWidget
{
    Q_OBJECT

public:
    explicit PTKMainStackForm(QWidget *parent = nullptr);
    ~PTKMainStackForm();

private slots:
    void on_inputLoadTransportBtn_clicked();

    void on_backToMainPage_clicked();

private:
    Ui::PTKMainStackForm *ui;
};

#endif // PTKMAINSTACKFORM_H
