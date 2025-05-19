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
    
    // reference: https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }
};