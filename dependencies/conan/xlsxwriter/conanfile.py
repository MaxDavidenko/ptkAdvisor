from conans import ConanFile, CMake, MSBuild, tools
import os
import shutil
class XlntConan(ConanFile):
    name = "xlsxwriter"
    version = "1.0"
    description = "The library for convinient work with xlsx files github repo: https://github.com/Alexhuszagh/libxlsxwriterpp"
    license = "MIT"
    url = "https://github.com/Alexhuszagh/libxlsxwriterpp.git"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared" : [True, False]}
    exports_sources = ["CMakeLists.txt", ".gitmodules"]
    full_name = "{_name}-{_version}".format(_name = name, _version = version)
    default_options = "shared=False"
    generators = "cmake"

    def build_requirements(self):
    # useful for example for conditional build_requires
    # This means, if we are running on a Windows machine, require ToolWin
        self.build_requires("zlib/1.2.11@conan/stable")
    
    def source(self):
	#tools.get("https://github.com/Alexhuszagh/libxlsxwriterpp/archive/master.zip")
        self.run("git clone https://github.com/jmcnamara/libxlsxwriter.git")
		self.run("git submodule update --init --recursive")

    def build(self):
        cmake = CMake(self)
        shutil.copy("CMakeLists.txt", "libxlsxwriter/CMakeLists.txt")
        cmake.configure(source_folder="libxlsxwriter")
        #cmake.definitions["CMAKE_CXX_STANDARD"]="17"
        if self.settings.os == "Windows":
            msbuild = MSBuild(self)
            msbuild.build("xlsxwriter.sln", parallel=False)
          #  self.run("msbuild libxlsxwriter++.sln")
        else:
            cmake.build()
            self.run("make -j6")

    def package(self):
        self.copy("*.hpp", dst="include/xlsxwriterpp", src="libxlsxwriterpp/include")
        self.copy("*.h", dst="include", src="libxlsxwriterpp/libxlsxwriter/include")
        self.copy("*.dll", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
     
    def package_info(self):
        self.cpp_info.libs = ["xlsxwriter", "zlib"]
        
