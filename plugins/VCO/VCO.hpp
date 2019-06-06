// PluginVCO.hpp
// Eric Sluyter (wondersluyter@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"
#include "VoltageControlledOscillator.hpp"

namespace VCO {

class VCO : public SCUnit
{
public:
    VCO();

    // Destructor
    // ~VCO();

private:
    // Calc function
    void next_ki(int nSamples);
    void next_ka(int nSamples);
    void next_ai(int nSamples);
    void next_aa(int nSamples);

    // Member variables
    VoltageControlledOscillator<16, 16> oscillator;
};

} // namespace VCO
