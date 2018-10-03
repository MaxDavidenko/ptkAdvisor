import qbs

Project {
    minimumQbsVersion: "1.9.1"

    CppApplication {
        cpp.cxxLanguageVersion: "c++17"
        consoleApplication: true
        files: [
            "imachine.h",
            "loadingtransport.cpp",
            "loadingtransport.h",
            "main.cpp",
            "ptk.cpp",
            "ptk.h",
            "tipper.cpp",
            "tipper.h",
        ]

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
        }
    }
}
