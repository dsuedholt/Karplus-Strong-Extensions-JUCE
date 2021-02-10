/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "KSVoice.h"

//==============================================================================
/**
*/
class KarplusStrongAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    KarplusStrongAudioProcessor();
    ~KarplusStrongAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void setL(float L) { params.L = L; };
    void setRho(float rho) { params.rho = rho; };
    void setS(float S) { params.S = S; };
    void setMu(float mu) { params.mu = mu; };
    void setT60(float t60) { params.t60 = t60; };
    void setPitchBend(int semitones) { params.pitchBendSemitones = semitones; };
    void setPickStrength(float pickstrength) { params.pickStrengthFactor = pickstrength; };

private:
    //==============================================================================

    juce::Synthesiser synth;
    struct KPStrongParams params;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KarplusStrongAudioProcessor)
};
