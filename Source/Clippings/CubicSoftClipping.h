/*
  ==============================================================================

    CubicSoftClipping.h
    Created: 8 Jul 2025 2:23:05pm
    Author:  vqbao

  ==============================================================================
*/

#pragma once
#include "Clipping.h"

class CubicSoftClipping : public Clipping
{
public:
    void clip(float* samples, int sampleIndex, float factor) override;
    bool hasFactor() override;
};