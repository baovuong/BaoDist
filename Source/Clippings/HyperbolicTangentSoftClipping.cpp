/*
  ==============================================================================

    HyperbolicTangentSoftClipping.cpp
    Created: 18 May 2025 12:33:34am
    Author:  vqbao

  ==============================================================================
*/

#include "HyperbolicTangentSoftClipping.h"

#include <JuceHeader.h>

void HyperbolicTangentSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    samples[sampleIndex] = tanhf(5.f * (factor * .8f + .2f) * samples[sampleIndex]);
}

bool HyperbolicTangentSoftClipping::hasFactor()
{
    return true;
}
