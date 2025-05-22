/*
  ==============================================================================

    ExponentialSoftClipping.h
    Created: 22 May 2025 2:37:09am
    Author:  vqbao

  ==============================================================================
*/

#pragma once
#include "Clipping.h"

class ExponentialSoftClipping : public Clipping
{
public:
    void clip(float* samples, int sampleIndex, float factor) override;
    bool hasFactor() override;
};