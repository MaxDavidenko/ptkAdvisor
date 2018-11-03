#ifndef PTKMAINSTACKFORM_H
#define PTKMAINSTACKFORM_H

#include <QWidget>
#include <QGridLayout>
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

    void on_inputTipperBtn_clicked();



    void on_backToMainPageReturn();
    void on_exportClicked();
    void on_importClicked();

    void on_addMachineTipper();
    void on_addMachineLoadingTransport();

    void on_toProcessingPageBtn_clicked();


    void on_processingBtn_2_clicked();

private:
    void clearInputPage(QGridLayout* parent);
    void initTLineEditValidators(QGridLayout* layout);
private:
    bool inputDataTipper;
    Ui::PTKMainStackForm *ui;
    std::list<std::shared_ptr<machine::Tipper>> tippers;
    std::list<std::shared_ptr<machine::LoadingTransport>> ltransports;
};

#endif // PTKMAINSTACKFORM_H
