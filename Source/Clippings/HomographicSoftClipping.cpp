/*
  ==============================================================================

    HomographicSoftClipping.cpp
    Created: 7 May 2025 9:55:11pm
    Author:  vqbao

  ==============================================================================
*/

#include <JuceHeader.h>

#include "HomographicSoftClipping.h"
#include "../Helper.h"

constexpr float kTop = 1.5f;
constexpr float kBottom = 0.05f;

void HomographicSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    samples[sampleIndex] /= fabsf(samples[sampleIndex]) + Helper::scale(1 - factor, kBottom, kTop);
}

bool HomographicSoftClipping::hasFactor()
{
    return true;
}
