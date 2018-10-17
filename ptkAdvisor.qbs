Product
{
    name: "ptkAdvisor"
    type: "application"

    Depends {name: "cpp"}
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
