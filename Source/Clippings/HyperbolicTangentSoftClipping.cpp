/*
  ==============================================================================

    HyperbolicTangentSoftClipping.cpp
    Created: 18 May 2025 12:33:34am
    Author:  vqbao

  ==============================================================================
*/

#include "HyperbolicTangentSoftClipping.h"

#include <JuceHeader.h>

void HyperbolicTangentSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    samples[sampleIndex] = tanh(5 * (factor * 0.8f + 0.2f) *samples[sampleIndex]);
}
