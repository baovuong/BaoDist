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

    const float sgnValue = Helper::sgn(samples[sampleIndex]);
    int exponential = floor(Helper::scale(factor, 2.f, 10.f));

    if (fabsf(samples[sampleIndex]) > Helper::kTwoThirds)
    {
        samples[sampleIndex] = sgnValue;
    }
    else if (samples[sampleIndex] >= -1 * Helper::kTwoThirds && samples[sampleIndex] <= Helper::kTwoThirds)
    {
        samples[sampleIndex] = sgnValue * (1 - powf(fabsf(3.f * samples[sampleIndex] / 2.f - sgnValue), exponential));
    }
}

bool ExponentialSoftClipping::hasFactor()
{
    return true;
}
