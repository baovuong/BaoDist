/*
  ==============================================================================

    HardClipDistortion.cpp
    Created: 1 May 2025 1:50:04am
    Author:  vqbao

  ==============================================================================
*/

#include <JuceHeader.h>
#include "HardClipDistortion.h"

#define DRIVE_SCALE 2.0f
#define BOTTOM_THRESHOLD 0.0005f

void HardClipDistortion::process(int numSamples, float* samples)
{
    for (int sample = 0; sample < numSamples; ++sample)
    {
        // noise gate cuz we really need it lol
        if (abs(samples[sample] < BOTTOM_THRESHOLD))
            continue;

        // add the drive
        samples[sample] *= drive * DRIVE_SCALE;

        // hard-clipping distortion piecewise function
        if (samples[sample] > threshold)
            samples[sample] = threshold;
        else if (samples[sample] < -1 * threshold)
            samples[sample] = -1 * threshold;
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
