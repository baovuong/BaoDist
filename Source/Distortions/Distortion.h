/*
  ==============================================================================

    Distortion.h
    Created: 1 May 2025 1:49:46am
    Author:  vqbao

  ==============================================================================
*/

#pragma once

class Distortion
{
public:
    virtual void process(int numSamples, float* samples) = 0;
};