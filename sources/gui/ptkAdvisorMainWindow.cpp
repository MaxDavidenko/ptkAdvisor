#include "ptkAdvisorMainWindow.h"
#include "PTKMainStackForm.h"
#include "ui_ptkAdvisorMainWindow.h"

ptkAdvisorMainWindow::ptkAdvisorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ptkAdvisorMainWindow),
    stackForm(new PTKMainStackForm())
{
    ui->setupUi(this);
    stackForm->hide();

}

ptkAdvisorMainWindow::~ptkAdvisorMainWindow()
{
    delete ui;
}

void ptkAdvisorMainWindow::on_pushButton_clicked()
{
    stackForm->show();
    this->hide();
}
