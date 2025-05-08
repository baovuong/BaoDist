/*
  ==============================================================================

    HomographicSoftClipping.h
    Created: 7 May 2025 9:55:11pm
    Author:  vqbao

  ==============================================================================
*/

#pragma once
#include "Clipping.h"

class HomographicSoftClipping : public Clipping
{
public:
    void clip(float* samples, int sampleIndex, float factor) override;
};