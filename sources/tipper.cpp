#include "tipper.h"
#include "tinyxml2.h"
#include <iostream>
#include "ptkutils.h"
#include <random>

machine::Tipper::Tipper(): params(9, std::rand())
{

}

machine::Tipper::Tipper(const std::string &name, const std::vector<double> &_params): machineName(name), params(_params)
{
}

bool machine::Tipper::Export(std::string_view path)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement * pRoot = doc.NewElement("Machine");
    doc.LinkEndChild(pRoot);
    pRoot->SetValue(machineName.c_str());
//    auto tipperExportNames = machine::utils::getTTExportNames();

    for (size_t i = 0; i < params.size(); ++i)
    {
        tinyxml2::XMLElement * node = doc.NewElement("el");
        if (node != nullptr)
        {
            node->SetText(std::to_string(params[i]).c_str());
            pRoot->LinkEndChild(node);
        }
    }
    return doc.SaveFile(path.data());
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
    tinyxml2::XMLElement* root = doc.RootElement();
    machineName = root->Value();

    tinyxml2::XMLElement* child = root->FirstChildElement();
    size_t pos = 0;

    while (child != nullptr)
    {
        params[pos++] = std::stod(child->GetText());

        child = child->NextSiblingElement();
    }
    return true;
}

IMachine *machine::Tipper::Copy()
{

}

void machine::Tipper::setParam(machine::tipperT num, double value)
{
    params[num] = value;
}

double machine::Tipper::getParam(machine::tipperT num) const
{
    return params[num];
}

machine::Tipper::~Tipper()
{

}
