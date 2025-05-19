/*
  ==============================================================================

    HyperbolicTangentSoftClipping.h
    Created: 18 May 2025 12:33:34am
    Author:  vqbao

  ==============================================================================
*/

#pragma once

#include "Clipping.h"

class HyperbolicTangentSoftClipping : public Clipping
{
    void clip(float* samples, int sampleIndex, float factor) override;
};