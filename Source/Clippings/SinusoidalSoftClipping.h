/*
  ==============================================================================

    SinusoidalSoftClipping.h
    Created: 19 May 2025 12:57:39am
    Author:  vqbao

  ==============================================================================
*/

#pragma once
#include "Clipping.h"

class SinusoidalSoftClipping : public Clipping
{
public:
    void clip(float* samples, int sampleIndex, float factor) override;
    bool hasFactor() override;
};