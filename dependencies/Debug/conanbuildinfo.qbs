import qbs 1.0

Project {
    Product {
        name: "ConanBasicSetup"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: ["C:/Users/Max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/8cf01e2f50fcd6b63525e70584df0326550364e1/include",
                "C:/.conan/yxhbhem7/1/include",
                "C:/Users/Max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/8cf01e2f50fcd6b63525e70584df0326550364e1/include"]
            cpp.libraryPaths: ["C:/Users/Max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/8cf01e2f50fcd6b63525e70584df0326550364e1/lib",
                "C:/.conan/yxhbhem7/1/lib",
                "C:/Users/Max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/8cf01e2f50fcd6b63525e70584df0326550364e1/lib"]
            cpp.systemIncludePaths: []
            cpp.dynamicLibraries: ["tinyxml2d",
                "log4cplusD",
                "Ws2_32",
                "xlsxwriter++",
                "xlsxwriter",
                "zlib"]
            cpp.defines: []
            cpp.cppFlags: []
            cpp.cFlags: []
            cpp.linkerFlags: []
        }
    }

    Product {
        name: "tinyxml2"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: ["C:/Users/Max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/8cf01e2f50fcd6b63525e70584df0326550364e1/include"]
            cpp.libraryPaths: ["C:/Users/Max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/8cf01e2f50fcd6b63525e70584df0326550364e1/lib"]
            cpp.systemIncludePaths: []
            cpp.dynamicLibraries: ["tinyxml2d"]
            cpp.defines: []
            cpp.cppFlags: []
            cpp.cFlags: []
            cpp.linkerFlags: []
        }
    }
    // tinyxml2 root path: C:/Users/Max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/8cf01e2f50fcd6b63525e70584df0326550364e1

    Product {
        name: "log4cplus"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: ["C:/.conan/yxhbhem7/1/include"]
            cpp.libraryPaths: ["C:/.conan/yxhbhem7/1/lib"]
            cpp.systemIncludePaths: []
            cpp.dynamicLibraries: ["log4cplusD",
                "Ws2_32"]
            cpp.defines: []
            cpp.cppFlags: []
            cpp.cFlags: []
            cpp.linkerFlags: []
        }
    }
    // log4cplus root path: C:/.conan/yxhbhem7/1

    Product {
        name: "xlsxwriter++"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: ["C:/Users/Max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/8cf01e2f50fcd6b63525e70584df0326550364e1/include"]
            cpp.libraryPaths: ["C:/Users/Max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/8cf01e2f50fcd6b63525e70584df0326550364e1/lib"]
            cpp.systemIncludePaths: []
            cpp.dynamicLibraries: ["xlsxwriter++",
                "xlsxwriter",
                "zlib"]
            cpp.defines: []
            cpp.cppFlags: []
            cpp.cFlags: []
            cpp.linkerFlags: []
        }
    }
    // xlsxwriter++ root path: C:/Users/Max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/8cf01e2f50fcd6b63525e70584df0326550364e1
}
