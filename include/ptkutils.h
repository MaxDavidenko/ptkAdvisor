#ifndef PTKUTILS_H
#define PTKUTILS_H
#include <string_view>
#include <vector>

namespace machine::utils
{
    const std::vector<std::string_view>& getLTExportNames();
    const std::vector<std::string_view>& getTTExportNames();
}
#endif // PTKUTILS_H
