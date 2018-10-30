#ifndef TIPPER_H
#define TIPPER_H
#include "imachine.h"
#include<string>

namespace machine {

enum tipperT
{
    qa, // грузоподъемность самосвала
    Vpc, // расчетная скорость движения автосамосвалов в км/ч
    Kq, // коэффициент использования грузоподьемности автосамосвала
    Da, // расход дизельного топлива автосамосвала за 1 маш час
    Ckg, // годовые капитальные затраты на гаражное хозяйство на 1 самосвал тыс/руб. маш. год
    Ta, // годовой рабочий фонд времени автосамосвала
    Kta, // коэффициент использования Ta
    Ca, // стоимость маш-час автосамосвала, руб.маш -час
    Wa //мощность двигателя автосамосвала
};

class Tipper: public IMachine
{
public:
    Tipper();
    explicit Tipper(const std::string& name, const std::vector<double>& params);
    virtual bool Export(std::string_view path) override;
    virtual bool Import(std::string_view path) override;
    virtual IMachine* Copy() override;
    void setParam(tipperT num, double value);
    double getParam(tipperT num);
    inline const std::vector<double> getParams() { return params;}
    virtual ~Tipper();
private:
    std::string machineName;
    std::vector<double> params;
};
}
#endif // TIPPER_H
