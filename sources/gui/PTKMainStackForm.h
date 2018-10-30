#ifndef PTKMAINSTACKFORM_H
#define PTKMAINSTACKFORM_H

#include <QWidget>
#include <list>
#include <memory>
#include "tipper.h"
#include "loadingtransport.h"

class PTK;

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

    void on_inputTipperBtn_clicked();

    void on_processingBtn_clicked();

    void on_importDataButton_clicked();

    void on_exportDataButton_clicked();

    void on_createPTKBtn_clicked();

private:
    bool inputDataTipper;
    Ui::PTKMainStackForm *ui;
    std::list<std::shared_ptr<machine::Tipper>> tippers;
    std::list<std::shared_ptr<machine::LoadingTransport>> ltransports;
};

#endif // PTKMAINSTACKFORM_H
