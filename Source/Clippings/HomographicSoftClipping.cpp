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

void HomographicSoftClipping::clip(float* samples, int sampleIndex)
{
    samples[sampleIndex] /= abs(samples[sampleIndex]) + factor * (FACTOR_SCALE-BOTTOM_FACTOR) + BOTTOM_FACTOR;
}

void HomographicSoftClipping::setFactor(float factor)
{
    this->factor = factor;
}
