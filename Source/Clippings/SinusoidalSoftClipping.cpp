/*
  ==============================================================================

    SinusoidalSoftClipping.cpp
    Created: 19 May 2025 12:57:39am
    Author:  vqbao

  ==============================================================================
*/

#include "SinusoidalSoftClipping.h"
#include "../Helper.h"
#include <JuceHeader.h>

void SinusoidalSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    float a = Helper::scale(factor, 0.5f, 1.5f);
    float b = 1.0f / (2 * a);

    // sinusoidal soft clipping piecewise function
    if (abs(samples[sampleIndex] > b))
    {
        samples[sampleIndex] = Helper::sgn(samples[sampleIndex]);
    }
    else if (samples[sampleIndex] >= -1 * b || samples[sampleIndex] <= b)
    {
        samples[sampleIndex] = sin(a * juce::MathConstants<float>::pi * samples[sampleIndex]);
    }
}

bool SinusoidalSoftClipping::hasFactor()
{
    return true;
}
