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
    
    float a = 1.0f / 3.0f;
    float b = 2.0f / 3.0f;

    float scaled = Helper::scale(factor, 2, 5);
    int sign = Helper::sgn(samples[sampleIndex]);
    float absValue = abs(samples[sampleIndex]);

    // TODO there is a lot of variables that the factor knob could control. let's figure out what to do
    // * the piecewise function boundary values
    // * in the second condition block, some subtraction values could work
    // * in the second condition block, maybe the base value for pow(n - abs(m))

    if (absValue > b)
    {
        samples[sampleIndex] = sign;
    }
    else if (Helper::isBetween(absValue, a, b))
    {
        samples[sampleIndex] = sign * ((3 - pow(2 - abs(3 * samples[sampleIndex]), 2)) / 3.0f);
    }
    else if (absValue < a)
    {
        samples[sampleIndex] *= 2;
    }
}

bool TwoStageQuadraticSoftClipping::hasFactor()
{
    return true;
}
