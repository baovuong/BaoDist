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
#define BOTTOM_THRESHOLD 0.0005f

void Distortion::process(int numSamples, float* samples, float drive, Clipping *clipping)
{
    for (int sample = 0; sample < numSamples; ++sample)
    {
        // noise gate cuz we really need it lol
        //if (abs(samples[sample] < BOTTOM_THRESHOLD))
        //    continue;

        // add the drive
        samples[sample] *= drive * DRIVE_SCALE;

        // hard-clipping distortion piecewise function
        clipping->clip(samples, sample);
    }
}
