#ifndef PTKADVISORMAINWINDOW_H
#define PTKADVISORMAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui
{
class ptkAdvisorMainWindow;
}

class PTKMainStackForm;

class ptkAdvisorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ptkAdvisorMainWindow(QWidget *parent = nullptr);
    ~ptkAdvisorMainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ptkAdvisorMainWindow *ui;
    std::shared_ptr<PTKMainStackForm> stackForm;

};

#endif // PTKADVISORMAINWINDOW_H
