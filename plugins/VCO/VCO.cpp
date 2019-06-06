// PluginVCO.cpp
// Eric Sluyter (wondersluyter@gmail.com)

#include "SC_PlugIn.hpp"
#include "VCO.hpp"

static InterfaceTable *ft;

namespace VCO {

VCO::VCO()
{
    set_calc_function<VCO, &VCO::next>();
    next(1);
}

void VCO::next(int nSamples)
{
    const float * input = in(0);
    const float * gain = in(0);
    float * outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }
}

} // namespace VCO

PluginLoad(VCOUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<VCO::VCO>(ft, "VCO");
}
