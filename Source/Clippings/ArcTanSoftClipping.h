/*
  ==============================================================================

    SoftClipping.h
    Created: 6 May 2025 1:31:01am
    Author:  vqbao

  ==============================================================================
*/

#pragma once
#include "Clipping.h"

class ArcTanSoftClipping : public Clipping
{
public:
    void clip(float* samples, int sampleIndex) override;
};