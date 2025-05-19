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
    setSize (800, 400);
	setLookAndFeel(&lookAndFeel);

	// Set up the title label
	titleLabel.setText("BEVY DISTORTION", juce::dontSendNotification);
	//titleLabel.setFont(juce::FontOptions(
	//	getHeight() / titleLableHeight));
	titleLabel.setFont(juce::FontOptions(customFonts.getImpacted().getTypefaceName(), getHeight() / titleLabelHeight, juce::Font::plain));

	titleLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(titleLabel); // Add the label to the editor

    driveKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    driveKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    driveKnob.setRange(0.0, 1.0, 0.01); // Example range: 0.0 to 1.0 with 0.01 steps
    driveKnob.setValue(0.5); // Default value
    addAndMakeVisible(driveKnob); // Add the knob to the editor

	driveLabel.setText("DRIVE", juce::dontSendNotification);
	driveLabel.attachToComponent(&driveKnob, false);
	driveLabel.setJustificationType(juce::Justification::centred);
	driveLabel.setFont(juce::FontOptions(
		getHeight() / knobLabelHeight, 
		juce::Font::FontStyleFlags::bold));
	addAndMakeVisible(driveLabel); // Add the label to the editor

	levelKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	levelKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
    levelKnob.setRange(0.0, 1.0, 0.01); // Example range: 0.0 to 1.0 with 0.01 steps
    levelKnob.setValue(0.5); // Default value
    addAndMakeVisible(levelKnob); // Add the knob to the editor

	levelLabel.setText("LEVEL", juce::dontSendNotification);
	levelLabel.attachToComponent(&levelKnob, false);
	levelLabel.setJustificationType(juce::Justification::centred);
	levelLabel.setFont(juce::FontOptions(
		getHeight() / knobLabelHeight, 
		juce::Font::FontStyleFlags::bold));
	addAndMakeVisible(levelLabel); // Add the label to the editor

	factorKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	factorKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 20);
	factorKnob.setRange(0.0, 1.0, 0.01);
	factorKnob.setValue(0.5);
	addAndMakeVisible(factorKnob);

	factorLabel.setText("FACTOR", juce::dontSendNotification);
	factorLabel.attachToComponent(&factorKnob, false);
	factorLabel.setJustificationType(juce::Justification::centred);
	factorLabel.setFont(juce::FontOptions(
		getHeight() / knobLabelHeight,
		juce::Font::FontStyleFlags::bold));
	addAndMakeVisible(factorLabel);

	// populate the distortionMenu 
	
	// TODO genereated by copilot, so double check
	auto* choiceParameter = dynamic_cast<juce::AudioParameterChoice*>(valueTreeState.getParameter("type"));
	if (choiceParameter != nullptr)
	{
		// Add all choices from the parameter
		for (int i = 0; i < choiceParameter->getAllValueStrings().size(); ++i)
		{
			typeMenu.addItem(choiceParameter->getAllValueStrings()[i], i + 1);
		}

		// Set initial value
		typeMenu.setSelectedId(choiceParameter->getIndex() + 1);

		typeMenu.onChange = [this] { distortionMenuChanged(); };
	}
	addAndMakeVisible(typeMenu);

	driveAttachment.reset(new SliderAttachment(valueTreeState, "drive", driveKnob)); // Attach the knob to the parameter
	levelAttachment.reset(new SliderAttachment(valueTreeState, "level", levelKnob)); // Attach the knob to the parameter
	factorAttachment.reset(new SliderAttachment(valueTreeState, "factor", factorKnob));
	typeAttachment.reset(new ComboBoxAttachment(valueTreeState, "type", typeMenu));

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
	setLookAndFeel(nullptr);
	driveAttachment.reset();
	levelAttachment.reset();
	factorAttachment.reset();
	typeAttachment.reset();
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

	typeMenu.setBounds(area.removeFromTop(getHeight() / 10).reduced(getWidth() / 20, 0));

	// Update the knob layout to accommodate three knobs
	auto knobArea = area.reduced(10, 20);
	auto knobWidth = knobArea.getWidth() / 3;  // Divide space into thirds
	driveKnob.setBounds(knobArea.removeFromLeft(knobWidth).reduced(30));
	factorKnob.setBounds(knobArea.removeFromLeft(knobWidth).reduced(30));  // Add factor knob in the middle
	levelKnob.setBounds(knobArea.reduced(30));  // Level knob takes the remaining space
}

void BevyDistortionAudioProcessorEditor::distortionMenuChanged()
{
	// UI change
	factorKnob.setEnabled(audioProcessor.chosenDistortion().hasFactor());

	// state change
	auto* param = dynamic_cast<juce::AudioParameterChoice*>(valueTreeState.getParameter("type"));
	if (param != nullptr)
		param->setValueNotifyingHost((float)(typeMenu.getSelectedId() - 1) / (float)(param->getAllValueStrings().size() - 1));
}
