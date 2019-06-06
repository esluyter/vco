// PluginVCO.hpp
// Eric Sluyter (wondersluyter@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace VCO {

class VCO : public SCUnit
{
public:
    VCO();

    // Destructor
    // ~VCO();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace VCO
