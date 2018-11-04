#include "ptkAdvisorMainWindow.h"
#include "PTKMainStackForm.h"
#include "ui_ptkAdvisorMainWindow.h"
#include <QMovie>

ptkAdvisorMainWindow::ptkAdvisorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ptkAdvisorMainWindow),
    stackForm(new PTKMainStackForm())
{
    ui->setupUi(this);
    stackForm->hide();
    QMovie *movie = new QMovie(":/images/loading.gif");
    ui->movieLbl->setMovie(movie);
    movie->start();

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
