/*
  ==============================================================================

    SoftClipping.cpp
    Created: 6 May 2025 1:31:01am
    Author:  vqbao

  ==============================================================================
*/

#include <JuceHeader.h>

#include "SoftClipping.h"

using namespace juce;


void SoftClipping::clip(float* samples, int sampleIndex)
{
    samples[sampleIndex] = 2 / MathConstants<float>::pi * atan(samples[sampleIndex]);
}