/*
  ==============================================================================

    HardClipDistortion.cpp
    Created: 1 May 2025 1:50:04am
    Author:  vqbao

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HardClipDistortion.h"

#define DRIVE_SCALE 0.5f
#define BOTTOM_THRESHOLD 0.0005f

void HardClipDistortion::process(int numSamples, float* samples)
{
    for (int sample = 0; sample < numSamples; ++sample)
    {
        // noise gate cuz we really need it lol
        if (abs(samples[sample] < BOTTOM_THRESHOLD))
            continue;

        // hard-clipping distortion piecewise function
        if (samples[sample] > threshold)
            samples[sample] = threshold + drive;
        else if (samples[sample] < -1 * threshold)
            samples[sample] = -1 * (threshold + drive);
        else if (samples[sample] != 0)
            samples[sample] = samples[sample] + (samples[sample] < 0 ? -1 : 1) * drive;
        else
            samples[sample] = 0;
    }
}

void HardClipDistortion::setDrive(float drive)
{
    this->drive = drive;
}

void HardClipDistortion::setThreshold(float threshold)
{
    this->threshold = threshold;
}
