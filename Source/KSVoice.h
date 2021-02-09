/*
  ==============================================================================

    KSVoice.h
    Created: 7 Feb 2021 11:54:06am
    Author:  david

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

struct KSSound : public juce::SynthesiserSound
{
    KSSound() {}

    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }
};

class KSVoice : public juce::SynthesiserVoice
{
public:
    KSVoice() {};
    ~KSVoice() {};

    void startNote(int midiNote, float velocity, juce::SynthesiserSound*, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff);

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void pitchWheelMoved(int newPitchWheelValue) override;

    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override {};

private:

    juce::Random rand;

    int currentNote;

    const static int bufferSize = 1 << 16;

    float excitation[bufferSize];
    float lowpassDelayBuffer[bufferSize];
    float allpassTuningBuffer[bufferSize];
    float lowpassDynamicsBuffer[bufferSize];

    int bufIdx = 0;
    int period;

    // roughly based on the range of a 6 string guitar
    float upperPitchLimit = 1300;
    float lowerPitchLimit = 80;

    float middlePitchOmega = juce::MathConstants<float>::twoPi * std::sqrt(upperPitchLimit * lowerPitchLimit);

    float R;

    float L = 1000;

    float rho = 0.99;

    float rhoTailoff;

    float t60 = 0.2; // tailoff length in seconds
    int lastTailoffIdx;

    float S = 0.5;

    float mu = 1.f/7;

    bool playing = false;
    bool tailoff = false;

    int pitchBendSemitones = 12;

    float pizzicatoFactor = 10;

    float allpassTuningC;

    void calculatePitchInfo(int midiNote, int pwPosition);
    void createExcitation(float velocity);
};