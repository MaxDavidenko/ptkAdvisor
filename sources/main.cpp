#include <iostream>

#include <xlnt/xlnt.hpp>
#include <tinyxml2.h>
#include "loadingtransport.h"
#include <tipper.h>
#include "ptk.h"
#include <experimental/filesystem>
#include <xlsxwriterpp/workbook.hpp>

int main()
{
    std::cout << "Hello World!" << std::endl;
//    xlnt::workbook wb;
//     tinyxml2::XMLDocument xml_doc;
//    machine::LoadingTransport t("loadingT");
////    auto path = std::experimental::filesystem::v1::current_path();
////    t.Export("loadingT.xml");
//      t.Import("loadingT.xml");
    std::vector<std::shared_ptr<machine::LoadingTransport>> transport(5, std::shared_ptr<machine::LoadingTransport>{new machine::LoadingTransport()} );
    std::shared_ptr<machine::Tipper> tipper(new machine::Tipper());
    machine::MachineComplex_map myMap( {{tipper, transport}});
    machine::PTK ptk(std::vector<int>(5, rand()), std::move(myMap));
    std::string path("exportExample.xlsx");

    xlsxwriter::Workbook myWorkBook("1test.xlsx");
    xlsxwriter::Worksheet sheet = myWorkBook.add_worksheet("sheet");

    ptk.Processing(myWorkBook, path);
    myWorkBook.close();

    return 0;
}

