/*
  ==============================================================================

    WhoopsieSineSoftClipping.h
    Created: 22 May 2025 1:04:28pm
    Author:  vqbao

  ==============================================================================
*/

#pragma once
#include "Clipping.h"

class WhoopsieSineSoftClipping : public Clipping
{
public:
    void clip(float* samples, int sampleIndex, float factor) override;
    bool hasFactor() override;
};