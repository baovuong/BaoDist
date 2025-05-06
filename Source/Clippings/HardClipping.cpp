/*
  ==============================================================================

    HardClipping.cpp
    Created: 5 May 2025 4:01:24pm
    Author:  bvuong

  ==============================================================================
*/

#include "HardClipping.h"


void HardClipping::clip(float* samples, int sampleIndex)
{
    // hard-clipping distortion piecewise function
    if (samples[sampleIndex] > THRESHOLD)
        samples[sampleIndex] = THRESHOLD;
    else if (samples[sampleIndex] < -1 * THRESHOLD)
        samples[sampleIndex] = -1 * THRESHOLD;
}