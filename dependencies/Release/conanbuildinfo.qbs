import qbs 1.0

Project {
    Product {
        name: "ConanBasicSetup"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: ["C:/Users/Max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/6cc50b139b9c3d27b3e9042d5f5372d327b3a9f7/include",
                "C:/.conan/99_qidyv/1/include",
                "C:/Users/Max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/6cc50b139b9c3d27b3e9042d5f5372d327b3a9f7/include"]
            cpp.libraryPaths: ["C:/Users/Max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/6cc50b139b9c3d27b3e9042d5f5372d327b3a9f7/lib",
                "C:/.conan/99_qidyv/1/lib",
                "C:/Users/Max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/6cc50b139b9c3d27b3e9042d5f5372d327b3a9f7/lib"]
            cpp.systemIncludePaths: []
            cpp.dynamicLibraries: ["tinyxml2",
                "log4cplus",
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
            cpp.includePaths: ["C:/Users/Max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/6cc50b139b9c3d27b3e9042d5f5372d327b3a9f7/include"]
            cpp.libraryPaths: ["C:/Users/Max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/6cc50b139b9c3d27b3e9042d5f5372d327b3a9f7/lib"]
            cpp.systemIncludePaths: []
            cpp.dynamicLibraries: ["tinyxml2"]
            cpp.defines: []
            cpp.cppFlags: []
            cpp.cFlags: []
            cpp.linkerFlags: []
        }
    }
    // tinyxml2 root path: C:/Users/Max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/6cc50b139b9c3d27b3e9042d5f5372d327b3a9f7

    Product {
        name: "log4cplus"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: ["C:/.conan/99_qidyv/1/include"]
            cpp.libraryPaths: ["C:/.conan/99_qidyv/1/lib"]
            cpp.systemIncludePaths: []
            cpp.dynamicLibraries: ["log4cplus",
                "Ws2_32"]
            cpp.defines: []
            cpp.cppFlags: []
            cpp.cFlags: []
            cpp.linkerFlags: []
        }
    }
    // log4cplus root path: C:/.conan/99_qidyv/1

    Product {
        name: "xlsxwriter++"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: ["C:/Users/Max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/6cc50b139b9c3d27b3e9042d5f5372d327b3a9f7/include"]
            cpp.libraryPaths: ["C:/Users/Max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/6cc50b139b9c3d27b3e9042d5f5372d327b3a9f7/lib"]
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
    // xlsxwriter++ root path: C:/Users/Max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/6cc50b139b9c3d27b3e9042d5f5372d327b3a9f7
}
