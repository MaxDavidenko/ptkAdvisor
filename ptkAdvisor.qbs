Product
{
    files: [
        "sources/gui/PTKMainStackForm.cpp",
        "sources/gui/PTKMainStackForm.h",
        "sources/gui/PTKMainStackForm.ui",
    ]
    Group
    {
        name: "GUI"
        files:[
            "sources/gui/ptkAdvisorMainWindow.cpp",
            "sources/gui/ptkAdvisorMainWindow.h",
            "sources/gui/ptkAdvisorMainWindow.ui",
        ]
    }

    name: "ptkAdvisor"
    type: "application"

    Depends {name: "cpp"}
    Depends { name: "Qt"; submodules: [ "core", "gui", "widgets"] }
    Depends {name: "xlnt"}
    Depends {name: "tinyxml2"}
    Depends {name: "xlsxwriter++"}

    cpp.cxxLanguageVersion: "c++17"
    cpp.includePaths: "include"
    consoleApplication: true

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
    }
    Group
    {
        name: "headers"
        files: ["include/*.h"]
    }
    Group
    {
        name: "sources"
        files: ["sources/*.cpp"]
    }
}
