#include "PTKMainStackForm.h"
#include "ui_PTKMainStackForm.h"
#include "loadingtransport.h"
#include "tipper.h"
#include "ptkutils.h"
#include <memory>
#include <assert.h>

#include <QCheckBox>
#include <QSpacerItem>
#include <QLineEdit>
#include <QFileDialog>
#include <QString>

namespace
{
enum StackPages  {MAIN_PAGE, INPUT_DATA_PAGE, PROCESSING_PAGE, GROUP_PAGE};

QHBoxLayout* CreateHBoxWithLabelAndEdit(std::string_view labelName)
{
    QHBoxLayout* layout (new QHBoxLayout());

    layout->addWidget(new QLabel(labelName.data()));
    layout->insertSpacerItem(1, new QSpacerItem(10, 10));
    layout->addWidget(new QLineEdit());

    return layout;
}


void FillInputPage(const std::vector<std::string_view>& labelsNames,
                   QBoxLayout* parent,
                   QVBoxLayout* firstInputVLayout,
                   QVBoxLayout* secondInputVLayout)
{
    const size_t firstColumnCapacity = labelsNames.size() / 2;
    const size_t secondColumnCapacity = labelsNames.size() - firstColumnCapacity;

    for (size_t i = 0; i < firstColumnCapacity; ++i)
    {
        QHBoxLayout* value = CreateHBoxWithLabelAndEdit(labelsNames.at(i));
        firstInputVLayout->addLayout(value);
    }

    for (auto i = firstColumnCapacity; i < firstColumnCapacity + secondColumnCapacity; ++i)
    {
        QHBoxLayout* value = CreateHBoxWithLabelAndEdit(labelsNames.at(i));
        secondInputVLayout->addLayout(value);
    }
}

std::vector<double> AcquireInputData(QVBoxLayout* firstInputVLayout,
                                     QVBoxLayout* secondInputVLayout)
{
    auto children = firstInputVLayout->children() + secondInputVLayout->children();
    //    auto secondChildren = firstInputVLayout->children();
    std::vector<double> params(children.size());


    // start from 1 and before this read data from 0 element for datfill the name of machine.
    // return pair with <name, vector>

    for (const auto& child : children)
    {
        QLineEdit* dataEdit = dynamic_cast<QLineEdit*>(child->children().at(1));
        if (dataEdit != nullptr)
        {
            auto strData = dataEdit->text().toStdString();
            double param = 0;
            try {
                param = std::stod(strData);
            } catch (const std::exception& ex) {
                //add log
                assert(true && ex.what());

                param = 0;
            }
            params.push_back(param);
        }
    }
    return params;
}
std::vector<double> ImportAquiredData(const std::vector<double>& params,
                                      QVBoxLayout* firstInputVLayout,
                                      QVBoxLayout* secondInputVLayout)
{
    auto children1 = firstInputVLayout->children();
    size_t index = 0;

    for (const auto& child : children1)
    {
        QLineEdit* dataEdit = dynamic_cast<QLineEdit*>(child->children().at(1));
        if (dataEdit != nullptr)
        {
            dataEdit->setText(std::to_string(params[index++]).c_str());
        }
    }

    auto children2 = secondInputVLayout->children();

    for (const auto& child : children2)
    {
        QLineEdit* dataEdit = dynamic_cast<QLineEdit*>(child->children().at(1));
        if (dataEdit != nullptr)
        {
            dataEdit->setText(std::to_string(params[index++]).c_str());
        }
    }
    return params;
}

}

PTKMainStackForm::PTKMainStackForm(QWidget *parent) :
    QWidget(parent),
    inputDataTipper(false),
    ui(new Ui::PTKMainStackForm)
{
    ui->setupUi(this);
    connect(ui->inputLoadTransportBtn, &QPushButton::clicked, this, [this]{ this->inputDataTipper = false;});
    connect(ui->inputTipperBtn, &QPushButton::clicked, this, [this]{ this->inputDataTipper = true;});
}

PTKMainStackForm::~PTKMainStackForm()
{
    delete ui;
}

void PTKMainStackForm::on_inputLoadTransportBtn_clicked()
{
    auto * stackedWidget = ui->mainStackedWidget;
    stackedWidget->setCurrentIndex(INPUT_DATA_PAGE);

    if (ui->firstInputVLayout->children().size() > 0)
    {
        qDeleteAll(ui->firstInputVLayout->findChildren<QBoxLayout*>("", Qt::FindDirectChildrenOnly));
        qDeleteAll(ui->firstInputVLayout->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
        qDeleteAll(ui->secondInputVLayout->findChildren<QBoxLayout*>("", Qt::FindDirectChildrenOnly));
    qDeleteAll(ui->secondInputVLayout->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
    }

    FillInputPage(machine::utils::getLTExportNames(),
                  ui->inputCellsVLayout,
                  ui->firstInputVLayout,
                  ui->secondInputVLayout);
}

void PTKMainStackForm::on_backToMainPage_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(0);
}

void PTKMainStackForm::on_inputTipperBtn_clicked()
{
    auto * stackedWidget = ui->mainStackedWidget;
    stackedWidget->setCurrentIndex(INPUT_DATA_PAGE);

    FillInputPage(machine::utils::getTTExportNames(),
                  ui->inputCellsVLayout,
                  ui->firstInputVLayout,
                  ui->secondInputVLayout);
}

void PTKMainStackForm::on_processingBtn_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(PROCESSING_PAGE);

    std::vector<double> params = AcquireInputData(ui->firstInputVLayout, ui->secondInputVLayout);

    if (inputDataTipper)
    {
        tippers.emplace_back(new machine::Tipper("tipper",params));
    }
    else
    {
        ltransports.emplace_back(new machine::LoadingTransport("loader", params));
    }
}

void PTKMainStackForm::on_importDataButton_clicked()
{
    auto path = QFileDialog::getSaveFileName(nullptr, "Выбирете путь к файлу", tr("XML Files (*.xml)"));
    if (inputDataTipper)
    {
        machine::Tipper tipper;
        tipper.Import(path.toStdString());
        ImportAquiredData(tipper.getParams(),
                          ui->firstInputVLayout,
                          ui->secondInputVLayout);

    }
    else
    {
        machine::LoadingTransport loadT;
        loadT.Import(path.toStdString());
        ImportAquiredData(loadT.getParams(),
                          ui->firstInputVLayout,
                          ui->secondInputVLayout);

    }
}

void PTKMainStackForm::on_exportDataButton_clicked()
{
    auto path = QFileDialog::getSaveFileName(nullptr, "Выбирете путь к файлу", tr("XML Files (*.xml)"));
    if (inputDataTipper)
    {
        std::vector<double> params = AcquireInputData(ui->firstInputVLayout, ui->secondInputVLayout);
        //        auto name = params[0]; handle names for tippers and loaders
        params.erase(params.begin());

        machine::Tipper tipper("tipper", params);
        tipper.Export(path.toStdString());
    }
    else
    {
        std::vector<double> params = AcquireInputData(ui->firstInputVLayout, ui->secondInputVLayout);
        machine::LoadingTransport loadT("loader",params);
        loadT.Export(path.toStdString());
    }
}

void PTKMainStackForm::on_createPTKBtn_clicked()
{

}
