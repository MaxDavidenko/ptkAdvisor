#include "tipper.h"
#include "tinyxml2.h"
#include <iostream>
#include <random>

machine::Tipper::Tipper(): params(9, std::rand())
{

}

bool machine::Tipper::Export(std::string_view path)
{

}

bool machine::Tipper::Import(std::string_view path)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError eResult = doc.LoadFile(path.data());
    if (eResult != 0)
    {
        std::cout << "Can't load loading transport xml file!\n";
        return false;
    }
    tinyxml2::XMLNode* root = doc.RootElement();
    machineName = root->Value();

    auto child = root->FirstChild();
    size_t pos = 0;

    while (child != nullptr)
    {
        params[pos++] = std::stod(child->Value());

        child = child->NextSibling();
    }
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
