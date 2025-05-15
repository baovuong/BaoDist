/*
  ==============================================================================

    BevyLookAndFeel.cpp
    Created: 8 May 2025 6:27:47pm
    Author:  vqbao

  ==============================================================================
*/

#include "BevyLookAndFeel.h"

BevyLookAndFeel::BevyLookAndFeel()
{
    juce::LookAndFeel::setDefaultLookAndFeel(this);
    // knob colors
    setColour(juce::Slider::thumbColourId, outlineColor);
    setColour(juce::Slider::rotarySliderOutlineColourId, componentBackgroundColor);
    setColour(juce::Slider::rotarySliderFillColourId, findColour(juce::Slider::rotarySliderOutlineColourId).brighter(0.05f));

    // general background
    setColour(juce::ResizableWindow::backgroundColourId, juce::Colour::fromRGB(20, 20, 20));

    // combobox
    setColour(juce::ComboBox::backgroundColourId, componentBackgroundColor);
    setColour(juce::ComboBox::ColourIds::outlineColourId, componentBackgroundColor.darker(0.05f));

    // popup
    setColour(juce::PopupMenu::backgroundColourId, componentBackgroundColor);
    setColour(juce::PopupMenu::highlightedBackgroundColourId, componentBackgroundColor.brighter(0.2f));

    // misc colors
    disabled = findColour(juce::ResizableWindow::backgroundColourId).brighter(0.02f);

    setDefaultSansSerifTypeface(customFonts.getGontserrat().getTypefacePtr());
}

void BevyLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    float radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
    float centreX = (float)x + (float)width * 0.5f;
    float centreY = (float)y + (float)height * 0.5f;
    float rx = centreX - radius;
    float ry = centreY - radius;
    float rw = radius * 2.0f;
    float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    float dialRadius = radius * 0.9f;

    // === full circle ===
    g.setColour(slider.isEnabled() 
        ? findColour(juce::Slider::rotarySliderOutlineColourId)
        : disabled);
    g.fillEllipse(rx, ry, rw, rw);

    // === dial center ===
    juce::Path dialCenter;

    dialCenter.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0);
    g.setColour(slider.isEnabled()
        ? findColour(juce::Slider::rotarySliderFillColourId)
        : disabled.brighter(0.01f));
    g.fillPath(dialCenter);


    // === pointer ===
    juce::Path pointerLevel;
    pointerLevel.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, 0);
    g.setColour(slider.isEnabled()
        ? findColour(juce::Slider::thumbColourId).darker(2*(1.0f - sliderPosProportional))
        : invisible);
    g.fillPath(pointerLevel);


    g.setColour(slider.isEnabled() 
        ? findColour(juce::Slider::rotarySliderOutlineColourId) 
        : disabled);
    g.fillEllipse(centreX - dialRadius, centreY - dialRadius, 2 * dialRadius, 2 * dialRadius);
}
