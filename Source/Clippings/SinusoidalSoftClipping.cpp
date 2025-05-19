/*
  ==============================================================================

    SinusoidalSoftClipping.cpp
    Created: 19 May 2025 12:57:39am
    Author:  vqbao

  ==============================================================================
*/

#include "SinusoidalSoftClipping.h"
#include <JuceHeader.h>

void SinusoidalSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    float twoThirds = 2.0f / 3.0f;

    // sinusoidal soft clipping piecewise function
    if (abs(samples[sampleIndex] > twoThirds))
    {
        samples[sampleIndex] = sgn(samples[sampleIndex]);
    }
    else if (samples[sampleIndex] >= -1 * twoThirds || samples[sampleIndex] <= twoThirds)
    {
        samples[sampleIndex] = sin(3.0f * juce::MathConstants<float>::pi * samples[sampleIndex] / 4.0f);
    }
}

bool SinusoidalSoftClipping::hasFactor()
{
    return false;
}
