/*
  ==============================================================================

    SoftClipping.cpp
    Created: 6 May 2025 1:31:01am
    Author:  vqbao

  ==============================================================================
*/

#include <JuceHeader.h>

#include "ArcTanSoftClipping.h"

#define FACTOR_SCALE 5
#define BOTTOM_FACTOR 0.5

using namespace juce;

void ArcTanSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    samples[sampleIndex] = 2 / MathConstants<float>::pi * atan((factor * (FACTOR_SCALE - BOTTOM_FACTOR) + BOTTOM_FACTOR) * samples[sampleIndex]);
}

bool ArcTanSoftClipping::hasFactor()
{
    return true;
}
