/*
  ==============================================================================

    ReciprocalSoftClipping.cpp
    Created: 8 Jul 2025 4:52:58pm
    Author:  vqbao

  ==============================================================================
*/
#include <JuceHeader.h>

#include "ReciprocalSoftClipping.h"
#include "../Helper.h"

void ReciprocalSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    samples[sampleIndex] = Helper::sgn(samples[sampleIndex]) * (1 - 1 / (abs(Helper::scale(factor, 1, 30) * samples[sampleIndex]) + 1));
}

bool ReciprocalSoftClipping::hasFactor()
{
    return true;
}