from conans import ConanFile, CMake, tools
import os
class XlntConan(ConanFile):
    name = "xlsxwriter++"
    version = "1.0"
    description = "The library for convinient work with xlsx files github repo: https://github.com/Alexhuszagh/libxlsxwriterpp"
    license = "MIT"
    url = "https://github.com/Alexhuszagh/libxlsxwriterpp.git"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared" : [True, False]}
    full_name = "{_name}-{_version}".format(_name = name, _version = version)
    default_options = "shared=False"
    generators = "cmake"

    def source(self):
	#tools.get("https://github.com/Alexhuszagh/libxlsxwriterpp/archive/master.zip")
        self.run("git clone https://github.com/Alexhuszagh/libxlsxwriterpp.git")
        os.chdir("libxlsxwriterpp")
	self.run("git submodule update --init --recursive")

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="libxlsxwriterpp")
        cmake.definitions["CMAKE_CXX_STANDARD"]="17"
        cmake.build()
        self.run("make -j6")

    def package(self):
        self.copy("*.hpp", dst="include/xlsxwriterpp", src="libxlsxwriterpp/include")
        self.copy("*.h", dst="include", src="libxlsxwriterpp/libxlsxwriter/include")
        self.copy("*.dll", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
     
    def package_info(self):
        self.cpp_info.libs = ["xlsxwriter++"]
        
