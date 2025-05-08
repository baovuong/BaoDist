/*
  ==============================================================================

    Distortion.h
    Created: 1 May 2025 1:49:46am
    Author:  vqbao

  ==============================================================================
*/

#pragma once

#include "Clippings/Clipping.h"

class Distortion
{
public:
    void process(int numSamples, float* samples, float drive, Clipping *clipping);
};