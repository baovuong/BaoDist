/*
  ==============================================================================

    Helper.cpp
    Created: 22 May 2025 2:06:54am
    Author:  vqbao

  ==============================================================================
*/

#include "Helper.h"
#include <JuceHeader.h>

float Helper::scale(float factor, float bottom, float top)
{
    return factor * (top - bottom) + bottom;
}

bool Helper::isBetween(float input, float bottom, float top)
{
    return input >= bottom && input <= top;
}
