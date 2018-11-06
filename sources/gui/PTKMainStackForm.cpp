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
#include <QMessageBox>

#include <QString>
#include <QRegExpValidator>
#include <QRegExp>

namespace
{
enum StackPages  {MAIN_PAGE, INPUT_DATA_PAGE_LOADT, INPUT_DATA_PAGE_TT, PROCESSING_PAGE, GROUP_PAGE};


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

QLineEdit* getLineEditByPos(QGridLayout* layout, int row, int col)
{
    QLineEdit* edit = nullptr;

    if (auto val = (layout->itemAtPosition(row, col)); val != nullptr)
    {
        edit = dynamic_cast<QLineEdit*>(val->widget());
    }
    return edit;
}
std::vector<double> AcquireInputData(QGridLayout* layout)
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
        params.resize(machine::utils::getLTExportNames().size() -1);
    }

    QLineEdit* edit1 = nullptr;
    QLineEdit* edit2 = nullptr;

    for (size_t i = 0; i < rowCount; ++i)
    {
        if (edit1 = getLineEditByPos(layout, i, 1);edit1 != nullptr)
        {
            try {
                params[i] = std::stod(edit1->text().toStdString());
            } catch (const std::exception& ex) {
                params[i] = 0;
            }
        }
        if (edit2 = getLineEditByPos(layout, i, columntCount - 1);edit2 != nullptr)
        {
            try {
                params[i + rowCount] = std::stod(edit2->text().toStdString());
            } catch (const std::exception& ex) {
                params[i + rowCount] = 0;
            }

        }

    }

    return params;
}

