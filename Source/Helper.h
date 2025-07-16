/*
  ==============================================================================

    Helper.h
    Created: 22 May 2025 2:06:54am
    Author:  vqbao

  ==============================================================================
*/

#pragma once

namespace Helper
{
    constexpr float kTwoThirds = 2.f / 3.f;
    
    float scale(float factor, float bottom, float top);
    bool isBetween(float input, float bottom, float top);
    
    // reference: https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
    template <typename T> static int sgn(T val) 
    {
        return (T(0) < val) - (val < T(0));
    }
}