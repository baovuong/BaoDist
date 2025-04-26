/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BevyDistortionAudioProcessorEditor::BevyDistortionAudioProcessorEditor(BevyDistortionAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
	: AudioProcessorEditor(&p), audioProcessor(p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	// Set up the title label
	titleLabel.setText("Bevy Distortion", juce::dontSendNotification);
	titleLabel.setFont(juce::Font(24.0f, juce::Font::bold));
	titleLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(titleLabel); // Add the label to the editor

    driveKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    driveKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    driveKnob.setRange(0.0, 1.0, 0.01); // Example range: 0.0 to 1.0 with 0.01 steps
    driveKnob.setValue(0.5); // Default value
    addAndMakeVisible(driveKnob); // Add the knob to the editor

	driveLabel.setText("Drive", juce::dontSendNotification);
	driveLabel.attachToComponent(&driveKnob, false);
	driveLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(driveLabel); // Add the label to the editor

	levelKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	levelKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    levelKnob.setRange(0.0, 1.0, 0.01); // Example range: 0.0 to 1.0 with 0.01 steps
    levelKnob.setValue(0.5); // Default value
    addAndMakeVisible(levelKnob); // Add the knob to the editor

	levelLabel.setText("Level", juce::dontSendNotification);
	levelLabel.attachToComponent(&levelKnob, false);
	levelLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(levelLabel); // Add the label to the editor

	driveAttachment.reset(new SliderAttachment(valueTreeState, "drive", driveKnob)); // Attach the knob to the parameter
	levelAttachment.reset(new SliderAttachment(valueTreeState, "level", levelKnob)); // Attach the knob to the parameter
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
}

void BevyDistortionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	auto area = getLocalBounds();

	titleLabel.setBounds(area.removeFromTop(40).reduced(10));

	auto knobArea = area.removeFromBottom(area.getHeight()-titleLabel.getBounds().getHeight() - 10).reduced(10);
	driveKnob.setBounds(knobArea.removeFromLeft(knobArea.getWidth() / 2));
	levelKnob.setBounds(knobArea);
}
