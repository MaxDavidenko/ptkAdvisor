#include "PTKMainStackForm.h"
#include "ui_PTKMainStackForm.h"
#include "loadingtransport.h"
#include <memory>

#include <QCheckBox>
#include <QSpacerItem>
#include <QTextEdit>
namespace
{
    enum StackPages  {MAIN_PAGE, INPUT_DATA_PAGE, PROCESSING_PAGE, GROUP_PAGE};

    std::shared_ptr<QHBoxLayout> createHBoxWithLabelAndEdit(QWidget* parent, const std::string labelName)
    {
        std::shared_ptr<QHBoxLayout> layout (new QHBoxLayout(parent));

        layout->addWidget(new QLabel(labelName.c_str()));
        layout->insertSpacerItem(1, new QSpacerItem(10, 10));
        layout->addWidget(new QTextEdit());

        return layout;
    }
}

PTKMainStackForm::PTKMainStackForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PTKMainStackForm)
{
    ui->setupUi(this);
}

PTKMainStackForm::~PTKMainStackForm()
{
    delete ui;
}

void PTKMainStackForm::on_inputLoadTransportBtn_clicked()
{
    auto * stackedWidget = ui->mainStackedWidget;
    stackedWidget->setCurrentIndex(INPUT_DATA_PAGE);

    const size_t firstColumnCapacity = machine::LoadingTransportParamsSize / 2;
    const size_t secondColumnCapacity = machine::LoadingTransportParamsSize - firstColumnCapacity;

    for (size_t i = 0; i < firstColumnCapacity; ++i)
    {
        auto value = createHBoxWithLabelAndEdit(ui->firstInputVLayout, machine::loadingT::exportNames[i]);
        ui->firstInputVLayout->insertWidget(*value);
    }

    for (auto paramIndex = firstColumnCapacity; paramIndex < secondColumnCapacity; ++paramIndex)
    {
        auto value = createHBoxWithLabelAndEdit(ui->secondInputVLayout, machine::loadingT::exportNames[i]);
        ui->secondInputVLayout->insertWidget(*value);
    }

}


void PTKMainStackForm::on_backToMainPage_clicked()
{
   ui->mainStackedWidget->setCurrentIndex(0);
}
