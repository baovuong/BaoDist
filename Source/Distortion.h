/*
  ==============================================================================

    Distortion.h
    Created: 1 May 2025 1:49:46am
    Author:  vqbao

  ==============================================================================
*/

#pragma once

#include "Clippings/Clipping.h"

#define DRIVE_SCALE 2.0f
#define BOTTOM_THRESHOLD 0.0005f

class Distortion
{
public:
    void process(int numSamples, float* samples, float drive, Clipping *clipping);
};