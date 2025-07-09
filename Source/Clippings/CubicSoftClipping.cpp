/*
  ==============================================================================

    CubicSoftClipping.cpp
    Created: 8 Jul 2025 2:23:05pm
    Author:  vqbao

  ==============================================================================
*/
#include <JuceHeader.h>

#include "CubicSoftClipping.h"
#include "../Helper.h"

void CubicSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    constexpr float twoThirds = 2.f / 3.f;
    float sign = Helper::sgn(samples[sampleIndex]);

    if (fabsf(samples[sampleIndex]) > twoThirds)
    {
        samples[sampleIndex] = sign;
    }
    else if (Helper::isBetween(samples[sampleIndex], -1 * twoThirds, twoThirds))
    {
        samples[sampleIndex] = (9.0f / 4.0f) * samples[sampleIndex] - (27.0f / 16.0f) * powf(samples[sampleIndex], 3);
    }
}

bool CubicSoftClipping::hasFactor()
{
    return false;
}