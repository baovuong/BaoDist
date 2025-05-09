/*
  ==============================================================================

    BevyLookAndFeel.h
    Created: 8 May 2025 6:27:47pm
    Author:  vqbao

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class BevyLookAndFeel : public juce::LookAndFeel_V4
{
public:
    BevyLookAndFeel();

    // overrides
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider);
};