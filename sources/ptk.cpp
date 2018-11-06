#include "ptk.h"
#include "loadingtransport.h"
#include "tipper.h"
#include <xlsxwriterpp/worksheet.hpp>

namespace
{
using namespace::machine;
const size_t OUT_PARAMS_COUNT = 18;

std::vector<std::string> columnNames = { "Дальность возки",
                                         "Рабочая смена",
                                         "Объемная масса грунта",
                                         "Название самосвала",
                                         "Емкость ковша",
                                         "Произоводительность погрузочной машины м3.час",
                                         "Время обслуживания погрузочной машиной автосамосвала мин",
                                         "Время движения груженного и порожнего автосамосвала в мин",
                                         "Общее время рейса автосамосвала",
                                         "Производительность автосамосвала м3.ч",
                                         "Количество необходимых автосамосвалов",
                                         "Время необходимое птк для выполнения 1000 м3 земляных работ час.тыс м3",
                                         "Расход дизеля птк на 1000 м3",
                                         "Расход электроэнергии эл. экскаватором на 1000 квт х час.тыс м3",
                                         "Затраты труда на 1000 м3 чел/cмены",
                                         "Производителность ПТК за смену м3.см",
                                         "Производителность 1 рабочего за смену м3.см",
                                         "Затраты на гражданское хозяйство на 1 маш.-час(руб.маш-час)",
                                         "Стоимость часа эксплуатации всех машин птк руб.час",
                                         "Стоимость 1000 m3 эксплуатации всех машин птк тыс.руб.час/м3",
                                         "Время, необходимое для выполнения птком объема земляных работ А, смены",
                                         "Энергоемкость на 1 м3 земляных работ квт час на м3",
                                         "Энергоемкость на 1 м3 земляных работ (л.с)"
                                       };
std::vector<double> calculateExportComplex(int workWay,
                                           double Gamma,
                                           std::shared_ptr<machine::Tipper> tipper,
                                           std::shared_ptr<machine::LoadingTransport> loadingTransport)
{
    std::vector<double> outParams;

    outParams.resize(OUT_PARAMS_COUNT);

    outParams[Qp] = 60 * loadingTransport->getParam(machine::loadingT::E) *
            loadingTransport->getParam(loadingT::CyclesPerMin) *
            loadingTransport->getParam(loadingT::Ke) *
            loadingTransport->getParam(loadingT::Kv);

    outParams[to] = loadingTransport->getParam(loadingT::tn) +
            loadingTransport->getParam(loadingT::tz);

    outParams[tdv] = 2 * workWay * 60 / tipper->getParam(tipperT::Vpc);

    outParams[tob] = outParams[to] + outParams[tdv] + loadingTransport->getParam(loadingT::tp);

    outParams[Qa] = (60 * tipper->getParam(tipperT::qa)) *
            tipper->getParam(tipperT::Kq) / (Gamma * outParams[tob]);

    outParams[Na] = (outParams[Qp] / outParams[Qa]) + 1;

    outParams[tk] = 1000 / outParams[Qp];

    outParams[DiselPer1000] = (loadingTransport->getParam(loadingT::Dp) +
                               tipper->getParam(tipperT::Da) *
                               outParams[Na]) * outParams[tk] / 1000;

    outParams[EPer1000] = loadingTransport->getParam(loadingT::Ee) * outParams[tk];

    outParams[Qptk] = outParams[Qp] * T;

    outParams[WorkPer1000] = loadingTransport->getParam(loadingT::N) *
            outParams[tk] / T;

    outParams[Qr] = outParams[Qp] * T / loadingTransport->getParam(loadingT::N);

    outParams[Cg] = tipper->getParam(tipperT::Ckg) *
            tipper->getParam(tipperT::Kta) * 1000;

    outParams[Cptk] = loadingTransport->getParam(loadingT::Cp) +
            (tipper->getParam(tipperT::Ca) +
             outParams[Cg]) * outParams[Na];
    outParams[Toob] = loadingTransport->getParam(loadingT::A) / outParams[Qptk];

    outParams[Cptk1000] = ((outParams[Cg] + tipper->getParam(tipperT::Ca)) * outParams[Na]) + loadingTransport->getParam(loadingT::Cp);

    outParams[kvtPTK1] = (loadingTransport->getParam(loadingT::Wp) +
                          outParams[Na]+ tipper->getParam(tipperT::Wa)) / outParams[Qp];

    outParams[lsPTK1] = outParams[kvtPTK1] / 0.7355;

    return outParams;
}

bool PrepareExportToExel(xlsxwriter::Worksheet& ws,
                         size_t& index)
{
    size_t internalIndex = index;

    for (const auto& col : columnNames)
    {
        ws.write_string(internalIndex++, 0, col);
    }

    ws.set_column(0, 0, 70);

    return true;
}

}

machine::PTK::PTK(double _workShift,
                  double _groundWeight,
                  std::vector<double> &&_earthTransportingLengths,
                  MachineComplex_map&& _mam):
    workShift(_workShift),
    groundWeight(_groundWeight),
    earthTransportingLengths(_earthTransportingLengths),
    machineComplex(_mam)
{

}

void machine::PTK::ExportToXlsx(double workWay,
                                double groundWeight,
                                double workShift,
                                xlsxwriter::Worksheet& ws,
                                ExportComplex_vec &complexes,
                                size_t& rowPosition)
{
    xlsxwriter::Column startColumn = 1;
    xlsxwriter::Row startRow = rowPosition;

    for (auto&& complex : complexes)
    {
        ws.write_number(startRow++, startColumn,  workWay);
        ws.write_number(startRow++, startColumn,  workShift);
        ws.write_number(startRow++, startColumn,  groundWeight);
        ws.write_string(startRow++, startColumn,  complex.tipperName);
        ws.write_number(startRow++, startColumn,  complex.loadMachineGrabCapacity);

        for (const double& paramValue : complex.exportParams)
        {
            ws.write_number(startRow++, startColumn,  paramValue);
        }
        startRow = rowPosition;
        ++startColumn;
    }
    rowPosition += columnNames.size();
}



bool machine::PTK::Export(std::string_view path)
{
    return true;
}

bool machine::PTK::Import(std::string_view path)
{
    return true;
}

IMachine *machine::PTK::Copy()
{
    return nullptr;
}

void machine::PTK::Processing(std::string_view path)
{
    xlsxwriter::Workbook workbook(path.data());
    auto ws = workbook.add_worksheet("PTK");
    ws.activate();

    size_t cell_x = 1;
    for (auto workWay: earthTransportingLengths)
    {
        ExportComplex_vec exportComplex;

        for (const auto& [tipper, loadingTransports]: machineComplex)
        {
            for (const auto& loadingTransport: loadingTransports)
            {
                auto val = calculateExportComplex(workWay, groundWeight,tipper, loadingTransport);
                exportComplex.emplace_back(tipper->getName(),loadingTransport->getParam(machine::E), val);

            }
        }
        PrepareExportToExel(ws, cell_x);
        ExportToXlsx(workWay, groundWeight,workShift, ws, exportComplex, cell_x);
        cell_x += 2;
    }
    workbook.close();
}

machine::PTK::~PTK()
{

}
