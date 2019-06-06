// PluginVCO.cpp
// Eric Sluyter (wondersluyter@gmail.com)

#include "SC_PlugIn.hpp"
#include "VCO.hpp"
#include "VoltageControlledOscillator.hpp"

static InterfaceTable *ft;

namespace VCO {

VCO::VCO()
{
    bool syncEnabled = isAudioRateIn(3);
    oscillator.syncEnabled = syncEnabled;
    oscillator.phase = in0(5);
    oscillator.calcSin = in0(6) > 0.f;
    oscillator.calcTri = in0(7) > 0.f;
    oscillator.calcSaw = in0(8) > 0.f;
    oscillator.calcSqr = in0(9) > 0.f;

    if (isAudioRateIn(0)) {
        if (syncEnabled) {
            set_calc_function<VCO, &VCO::next_aa>();
        } else {
            set_calc_function<VCO, &VCO::next_ai>();
        }
    } else {
        if (syncEnabled) {
            set_calc_function<VCO, &VCO::next_ka>();
        } else {
            set_calc_function<VCO, &VCO::next_ki>();
            Print("ki");
        }
    }
    //next(1);
}

void VCO::next_ki(int nSamples)
{
    const float freq = in0(0);
    const float pw = in0(1);
    const float analog = in0(2);
    float * sinout = out(0);
    float * triout = out(1);
    float * sawout = out(2);
    float * sqrout = out(3);

    oscillator.analog = analog > 0.f;
    oscillator.setPulseWidth(pw);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        oscillator.setFreq(freq);
        oscillator.process(sampleDur(), 0);
        sinout[i] = oscillator.sin();
        triout[i] = oscillator.tri();
        sawout[i] = oscillator.saw();
        sqrout[i] = oscillator.sqr();
    }
}

void VCO::next_ka(int nSamples)
{
    const float freq = in0(0);
    const float pw = in0(1);
    const float analog = in0(2);
    const float * syncIn = in(3);
    const float softsync = in0(4);
    float * sinout = out(0);
    float * triout = out(1);
    float * sawout = out(2);
    float * sqrout = out(3);

    oscillator.analog = analog > 0.f;
    oscillator.soft = softsync > 0.f;
    oscillator.setPulseWidth(pw);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        oscillator.setFreq(freq);
        oscillator.process(sampleDur(), syncIn[i]);
        sinout[i] = oscillator.sin();
        triout[i] = oscillator.tri();
        sawout[i] = oscillator.saw();
        sqrout[i] = oscillator.sqr();
    }
}

void VCO::next_ai(int nSamples)
{
    const float * freq = in(0);
    const float pw = in0(1);
    const float analog = in0(2);
    float * sinout = out(0);
    float * triout = out(1);
    float * sawout = out(2);
    float * sqrout = out(3);

    oscillator.analog = analog > 0.f;
    oscillator.setPulseWidth(pw);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        oscillator.setFreq(freq[i]);
        oscillator.process(sampleDur(), 0);
        sinout[i] = oscillator.sin();
        triout[i] = oscillator.tri();
        sawout[i] = oscillator.saw();
        sqrout[i] = oscillator.sqr();
    }
}

void VCO::next_aa(int nSamples)
{
    const float * freq = in(0);
    const float pw = in0(1);
    const float analog = in0(2);
    const float * syncIn = in(3);
    const float softsync = in0(4);
    float * sinout = out(0);
    float * triout = out(1);
    float * sawout = out(2);
    float * sqrout = out(3);

    oscillator.analog = analog > 0.f;
    oscillator.soft = softsync > 0.f;
    oscillator.setPulseWidth(pw);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        oscillator.setFreq(freq[i]);
        oscillator.process(sampleDur(), syncIn[i]);
        sinout[i] = oscillator.sin();
        triout[i] = oscillator.tri();
        sawout[i] = oscillator.saw();
        sqrout[i] = oscillator.sqr();
    }
}

} // namespace VCO

PluginLoad(VCOUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<VCO::VCO>(ft, "VCO");
}
