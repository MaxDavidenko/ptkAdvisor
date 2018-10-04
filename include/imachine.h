#ifndef IMACHINE_H
#define IMACHINE_H
#include <string_view>
#include <vector>

class IMachine
{
public:
    virtual bool Export(std::string_view path) = 0;
    virtual bool Import(std::string_view path) = 0;
    virtual IMachine* Copy() = 0;

};

#endif // IMACHINE_H
