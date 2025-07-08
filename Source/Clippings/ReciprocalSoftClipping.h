/*
  ==============================================================================

    ReciprocalSoftClipping.h
    Created: 8 Jul 2025 4:52:58pm
    Author:  vqbao

  ==============================================================================
*/

#pragma once
#include "Clipping.h"

class ReciprocalSoftClipping : public Clipping
{
public:
    void clip(float* samples, int sampleIndex, float factor) override;
    bool hasFactor() override;
};