/*
  ==============================================================================

    WhoopsieSineSoftClipping.cpp
    Created: 22 May 2025 1:04:28pm
    Author:  vqbao

  ==============================================================================
*/

#include "WhoopsieSineSoftClipping.h"

#include "../Helper.h"
#include <JuceHeader.h>

void WhoopsieSineSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    float a = Helper::scale(factor, 0.5f, 1.5f);
    float b = 1.0f / (2 * a);

    // sinusoidal soft clipping piecewise function
    if (fabsf(samples[sampleIndex] > b))
    {
        samples[sampleIndex] = Helper::sgn(samples[sampleIndex]);
    }
    else if (samples[sampleIndex] >= -1 * b || samples[sampleIndex] <= b)
    {
        samples[sampleIndex] = sin(a * juce::MathConstants<float>::pi * samples[sampleIndex]);
    }
}

bool WhoopsieSineSoftClipping::hasFactor()
{
    return true;
}