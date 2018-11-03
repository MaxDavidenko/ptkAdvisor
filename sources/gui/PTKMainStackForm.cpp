#include "PTKMainStackForm.h"
#include "ui_PTKMainStackForm.h"
#include "loadingtransport.h"
#include "tipper.h"
#include "ptk.h"
#include "ptkutils.h"
#include "xlsxwriterpp/workbook.hpp"

#include <memory>
#include <assert.h>

#include <QCheckBox>
#include <QSpacerItem>
#include <QLineEdit>
#include <QFileDialog>
#include <QString>
#include <QRegExpValidator>
#include <QRegExp>

namespace
{
enum StackPages  {MAIN_PAGE, INPUT_DATA_PAGE_LOADT, INPUT_DATA_PAGE_TT, PROCESSING_PAGE, GROUP_PAGE};


void clearInputPage(QGridLayout* parent)
{
    //clear tippers by using rowcount/columncount methods
    auto columntCount = parent->columnCount();
    auto rowCount = parent->rowCount();

    for (int i = 0; i < rowCount; ++i)
    {
        QLineEdit* edit1 = dynamic_cast<QLineEdit*>(parent->itemAtPosition(i, 1)->widget());
        QLineEdit* edit2 = dynamic_cast<QLineEdit*>(parent->itemAtPosition(i, columntCount - 1)->widget());
        edit1->clear();
        edit2->clear();
    }
}

std::vector<double> parseCarriageDistances(const QString& text)
{
    QStringList valuesList = text.split(" ");
    std::vector<double> values;

    for (const auto& value : valuesList)
    {
        values.emplace_back(value.toDouble());
    }
    return  values;
}
std::vector<double> AcquireInputData(QGridLayout* layout, QString& name)
{
    size_t columntCount = layout->columnCount();
    size_t rowCount = layout->rowCount();
    std::vector<double> params;
    if (rowCount < 7)
    {
        params.resize(machine::utils::getTTExportNames().size() -1);
    }
    else
    {
        params.resize(machine::utils::getLTExportNames().size());
    }

    QLineEdit* edit1 = dynamic_cast<QLineEdit*>(layout->itemAtPosition(0, 1)->widget());
    QLineEdit* edit2 = dynamic_cast<QLineEdit*>(layout->itemAtPosition(0, columntCount - 1)->widget());

    name = edit1->text();
    params[rowCount -1] = std::stod(edit2->text().toStdString());

    for (size_t i = 1, k = 0; i < rowCount; ++i, ++k)
    {
        edit1 = dynamic_cast<QLineEdit*>(layout->itemAtPosition(i, 1)->widget());
        edit2 = dynamic_cast<QLineEdit*>(layout->itemAtPosition(i, columntCount - 1)->widget());

        if (edit1 != nullptr)
        {
            params[k] = std::stod(edit1->text().toStdString());
        }
        if (edit2 != nullptr)
        {
            params[k + rowCount] = std::stod(edit2->text().toStdString());
        }

    }

    return params;
}

void ImportAquiredData(const std::string& tname,
                       const std::vector<double>& params,
                       QGridLayout* layout)
{
    size_t columntCount = static_cast<size_t>(layout->columnCount());
    size_t rowCount = static_cast<size_t>(layout->rowCount());

    QLineEdit* edit1 = dynamic_cast<QLineEdit*>(layout->itemAtPosition(0, 1)->widget());
    QLineEdit* edit2 = dynamic_cast<QLineEdit*>(layout->itemAtPosition(0, columntCount - 1)->widget());

    edit1->setText(tname.c_str());
    if (edit2 != nullptr)
    {
        edit2->setText(std::to_string(params[rowCount + 1]).c_str()); // 7 element and after him
    }
    for (size_t i = 1, k = 0; i < rowCount; ++i, ++k)
    {
        edit1 = dynamic_cast<QLineEdit*>(layout->itemAtPosition(i, 1)->widget());
        edit2 = dynamic_cast<QLineEdit*>(layout->itemAtPosition(i, columntCount - 1)->widget());

        if (edit1 != nullptr)
        {
            edit1->setText(std::to_string(params[k]).c_str());
        }

        if (edit2 != nullptr)
        {
            edit2->setText(std::to_string(params[k + rowCount]).c_str());
        }

    }

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

    connect(ui->importDataButton, &QPushButton::clicked, this, &PTKMainStackForm::on_importClicked);
    connect(ui->importDataButton_2, &QPushButton::clicked, this, &PTKMainStackForm::on_importClicked);

    connect(ui->exportDataButton, &QPushButton::clicked, this, &PTKMainStackForm::on_exportClicked);
    connect(ui->exportDataButton_2, &QPushButton::clicked, this, &PTKMainStackForm::on_exportClicked);

    connect(ui->backToMainPageBtnT,&QPushButton::clicked, this, &PTKMainStackForm::on_backToMainPageReturn);
    connect(ui->backToMainPageBtnT_2,&QPushButton::clicked, this, &PTKMainStackForm::on_backToMainPageReturn);

    connect(ui->addMachine, &QPushButton::clicked, this, &PTKMainStackForm::on_addMachineLoadingTransport);
    connect(ui->addMachine_2, &QPushButton::clicked, this, &PTKMainStackForm::on_addMachineTipper);

    initTLineEditValidators(ui->inputCellsLTGridLayout);
    initTLineEditValidators(ui->inputCellsTTGridLayout);

    //init lineedit validator on processing page

    ui->workShiftLineEdit->setValidator(ui->lineEdit_3->validator());
    ui->groundWeightLineEdit->setValidator(ui->lineEdit_2->validator());
    std::unique_ptr<QRegExpValidator> validator(new QRegExpValidator(QRegExp("(([0-9]+\\.{0,1}[0-9]+)\\s)+"), this));
    ui->carriageDistanceLineEdit->setValidator(validator.release());
}

PTKMainStackForm::~PTKMainStackForm()
{
    delete ui;
}

void PTKMainStackForm::on_inputLoadTransportBtn_clicked()
{
    auto * stackedWidget = ui->mainStackedWidget;

    clearInputPage(ui->inputCellsLTGridLayout);

    stackedWidget->setCurrentIndex(INPUT_DATA_PAGE_LOADT);
}

void PTKMainStackForm::on_inputTipperBtn_clicked()
{
    auto * stackedWidget = ui->mainStackedWidget;

    clearInputPage(ui->inputCellsTTGridLayout);

    stackedWidget->setCurrentIndex(INPUT_DATA_PAGE_TT);

}

void PTKMainStackForm::on_importClicked()
{
    auto path = QFileDialog::getOpenFileName(nullptr, "Выбирете путь к файлу", tr("file.xml"));

    if (path.isEmpty())
    {
        return;
    }

    if (ui->mainStackedWidget->currentIndex() == INPUT_DATA_PAGE_TT)
    {
        machine::Tipper tipper;
        tipper.Import(path.toStdString());
        ImportAquiredData(
                    tipper.getName(),
                    tipper.getParams(),
                    ui->inputCellsTTGridLayout);
    }
    else
    {
        machine::LoadingTransport loadT;
        loadT.Import(path.toStdString());
        ImportAquiredData(
                    loadT.getName(),
                    loadT.getParams(),
                    ui->inputCellsLTGridLayout);
    }
}

void PTKMainStackForm::on_addMachineTipper()
{
    QString machineName;
    std::vector<double> params = AcquireInputData(ui->inputCellsTTGridLayout, machineName);

    tippers.emplace_back(new machine::Tipper(machineName.toStdString(), params));

}

void PTKMainStackForm::on_addMachineLoadingTransport()
{
    QString machineName;
    std::vector<double> params = AcquireInputData(ui->inputCellsLTGridLayout, machineName);

    ltransports.emplace_back(new machine::LoadingTransport (machineName.toStdString(), params));
}

void PTKMainStackForm::on_exportClicked()
{
    auto path = QFileDialog::getSaveFileName(nullptr, "Выбирете путь к файлу", tr("file.xml"));

    if (path.isEmpty())
    {
        return;
    }

    if (ui->mainStackedWidget->currentIndex() == INPUT_DATA_PAGE_TT)
    {
        QString machineName;
        std::vector<double> params = AcquireInputData(ui->inputCellsTTGridLayout, machineName);

        machine::Tipper tipper(machineName.toStdString(), params);
        tipper.Export(path.toStdString());
    }
    else
    {
        QString machineName;
        std::vector<double> params = AcquireInputData(ui->inputCellsLTGridLayout, machineName);

        machine::LoadingTransport lt(machineName.toStdString(), params);
        lt.Export(path.toStdString());
    }
}

void PTKMainStackForm::on_backToMainPageReturn()
{
    ui->mainStackedWidget->setCurrentIndex(MAIN_PAGE);
}

void PTKMainStackForm::initTLineEditValidators(QGridLayout* layout)
{
    QRegExpValidator *reVal = new QRegExpValidator(QRegExp("[0-9]+\\.[0-9]+"), this);

    auto columntCount = layout->columnCount();
    auto rowCount = layout->rowCount();

    QLineEdit* edit1 = nullptr; // first is for name
    QLineEdit* edit2 = dynamic_cast<QLineEdit*>(layout->itemAtPosition(0, columntCount - 1)->widget());

    edit2->setValidator(reVal);

    for (int i = 1; i < rowCount; ++i)
    {
        edit1 = dynamic_cast<QLineEdit*>(layout->itemAtPosition(i, 1)->widget());
        edit2 = dynamic_cast<QLineEdit*>(layout->itemAtPosition(i, columntCount - 1)->widget());

        edit1->setValidator(reVal);
        if (edit2 != nullptr)
        {
            edit2->setValidator(reVal);
        }
    }
}

void PTKMainStackForm::on_toProcessingPageBtn_clicked()
{
    ui->mainStackedWidget->setCurrentIndex(PROCESSING_PAGE);
}


void PTKMainStackForm::on_processingBtn_2_clicked()
{
    auto path = QFileDialog::getSaveFileName(nullptr, "Выбирете путь к файлу", tr("PTK.xlsx"));

    if (ui->carriageDistanceLineEdit->text().isEmpty())
    {
        return;
    }

    std::vector<double> carriageDistances = parseCarriageDistances(ui->carriageDistanceLineEdit->text());
    double workShift = ui->workShiftLineEdit->text().toDouble();
    double groundWeight = ui->groundWeightLineEdit->text().toDouble();

    // generate pairs for tippers
    machine::MachineComplex_map mmap;
    for (const auto& tipper: tippers)
    {
        std::vector<std::shared_ptr<machine::LoadingTransport>> lt(ltransports.begin(), ltransports.end());

        mmap.insert({tipper, lt});
    }

    machine::PTK ptk(workShift, groundWeight, std::move(carriageDistances), std::move(mmap));
    xlsxwriter::Workbook workbook(path.toStdString());
    workbook.add_worksheet("ПТК");

    ptk.Processing(workbook);
    workbook.close();
}
