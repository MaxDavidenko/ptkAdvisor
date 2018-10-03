#include "ptk.h"
#include "loadingtransport.h"
#include "tipper.h"

machine::PTK::PTK()
{

}

bool machine::PTK::Export(std::string_view path)
{

}

bool machine::PTK::Import(std::string_view path)
{

}

IMachine *machine::PTK::Copy()
{

}

void machine::PTK::SetParam(machine::ptkT num, double value)
{
    params[num] = value;
}

void machine::PTK::Processing()
{
    for (const auto& tipper: tippers)
    {
        for (auto workWay: earthTransportingLengths)
        {
            outParams[Qp] = 60 * loadingTransport->getParam(loadingT::E) *
                                 loadingTransport->getParam(loadingT::CyclesPerMin) *
                                 loadingTransport->getParam(loadingT::Ke) *
                                 loadingTransport->getParam(loadingT::Kv);

            outParams[to] = loadingTransport->getParam(loadingT::tn) +
                            loadingTransport->getParam(loadingT::tz);

            outParams[tdv] = 2 * workWay * 60 / tipper->getParam(tipperT::Vpc);

            outParams[tob] = outParams[to] + outParams[tdv] + loadingTransport->getParam(loadingT::tp);

            outParams[Qa] = (60 * tipper->getParam(tipperT::qa)) *
                             tipper->getParam(tipperT::Kq) / (Gamma * outParams[tob]);

            outParams[Na] = (outParams[Qp] / outParams[Qa]) + 1;

            outParams[tk] = 1000 / outParams[Qp];

            outParams[DiselPer1000] = (loadingTransport->getParam(loadingT::Dp) +
                                       tipper->getParam(tipperT::Da) *
                                       outParams[Na]) * outParams[tk] / 1000;

            outParams[EPer1000] = loadingTransport->getParam(loadingT::Ee) * outParams[tk];

            outParams[Qptk] = outParams[Qp] * T;

            outParams[WorkPer1000] = loadingTransport->getParam(loadingT::N) *
                                     outParams[tk] / T;

            outParams[Qr] = outParams[Qp] * T / loadingTransport->getParam(loadingT::N);

            outParams[Cg] = tipper->getParam(tipperT::Ckg) *
                            tipper->getParam(tipperT::Kta) * 1000;

            outParams[Cptk] = loadingTransport->getParam(loadingT::Cp) +
                              (tipper->getParam(tipperT::Ca) +
                              outParams[Cg]) * outParams[Na];
            outParams[Toob] = loadingTransport->getParam(loadingT::A) / outParams[Qptk];

            outParams[kvtPTK1] = (loadingTransport->getParam(loadingT::Wp) +
                                  outParams[Na]+ tipper->getParam(tipperT::Wa)) / outParams[Qp];

            outParams[lsPTK1] = outParams[kvtPTK1] / 0.7355;
        }
        Export("path");
    }
}

machine::PTK::~PTK()
{

}
