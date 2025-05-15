/*
  ==============================================================================

    BevyLookAndFeel.h
    Created: 8 May 2025 6:27:47pm
    Author:  vqbao

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomFonts.h"

class BevyLookAndFeel : public juce::LookAndFeel_V4
{
public:
    BevyLookAndFeel();

    // overrides
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;


private:
    const juce::Colour invisible = juce::Colour::fromRGBA(0, 0, 0, 0);
    const juce::Colour outlineColor = juce::Colour::fromRGB(110, 255, 127);
    const juce::Colour componentBackgroundColor = juce::Colour::fromRGB(40, 40, 40);
    
    juce::Colour disabled;

    CustomFonts customFonts;
};