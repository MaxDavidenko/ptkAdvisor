#include "tipper.h"

machine::Tipper::Tipper()
{

}

bool machine::Tipper::Export(std::string_view path)
{

}

bool machine::Tipper::Import(std::string_view path)
{

}

IMachine *machine::Tipper::Copy()
{

}

void machine::Tipper::setParam(machine::tipperT num, double value)
{
    params[num] = value;
}

double machine::Tipper::getParam(machine::tipperT num)
{
    return params[num];
}

machine::Tipper::~Tipper()
{

}
