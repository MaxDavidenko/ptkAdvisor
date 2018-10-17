#ifndef PTK_H
#define PTK_H
#include "imachine.h"
#include <memory>
#include <map>
#include "xlsxwriterpp/workbook.hpp"

namespace  machine
{

class Tipper;
class LoadingTransport;

enum ptkT: size_t
{
    Alpha, // дальность возки грунта в км
    Gamma, // объемная масса грунта в т м3
    T // продолжительность смены в часах
};

enum ptkOutput
{
    Qp, // произоводительность погрузочной машины м3.час
    to, // время обслуживания погрузочной машиной автосамосвала мин
    tdv, // время движения груженного и порожнего автосамосвала в мин
    tob, // общее время рейса автосамосвала
    Qa, // производительность автосамосвала м3.ч
    Na, // количество необходимых автосамосвалов
    tk, // время необходимое птк для выполнения 1000 м3 земляных работ час.тысм3
    DiselPer1000, // расход дизеля птк на 1000 м3
    EPer1000, // расход электроэнергии эл. экскаватором на 1000 квт х час.тыс м3
    WorkPer1000, // затраты труда на 1000 м3 чел/cмены
    Qptk, // производителность ПТК за смену м3.см
    Qr, // производителность 1 рабочего за смену м3.см
    Cg, // затраты на гражданское хозяйство на 1 маш.-час(руб.мащ-час)
    Cptk, // стоимость часа эксплуатации всех машин птк руб.час
    Cptk1000, // стоимость 1000 m3 эксплуатации всех машин птк тыс.руб.час/м3
    Toob, // время, необходимое для выполнения птком объема земляных работ А, смены
    kvtPTK1, // энергоемкость на 1 м3 земляных работ квт час на м3
    lsPTK1 // энергоемкость на 1 м3 земляных работ (л.с)
};

using MachineComplex_map = std::multimap<std::shared_ptr<Tipper>, std::vector<std::shared_ptr<LoadingTransport>>>;
using ExportComplex_vec = std::vector<std::vector<double>>;

class PTK: public IMachine
{
public:
    PTK(std::vector<int>&& earthTransportingLengths, MachineComplex_map&& map);
    void ExportToXlsx(xlsxwriter::Workbook& wb, const std::string& path, ExportComplex_vec &complexes, size_t verticalOffset);
    virtual bool Export(std::string_view path) override;
    virtual bool Import(std::string_view path) override;
    virtual IMachine* Copy() override;
    void SetParam(ptkT num, double value);
    void Processing(xlsxwriter::Workbook &wb, const std::string &path);
    virtual ~PTK();

private:
    std::vector<int> earthTransportingLengths;
    MachineComplex_map machineComplex;
    std::vector<double> params;
};
}
#endif // PTK_H
