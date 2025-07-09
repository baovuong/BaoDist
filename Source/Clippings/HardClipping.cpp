/*
  ==============================================================================

    HardClipping.cpp
    Created: 5 May 2025 4:01:24pm
    Author:  bvuong

  ==============================================================================
*/

#include <JuceHeader.h>

#include "HardClipping.h"
#include "../Helper.h"

constexpr float kThreshold = 1.f;

void HardClipping::clip(float* samples, int sampleIndex, float factor)
{
    // hard-clipping distortion piecewise function
    samples[sampleIndex] = fabsf(samples[sampleIndex]) > kThreshold 
        ? Helper::sgn(samples[sampleIndex]) * kThreshold 
        : samples[sampleIndex];
}

bool HardClipping::hasFactor()
{
    return false;
}
