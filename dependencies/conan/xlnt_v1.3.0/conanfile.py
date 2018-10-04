from conans import ConanFile, CMake, tools
import os
class XlntConan(ConanFile):
    name = "xlnt"
    version = "1.3.0"
    description = "The library for convinient work with xlsx files. github repo: https://github.com/tfussell/xlnt"
    license = "MIT"
    url = "https://github.com/tfussell/xlnt/archive/v{_version}.zip".format(_version = version)
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared" : [True, False]}
    full_name = "{_name}-{_version}".format(_name = name, _version = version)
    default_options = "shared=False"
    generators = "cmake"

    def source(self):
        full_name = self.name + self.version + ".zip"
        tools.get(self.url)
        #tools.unzip(full_name, ".")

    def build(self):
        cmake = CMake(self)
        cmake.definitions["STATIC"]= "ON"
        cmake.configure(source_folder = self.full_name)
        self.run("make -j6")

    def package(self):
        self.copy("*.hpp", dst="include", src="{full_name}/include".format(full_name = self.full_name))
        self.copy("*.dll", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
