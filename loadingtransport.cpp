#include "loadingtransport.h"

machine::LoadingTransport::LoadingTransport()
{

}

bool machine::LoadingTransport::Export(std::string_view path)
{

}

bool machine::LoadingTransport::Import(std::string_view path)
{

}

IMachine *machine::LoadingTransport::Copy()
{

}

void machine::LoadingTransport::setParam(machine::loadingT num, double value)
{

    params[num] = value;
}

double machine::LoadingTransport::getParam(machine::loadingT num)
{
    return params[num];
}

machine::LoadingTransport::~LoadingTransport()
{

}
