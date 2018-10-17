#ifndef LOADINGTRANSPORT_H
#define LOADINGTRANSPORT_H
#include "imachine.h"
#include<string>

namespace machine
{

enum loadingT
{
    E, // геометрическая емкость ковша погрузочной машины
    CyclesPerMin, // число циклов погрузочной машины в 1 мин;
    Ke, // коеэффициент использования емкости ковша погрузочной машины
    Kv, // коеэффициент использования погрузочной машины по времени
    tn, // время нагрузки автосамосвала в мин
    tz, // время замены груженого автосамосвала порожним в мин
    tp, // время загрузки автосамосвала в мин
    Dp, // расход дизельного топлива погрузочной машиной за 1 маш час
    Ee, // расход электроенергии электрическим экскаватором 1 маш час
    N, // число операторов погрузочной машины и автосамосвалов, работающих в смену c одним   комплектом погрузочно-транспортных машин
    Cp, // стоимость маш-час погрузочной машины, руб.маш -час
    A, // объем земляных работ, м3
    Wp // мощность двигателя погрузчика, квт
};
class LoadingTransport : public IMachine
{
public:
    explicit LoadingTransport(std::string name="");
    virtual bool Export(std::string_view path) override;
    virtual bool Import(std::string_view path) override;
    virtual IMachine* Copy() override;
    void setParam(loadingT num, double value);
    double getParam(loadingT num);
    virtual ~LoadingTransport();
private:
    std::string machineName;
    std::vector<double> params;
};
}
#endif // LOADINGTRANSPORT_H