void ImportAquiredData(const std::vector<double>& params,
                       QGridLayout* layout)
{
    size_t columntCount = static_cast<size_t>(layout->columnCount());
    size_t rowCount = static_cast<size_t>(layout->rowCount());


    QLineEdit* edit1 = nullptr;
    QLineEdit* edit2 = nullptr;

    for (size_t i = 0; i < rowCount; ++i)
    {

        if (edit1 = getLineEditByPos(layout, i, 1);edit1 != nullptr)
        {
            edit1->setText(std::to_string(params[i]).c_str());
        }

        if (edit2 = getLineEditByPos(layout, i, columntCount - 1);edit2 != nullptr)
        {
            edit2->setText(std::to_string(params[i + rowCount]).c_str());
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
    connect(ui->backToMainPageBtnT_3,&QPushButton::clicked, this, &PTKMainStackForm::on_backToMainPageReturn);

    connect(ui->addMachine, &QPushButton::clicked, this, &PTKMainStackForm::on_addMachineLoadingTransport);
    connect(ui->addMachine_2, &QPushButton::clicked, this, &PTKMainStackForm::on_addMachineTipper);

    initTLineEditValidators(ui->inputCellsLTGridLayout);
    initTLineEditValidators(ui->inputCellsTTGridLayout);

    //init lineedit validator on processing page

    ui->workShiftLineEdit->setValidator(ui->lineEdit_3->validator());
    ui->groundWeightLineEdit->setValidator(ui->lineEdit_2->validator());
    std::unique_ptr<QRegExpValidator> validator(new QRegExpValidator(QRegExp("(([0-9]+(\\.[0-9]+){0,1})\\s)+"), this));
    ui->carriageDistanceLineEdit->setValidator(validator.release());
}

PTKMainStackForm::~PTKMainStackForm()
{
    delete ui;
}

void PTKMainStackForm::clearInputPage(QGridLayout* parent)
{
    //clear tippers by using rowcount/columncount methods
    auto columntCount = parent->columnCount();
    auto rowCount = parent->rowCount();

    ui->machineNameLineEdit_1->clear();
    ui->machineNameLineEdit_2->clear();

    QLineEdit* edit1 =nullptr;
    QLineEdit* edit2 =nullptr;

    for (int i = 0; i < rowCount; ++i)
    {

        if (edit1 = getLineEditByPos(parent, i, 1);edit1 != nullptr)
        {
            edit1->clear();
        }
        if (edit2 = getLineEditByPos(parent, i, columntCount - 1);edit2 != nullptr)
        {
            edit2->clear();
        }

    }
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
    auto path = QFileDialog::getOpenFileName(nullptr, "Выбирете путь к файлу", QDir::currentPath(),tr("*.xml"));

    if (path.isEmpty())
    {
        return;
    }

    if (ui->mainStackedWidget->currentIndex() == INPUT_DATA_PAGE_TT)
    {
        machine::Tipper tipper;
        tipper.Import(path.toStdString());
        ui->machineNameLineEdit_2->setText(tipper.getName().c_str());

        ImportAquiredData(tipper.getParams(), ui->inputCellsTTGridLayout);
    }
    else
    {
        machine::LoadingTransport loadT;
        loadT.Import(path.toStdString());
        ui->machineNameLineEdit_1->setText(loadT.getName().c_str());
        ImportAquiredData(loadT.getParams(), ui->inputCellsLTGridLayout);

    }
}

void PTKMainStackForm::on_addMachineTipper()
{
    QString machineName = ui->machineNameLineEdit_2->text();
    if (machineName.isEmpty())
    {
        QMessageBox::warning(this, tr("Предупреждение"),
                             tr("Заполните все поля!"),
                             QMessageBox::Ok);
        return;
    }

    std::vector<double> params = AcquireInputData(ui->inputCellsTTGridLayout);

    tippers.emplace_back(new machine::Tipper(machineName.toStdString(), params));

}

void PTKMainStackForm::on_addMachineLoadingTransport()
{
    QString machineName = ui->machineNameLineEdit_1->text();
    std::vector<double> params = AcquireInputData(ui->inputCellsLTGridLayout);

    if (machineName.isEmpty())
    {
        QMessageBox::warning(this, tr("Предупреждение"),
                             tr("Заполните все поля!"),
                             QMessageBox::Ok);
        return;
    }

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
        QString machineName = ui->machineNameLineEdit_2->text();
        std::vector<double> params = AcquireInputData(ui->inputCellsTTGridLayout);

        machine::Tipper tipper(machineName.toStdString(), params);
        tipper.Export(path.toStdString());
    }
    else
    {
        QString machineName = ui->machineNameLineEdit_1->text();
        std::vector<double> params = AcquireInputData(ui->inputCellsLTGridLayout);

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
    QLineEdit* edit2 = nullptr;

    for (int i = 0; i < rowCount; ++i)
    {

        if (edit1 = getLineEditByPos(layout, i, 1);edit1 != nullptr)
        {
            edit1->setValidator(reVal);
        }
        if (edit2 = getLineEditByPos(layout, i, columntCount - 1);edit2 != nullptr)
        {
            edit2->setValidator(reVal);
        }
        edit1 = dynamic_cast<QLineEdit*>(layout->itemAtPosition(i, 1)->widget());
    }
}

void PTKMainStackForm::on_toProcessingPageBtn_clicked()
{
    auto loadTransportLblTxt = ui->loadTransportLbl->text().split(':')[0];
    auto tipperLblTxt = ui->tipperCountLbl->text().split(':')[0];
    ui->loadTransportLbl->setText(loadTransportLblTxt  + ": " + std::to_string(ltransports.size()).c_str());
    ui->tipperCountLbl->setText(tipperLblTxt + ": " + std::to_string(tippers.size()).c_str());

    ui->mainStackedWidget->setCurrentIndex(PROCESSING_PAGE);
}


void PTKMainStackForm::on_processingBtn_2_clicked()
{
        auto path = QFileDialog::getSaveFileName(nullptr, "Выбирете путь к файлу", QDir::currentPath(),tr("*.xlsx"));
//        path = path.replace('/', '\\');
//        auto path = QString("path2.xlsx");
    std::string ps = path.toStdString();

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
    ptk.Processing(ps);
}
