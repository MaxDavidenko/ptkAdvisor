@echo off
set build_type="%1"
set runtime="%2"
conan export conan/xlnt_dev krabio/testing
conan export conan/xlsxwriter++ krabio/testing

mkdir %build_type%
cd %build_type%

conan install --build=missing -pr ../profiles/windows.pro -s build_type=%build_type% -s compiler.runtime=%runtime% ../conanfile.txt
cd ..
