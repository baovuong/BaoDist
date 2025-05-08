/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class BevyDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BevyDistortionAudioProcessorEditor (BevyDistortionAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~BevyDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void distortionMenuChanged();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BevyDistortionAudioProcessor& audioProcessor;

	
	juce::Label titleLabel;

    juce::AudioProcessorValueTreeState& valueTreeState;
    
    juce::Slider driveKnob;
    juce::Label driveLabel;
	std::unique_ptr<SliderAttachment> driveAttachment;

	juce::Slider levelKnob;
	juce::Label levelLabel;
	std::unique_ptr<SliderAttachment> levelAttachment;

    juce::Slider factorKnob;
    juce::Label factorLabel;
    std::unique_ptr<SliderAttachment> factorAttachment;

    juce::Label footer;

    // TODO create dropdown to choose different clipping methods
    juce::ComboBox distortionMenu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BevyDistortionAudioProcessorEditor)
};
