/*
  ==============================================================================

    HardClipDistortion.h
    Created: 1 May 2025 1:50:04am
    Author:  vqbao

  ==============================================================================
*/

#pragma once

#include "Distortion.h"

class HardClipDistortion : public Distortion
{
public:
    void process(int numSamples, float* samples);
    
    void setDrive(float drive);
    void setThreshold(float threshold);

private:
    float drive;
    float threshold;
};