/*
  ==============================================================================

    Clipping.h
    Created: 5 May 2025 3:49:54pm
    Author:  bvuong

  ==============================================================================
*/

#pragma once

#define THRESHOLD 1.0f

class Clipping
{
public:
    virtual void clip(float* samples, int sampleIndex, float factor) = 0;
    virtual bool hasFactor() = 0;
};