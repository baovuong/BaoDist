/*
  ==============================================================================

    ExponentialSoftClipping.cpp
    Created: 22 May 2025 2:37:09am
    Author:  vqbao

  ==============================================================================
*/

#include <JuceHeader.h>

#include "ExponentialSoftClipping.h"
#include "../Helper.h"

void ExponentialSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    // exponential soft clipping piecewise function
    constexpr float b = 2.f / 3.f;

    const float sgnValue = Helper::sgn(samples[sampleIndex]);
    int exponential = floor(Helper::scale(factor, 2, 10));

    if (fabsf(samples[sampleIndex]) > b)
    {
        samples[sampleIndex] = sgnValue;
    }
    else if (samples[sampleIndex] >= -1 * b && samples[sampleIndex] <= b)
    {
        samples[sampleIndex] = sgnValue * (1 - powf(fabsf(3 * samples[sampleIndex] / 2 - sgnValue), exponential));
    }
}

bool ExponentialSoftClipping::hasFactor()
{
    return true;
}
