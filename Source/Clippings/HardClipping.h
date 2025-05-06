/*
  ==============================================================================

    HardClipping.h
    Created: 5 May 2025 4:01:24pm
    Author:  bvuong

  ==============================================================================
*/

#pragma once

#include "Clipping.h"

class HardClipping : public Clipping
{
public:
    void clip(float* samples, int sampleIndex) override;
};