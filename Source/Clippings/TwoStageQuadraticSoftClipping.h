/*
  ==============================================================================

    TwoStageQuadraticSoftClipping.h
    Created: 22 May 2025 12:29:14pm
    Author:  vqbao

  ==============================================================================
*/

#pragma once
#include "Clipping.h"

class TwoStageQuadraticSoftClipping : public Clipping
{
public:
    void clip(float* samples, int sampleIndex, float factor) override;
    bool hasFactor() override;
};