/*
  ==============================================================================

    HomographicSoftClipping.cpp
    Created: 7 May 2025 9:55:11pm
    Author:  vqbao

  ==============================================================================
*/

#include <JuceHeader.h>

#include "HomographicSoftClipping.h"

#define FACTOR_SCALE 1.5f
#define BOTTOM_FACTOR 0.05f

void HomographicSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    samples[sampleIndex] /= fabsf(samples[sampleIndex]) + (1 - factor) * (FACTOR_SCALE-BOTTOM_FACTOR) + BOTTOM_FACTOR;
}

bool HomographicSoftClipping::hasFactor()
{
    return true;
}
