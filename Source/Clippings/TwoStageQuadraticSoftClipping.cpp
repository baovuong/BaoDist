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

    float scaled = Helper::scale(factor, 0, 0.5);
    int sign = Helper::sgn(samples[sampleIndex]);
    float absValue = fabsf(samples[sampleIndex]);

    float twoThirds = 2.0f / 3.0f;

    float a = scaled;
    float b = log10f(3 - 6 * a) / log10f(2 - fabsf(3 * a));


    // TODO there is a lot of variables that the factor knob could control. let's figure out what to do
    // [x] the piecewise function boundary values
    // * in the second condition block, some subtraction values could work
    // * in the second condition block, maybe the base value for pow(n - abs(m))

    if (absValue > twoThirds)
    {
        samples[sampleIndex] = sign;
    }
    else if (Helper::isBetween(absValue, a, twoThirds))
    {
        samples[sampleIndex] = sign * ((3 - powf(2 - fabsf(3 * samples[sampleIndex]), b)) / 3.0f);
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
