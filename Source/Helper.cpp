/*
  ==============================================================================

    Helper.cpp
    Created: 22 May 2025 2:06:54am
    Author:  vqbao

  ==============================================================================
*/

#include "Helper.h"

float Helper::scale(float factor, float bottom, float top)
{
    return factor * (top - bottom) + bottom;
}
