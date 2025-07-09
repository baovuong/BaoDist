/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BevyDistortionAudioProcessor::BevyDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    parameters(*this, nullptr, juce::Identifier("BevyParams"),
        {
            std::make_unique<juce::AudioParameterFloat>("drive", "Drive", 0.0f, 1.0f, 0.5f),
            std::make_unique<juce::AudioParameterFloat>("level", "Level", 0.0f, 1.0f, 0.5f),
            std::make_unique<juce::AudioParameterFloat>("factor", "Factor", 0.0f, 1.0f, 0.5f),
            std::make_unique<juce::AudioParameterChoice>("type", "Type",
                juce::StringArray 
                {
                    "Hard Clip", 
                    "Soft Clip (Arc Tangent)", 
                    "Soft Clip (Homographic)", 
                    "Soft Clip (Hyperbolic Tangent)",
                    "Soft Clip (Sinusoidal)",
                    "Soft Clip (Exponential)",
                    "Soft Clip (Two Stage Quadratic)",
                    "Soft Clip (Cubic)",
                    "Soft Clip (Reciprocal)"
                }, 0)
        })
#endif
{
    driveParameter = parameters.getRawParameterValue("drive");
    levelParameter = parameters.getRawParameterValue("level");
    factorParameter = parameters.getRawParameterValue("factor");
    typeParameter = parameters.getRawParameterValue("type");
}

BevyDistortionAudioProcessor::~BevyDistortionAudioProcessor()
{
}

//==============================================================================
const juce::String BevyDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BevyDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BevyDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BevyDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BevyDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BevyDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BevyDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BevyDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BevyDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void BevyDistortionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BevyDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    DBG("Preparing to play... { drive=" << *driveParameter << ", level=" << *levelParameter << " }");
}

void BevyDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BevyDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BevyDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    int totalNumInputChannels  = getTotalNumInputChannels();
    int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* outputData = buffer.getWritePointer (channel);
        const float* inputData = buffer.getReadPointer(channel);

        distortion.process(buffer.getNumSamples(), outputData, *driveParameter, *factorParameter, &chosenDistortion());

        // apply level
        buffer.applyGain(*levelParameter);
    }
}

//==============================================================================
bool BevyDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BevyDistortionAudioProcessor::createEditor()
{
    return new BevyDistortionAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void BevyDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    juce::ValueTree state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void BevyDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(parameters.state.getType()))
        {
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
        }
    }
}

Clipping& BevyDistortionAudioProcessor::chosenDistortion()
{
    // Get the parameter and cast it to AudioParameterChoice
    juce::AudioParameterChoice* typeChoiceParameter = dynamic_cast<juce::AudioParameterChoice*>(parameters.getParameter("type"));
    int choice = typeChoiceParameter == nullptr ? 1 : typeChoiceParameter->getIndex() + 1; // Get the current choice index

    switch (choice) {
    case 1:
        return hardClipping;
        break;
    case 2:
        return arcTanSoftClipping;
        break;
    case 3:
        return homographicSoftClipping;
        break;
    case 4:
        return hyperbolicTangentSoftClipping;
        break;
    case 5:
        return sinusoidalSoftClipping;
        break;
    case 6:
        return exponentialSoftClipping;
        break;
    case 7:
        return twoStageQuadraticSoftClipping;
        break;
    case 8:
        return cubicSoftClipping;
        break;
    case 9:
        return reciprocalSoftClipping;
        break;
    }

    return hardClipping;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BevyDistortionAudioProcessor();
}
