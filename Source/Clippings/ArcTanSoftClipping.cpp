/*
  ==============================================================================

    SoftClipping.cpp
    Created: 6 May 2025 1:31:01am
    Author:  vqbao

  ==============================================================================
*/

#include <JuceHeader.h>

#include "ArcTanSoftClipping.h"
#include "../Helper.h"

using namespace juce;

constexpr float kTop = 5.f;
constexpr float kBottom = .5f;

void ArcTanSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    samples[sampleIndex] = 2 / MathConstants<float>::pi * atanf(Helper::scale(factor, kBottom, kTop) * samples[sampleIndex]);
}

bool ArcTanSoftClipping::hasFactor()
{
    return true;
}
