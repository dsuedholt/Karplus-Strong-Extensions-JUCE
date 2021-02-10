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

struct KPStrongParams
{
    float L = 400;
    float rho = 0.99;
    float S = 0.5;
    float mu = 0.1;
    float t60 = 0.1;
    int pitchBendSemitones = 12;
    float pickStrengthFactor = 1.f;
};

class KSVoice : public juce::SynthesiserVoice
{
public:
    KSVoice(struct KPStrongParams& params) : params(params) {};
    ~KSVoice() {};

    void startNote(int midiNote, float velocity, juce::SynthesiserSound*, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff);

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void pitchWheelMoved(int newPitchWheelValue) override;

    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override {};

private:

    struct KPStrongParams& params;

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

    float rhoTailoff;

    int lastTailoffIdx;

    bool playing = false;
    bool tailoff = false;

    float allpassTuningC;

    void calculatePitchInfo(int midiNote, int pwPosition);
    void createExcitation(float velocity);
};