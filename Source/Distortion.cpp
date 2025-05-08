/*
  ==============================================================================

    Distortion.cpp
    Created: 5 May 2025 3:54:14pm
    Author:  bvuong

  ==============================================================================
*/

#include <JuceHeader.h>

#include "Distortion.h"

#define DRIVE_SCALE 50
#define BOTTOM_THRESHOLD 0.005f // TODO remove since we're not using it possibly

void Distortion::process(int numSamples, float* samples, float drive, Clipping *clipping)
{
    if (drive == 0)
        return;

    for (int sample = 0; sample < numSamples; ++sample)
    {
        // add the drive
        samples[sample] *= drive * DRIVE_SCALE;

        // hard-clipping distortion piecewise function
        clipping->clip(samples, sample);
    }
}
