/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BevyDistortionAudioProcessorEditor::BevyDistortionAudioProcessorEditor (BevyDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    //knob.setSliderStyle(juce::Slider::Rotary);
    //knob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    //knob.setRange(0.0, 1.0, 0.01); // Example range: 0.0 to 1.0 with 0.01 steps
    //knob.setValue(0.5); // Default value
    //addAndMakeVisible(knob); // Add the knob to the editor
}

BevyDistortionAudioProcessorEditor::~BevyDistortionAudioProcessorEditor()
{
}

//==============================================================================
void BevyDistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void BevyDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
