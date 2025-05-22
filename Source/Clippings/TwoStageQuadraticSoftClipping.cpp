/*
  ==============================================================================

    TwoStageQuadraticSoftClipping.cpp
    Created: 22 May 2025 12:29:14pm
    Author:  vqbao

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TwoStageQuadraticSoftClipping.h"
#include "../Helper.h"

void TwoStageQuadraticSoftClipping::clip(float* samples, int sampleIndex, float factor)
{
    float oneThird = 1.0f / 3.0f;
    float b = 2.0f / 3.0f;

    if (abs(samples[sampleIndex]) > b)
    {
        samples[sampleIndex] = Helper::sgn(samples[sampleIndex]);
    }
    else if (abs(samples[sampleIndex]) >= oneThird && abs(samples[sampleIndex]) <= b)
    {
        samples[sampleIndex] = Helper::sgn(samples[sampleIndex]) * ((3 - pow(2 - abs(3 * samples[sampleIndex]), 2)) / 3.0f);
    }
    else if (abs(samples[sampleIndex]) > -1 * oneThird && abs(samples[sampleIndex]) < oneThird)
    {
        samples[sampleIndex] *= 2;
    }
}

bool TwoStageQuadraticSoftClipping::hasFactor()
{
    return false;
}
