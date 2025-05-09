/*
  ==============================================================================

    BevyLookAndFeel.cpp
    Created: 8 May 2025 6:27:47pm
    Author:  vqbao

  ==============================================================================
*/

#include "BevyLookAndFeel.h"

#define INVISIBLE juce::Colour::fromRGBA(0,0,0,0)
#define DISABLED_COLOR findColour(juce::ResizableWindow::backgroundColourId).brighter(0.02f)
#define OUTLINE_COLOR juce::Colour::fromRGB(110, 255, 127)
#define COMPONENT_BACKGROUND_COLOR juce::Colour::fromRGB(40, 40, 40)
#define BACKGROUND_COLOR juce::Colour::fromRGB(20, 20, 20)

BevyLookAndFeel::BevyLookAndFeel()
{
    // knob colors
    setColour(juce::Slider::thumbColourId, OUTLINE_COLOR);
    setColour(juce::Slider::rotarySliderOutlineColourId, COMPONENT_BACKGROUND_COLOR);
    setColour(juce::Slider::rotarySliderFillColourId, findColour(juce::Slider::rotarySliderOutlineColourId).brighter(0.05f));

    // general background
    setColour(juce::ResizableWindow::backgroundColourId, BACKGROUND_COLOR);

    // combobox
    setColour(juce::ComboBox::backgroundColourId, COMPONENT_BACKGROUND_COLOR);
    setColour(juce::ComboBox::ColourIds::outlineColourId, COMPONENT_BACKGROUND_COLOR.darker(0.05f));

    // popup
    setColour(juce::PopupMenu::backgroundColourId, COMPONENT_BACKGROUND_COLOR);
    setColour(juce::PopupMenu::highlightedBackgroundColourId, COMPONENT_BACKGROUND_COLOR.brighter(0.2f));
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

    //juce::Colour disabledColor = findColour(juce::ResizableWindow::backgroundColourId).brighter(0.02f);

    // === full circle ===
    g.setColour(slider.isEnabled() 
        ? findColour(juce::Slider::rotarySliderOutlineColourId)
        : DISABLED_COLOR);
    g.fillEllipse(rx, ry, rw, rw);

    // === dial center ===
    juce::Path dialCenter;

    dialCenter.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0);
    g.setColour(slider.isEnabled()
        ? findColour(juce::Slider::rotarySliderFillColourId)
        : DISABLED_COLOR.brighter(0.01f));
    g.fillPath(dialCenter);


    // === pointer ===
    juce::Path pointerLevel;
    pointerLevel.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, 0);
    g.setColour(slider.isEnabled()
        ? findColour(juce::Slider::thumbColourId).darker(2*(1.0f - sliderPosProportional))
        : INVISIBLE);
    g.fillPath(pointerLevel);


    g.setColour(slider.isEnabled() 
        ? findColour(juce::Slider::rotarySliderOutlineColourId) 
        : DISABLED_COLOR);
    g.fillEllipse(centreX - dialRadius, centreY - dialRadius, 2 * dialRadius, 2 * dialRadius);
}
