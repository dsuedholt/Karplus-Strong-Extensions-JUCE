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
class KarplusStrongAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Slider::Listener
{
public:
    KarplusStrongAudioProcessorEditor (KarplusStrongAudioProcessor&);
    ~KarplusStrongAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KarplusStrongAudioProcessor& audioProcessor;

    juce::Slider loudnessSlider;
    juce::Label  loudnessLabel;
    juce::Slider rhoSlider;
    juce::Label  rhoLabel;
    juce::Slider decayStretchSlider;
    juce::Label  decayStretchLabel;
    juce::Slider tailoffSlider;
    juce::Label  tailoffLabel;
    juce::Slider pitchBendRangeSlider;
    juce::Label  pitchBendRangeLabel;
    juce::Slider pickStrengthSlider;
    juce::Label  pickStrengthLabel;
    juce::Slider pickPositionSlider;
    juce::Label  pickPositionLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KarplusStrongAudioProcessorEditor)
};
