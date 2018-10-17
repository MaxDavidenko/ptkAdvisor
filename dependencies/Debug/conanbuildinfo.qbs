import qbs 1.0

Project {
    Product {
        name: "ConanBasicSetup"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: ["/home/max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423/include",
                "/home/max/.conan/data/log4cplus/2.0.2/bincrafters/stable/package/1a651c5b4129ad794b88522bece2281a7453aee4/include",
                "/home/max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423/include",
                "/home/max/.conan/data/xlnt/dev/krabio/testing/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423/include"]
            cpp.libraryPaths: ["/home/max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423/lib",
                "/home/max/.conan/data/log4cplus/2.0.2/bincrafters/stable/package/1a651c5b4129ad794b88522bece2281a7453aee4/lib",
                "/home/max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423/lib",
                "/home/max/.conan/data/xlnt/dev/krabio/testing/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423/lib"]
            cpp.systemIncludePaths: []
            cpp.dynamicLibraries: ["tinyxml2d",
                "log4cplus",
                "dl",
                "pthread",
                "xlsxwriter++d",
                "xlntd"]
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
            cpp.includePaths: ["/home/max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423/include"]
            cpp.libraryPaths: ["/home/max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423/lib"]
            cpp.systemIncludePaths: []
            cpp.dynamicLibraries: ["tinyxml2d"]
            cpp.defines: []
            cpp.cppFlags: []
            cpp.cFlags: []
            cpp.linkerFlags: []
        }
    }
    // tinyxml2 root path: /home/max/.conan/data/tinyxml2/6.2.0/nicolastagliani/stable/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423

    Product {
        name: "log4cplus"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: ["/home/max/.conan/data/log4cplus/2.0.2/bincrafters/stable/package/1a651c5b4129ad794b88522bece2281a7453aee4/include"]
            cpp.libraryPaths: ["/home/max/.conan/data/log4cplus/2.0.2/bincrafters/stable/package/1a651c5b4129ad794b88522bece2281a7453aee4/lib"]
            cpp.systemIncludePaths: []
            cpp.dynamicLibraries: ["log4cplus",
                "dl",
                "pthread"]
            cpp.defines: []
            cpp.cppFlags: []
            cpp.cFlags: []
            cpp.linkerFlags: []
        }
    }
    // log4cplus root path: /home/max/.conan/data/log4cplus/2.0.2/bincrafters/stable/package/1a651c5b4129ad794b88522bece2281a7453aee4

    Product {
        name: "xlsxwriter++"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: ["/home/max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423/include"]
            cpp.libraryPaths: ["/home/max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423/lib"]
            cpp.systemIncludePaths: []
            cpp.dynamicLibraries: ["xlsxwriter++d"]
            cpp.defines: []
            cpp.cppFlags: []
            cpp.cFlags: []
            cpp.linkerFlags: []
        }
    }
    // xlsxwriter++ root path: /home/max/.conan/data/xlsxwriter++/1.0/krabio/testing/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423

    Product {
        name: "xlnt"
        Export {
            Depends { name: "cpp" }
            cpp.includePaths: ["/home/max/.conan/data/xlnt/dev/krabio/testing/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423/include"]
            cpp.libraryPaths: ["/home/max/.conan/data/xlnt/dev/krabio/testing/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423/lib"]
            cpp.systemIncludePaths: []
            cpp.dynamicLibraries: ["xlntd"]
            cpp.defines: []
            cpp.cppFlags: []
            cpp.cFlags: []
            cpp.linkerFlags: []
        }
    }
    // xlnt root path: /home/max/.conan/data/xlnt/dev/krabio/testing/package/69f10d1e6d78c1962fbe8fb80440f32b1fdf8423
}
