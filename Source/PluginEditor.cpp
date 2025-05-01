/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define KNOB_LABEL_HEIGHT 14.0f 
#define TITLE_LABEL_HEIGHT 7.0f

//==============================================================================
BevyDistortionAudioProcessorEditor::BevyDistortionAudioProcessorEditor(BevyDistortionAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
	: AudioProcessorEditor(&p), audioProcessor(p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);

	// Set up the title label
	titleLabel.setText("Bevy Distortion", juce::dontSendNotification);
	titleLabel.setFont(juce::FontOptions(
		getHeight() / TITLE_LABEL_HEIGHT, 
		juce::Font::FontStyleFlags::bold));

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
	driveLabel.setFont(juce::FontOptions(
		getHeight() / KNOB_LABEL_HEIGHT, 
		juce::Font::FontStyleFlags::bold));
	addAndMakeVisible(driveLabel); // Add the label to the editor

	levelKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	levelKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    levelKnob.setRange(0.0, 1.0, 0.01); // Example range: 0.0 to 1.0 with 0.01 steps
    levelKnob.setValue(0.5); // Default value
    addAndMakeVisible(levelKnob); // Add the knob to the editor

	levelLabel.setText("Level", juce::dontSendNotification);
	levelLabel.attachToComponent(&levelKnob, false);
	levelLabel.setJustificationType(juce::Justification::centred);
	levelLabel.setFont(juce::FontOptions(
		getHeight() / KNOB_LABEL_HEIGHT, 
		juce::Font::FontStyleFlags::bold));
	addAndMakeVisible(levelLabel); // Add the label to the editor

	driveAttachment.reset(new SliderAttachment(valueTreeState, "drive", driveKnob)); // Attach the knob to the parameter
	levelAttachment.reset(new SliderAttachment(valueTreeState, "level", levelKnob)); // Attach the knob to the parameter

	// footer

	juce::String footerText = ProjectInfo::projectName;
	footerText += " ";
	footerText += ProjectInfo::versionString;
	footerText += " - ";
	footerText += ProjectInfo::companyName;
	footer.setText(footerText, juce::dontSendNotification);
	footer.setJustificationType(juce::Justification::right);
	footer.setFont(juce::FontOptions(getHeight() / 30));
	addAndMakeVisible(footer);
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

	titleLabel.setBounds(area.removeFromTop(getHeight() / 5).reduced(10));
	footer.setBounds(area.removeFromBottom(getHeight() / 25));

	auto knobArea = area.removeFromBottom(area.getHeight() - titleLabel.getBounds().getHeight() - 10).reduced(10);
	driveKnob.setBounds(knobArea.removeFromLeft(knobArea.getWidth() / 2));
	levelKnob.setBounds(knobArea);
}
