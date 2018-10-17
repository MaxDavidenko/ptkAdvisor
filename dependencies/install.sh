
build_type=$1

conan export conan/xlnt_dev krabio/testing
conan export conan/xlsxwriter++ krabio/testing

mkdir $build_type
cd $build_type

conan install --build=missing -pr ../profiles/linux.pro -s build_type=$build_type ../conanfile.txt
cd ..
