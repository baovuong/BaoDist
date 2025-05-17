/*
  ==============================================================================

    CustomFonts.cpp
    Created: 14 May 2025 5:40:31pm
    Author:  vqbao

  ==============================================================================
*/

#include "CustomFonts.h"

const juce::Font& CustomFonts::getImpacted()
{
    static juce::Font impacted(juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::IMPACTED_ttf, BinaryData::IMPACTED_ttfSize)));
    return impacted;
}

const juce::Font& CustomFonts::getGontserrat()
{
    static juce::Font gontserrat(juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::GontserratRegular_ttf, BinaryData::GontserratRegular_ttfSize)));
    return gontserrat;
}