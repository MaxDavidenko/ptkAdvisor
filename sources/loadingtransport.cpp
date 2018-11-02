#include "loadingtransport.h"
#include <experimental/filesystem>
#include "tinyxml2.h"
#include <iostream>

namespace
{

    static std::vector<std::string> exportFieldNames { "E",
                                                       "CyclesPerMin",
                                                       "Ke",
                                                       "Kv",
                                                       "tn",
                                                       "tz",
                                                       "tp",
                                                       "Dp",
                                                       "Ee",
                                                       "N",
                                                       "Cp",
                                                       "A",
                                                       "Wp" };
}

machine::LoadingTransport::LoadingTransport(std::string name): machineName(name), params(13, std::rand())
{

}

machine::LoadingTransport::LoadingTransport(const std::string& name, std::vector<double> _params): machineName(name), params(_params)
{

}

bool machine::LoadingTransport::Export(std::string_view path)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement * pRoot = doc.NewElement("Machine");
    doc.LinkEndChild(pRoot);
    pRoot->SetValue(machineName.c_str());
    for (size_t i = 0; i != params.size(); ++i)
    {
        tinyxml2::XMLElement * node = doc.NewElement(exportFieldNames[i].data());
        if (node != nullptr)
        {
            node->SetText(std::to_string(params[i]).c_str());
            pRoot->LinkEndChild(node);
        }
    }
    return doc.SaveFile(path.data());
}

bool machine::LoadingTransport::Import(std::string_view path)
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
