/*
  ==============================================================================

    Distortion.cpp
    Created: 5 May 2025 3:54:14pm
    Author:  bvuong

  ==============================================================================
*/

#include <JuceHeader.h>

#include "Distortion.h"

constexpr float kDriveScale = 100.f;

void Distortion::process(int numSamples, float* samples, float drive, float factor, Clipping *clipping)
{
    if (drive == 0)
    {
        return;
    }

    for (int sample = 0; sample < numSamples; ++sample)
    {
        // add the drive
        samples[sample] *= drive * kDriveScale;

        // hard-clipping distortion piecewise function
        clipping->clip(samples, sample, factor);
    }
}
