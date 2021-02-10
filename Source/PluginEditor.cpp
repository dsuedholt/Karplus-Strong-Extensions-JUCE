/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KarplusStrongAudioProcessorEditor::KarplusStrongAudioProcessorEditor (KarplusStrongAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(loudnessSlider);
    loudnessSlider.setRange(80, 1300.0);
    loudnessSlider.setTextValueSuffix(" Hz"); 
    loudnessSlider.addListener(this);
    loudnessSlider.setValue(400);
    
    addAndMakeVisible(loudnessLabel);
    loudnessLabel.setText("Dynamics Lowpass Bandwidth", juce::dontSendNotification);
    loudnessLabel.attachToComponent(&loudnessSlider, true);

    addAndMakeVisible(rhoSlider);
    rhoSlider.setRange(0.8, 1.0);
    rhoSlider.setSkewFactorFromMidPoint(0.99);
    rhoSlider.setTextValueSuffix("");
    rhoSlider.addListener(this);
    rhoSlider.setValue(0.99);

    addAndMakeVisible(rhoLabel);
    rhoLabel.setText("Rho", juce::dontSendNotification);
    rhoLabel.attachToComponent(&rhoSlider, true);

    addAndMakeVisible(decayStretchSlider);
    decayStretchSlider.setRange(0.0, 1.0);
    decayStretchSlider.setTextValueSuffix("");
    decayStretchSlider.addListener(this);
    decayStretchSlider.setValue(0.5);

    addAndMakeVisible(decayStretchLabel);
    decayStretchLabel.setText("Decay Stretch S", juce::dontSendNotification);
    decayStretchLabel.attachToComponent(&decayStretchSlider, true);

    addAndMakeVisible(tailoffSlider);
    tailoffSlider.setRange(0.0, 1.0);
    tailoffSlider.setTextValueSuffix("s");
    tailoffSlider.addListener(this);
    tailoffSlider.setValue(0.1);

    addAndMakeVisible(tailoffLabel);
    tailoffLabel.setText("Tailoff time t_60", juce::dontSendNotification);
    tailoffLabel.attachToComponent(&tailoffSlider, true);

    addAndMakeVisible(pitchBendRangeSlider);
    pitchBendRangeSlider.setRange(1, 12, 1);
    pitchBendRangeSlider.setTextValueSuffix("");
    pitchBendRangeSlider.addListener(this);
    pitchBendRangeSlider.setValue(2);

    addAndMakeVisible(pitchBendRangeLabel);
    pitchBendRangeLabel.setText("Semitone range of MIDI pitch bend", juce::dontSendNotification);
    pitchBendRangeLabel.attachToComponent(&pitchBendRangeSlider, true);

    addAndMakeVisible(pickStrengthSlider);
    pickStrengthSlider.setRange(0.8, 10.0, 0.1);
    pickStrengthSlider.setTextValueSuffix("");
    pickStrengthSlider.addListener(this);
    pickStrengthSlider.setValue(1);

    addAndMakeVisible(pickStrengthLabel);
    pickStrengthLabel.setText("Pick attack (factor extending noise burst)", juce::dontSendNotification);
    pickStrengthLabel.attachToComponent(&pickStrengthSlider, true);

    addAndMakeVisible(pickPositionSlider);
    pickPositionSlider.setRange(0.0, 1.0);
    pickPositionSlider.setTextValueSuffix("s");
    pickPositionSlider.addListener(this);
    pickPositionSlider.setValue(0.1);

    addAndMakeVisible(pickPositionLabel);
    pickPositionLabel.setText("Pick position factor mu", juce::dontSendNotification);
    pickPositionLabel.attachToComponent(&pickPositionSlider, true);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);
}

KarplusStrongAudioProcessorEditor::~KarplusStrongAudioProcessorEditor()
{
}

//==============================================================================
void KarplusStrongAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Supports playing of MIDI notes & glissando through pitchbend signals", juce::Rectangle<int>(50, 230, getWidth() - 200 - 10, getHeight() - 200), juce::Justification::centred, 1);
}

void KarplusStrongAudioProcessorEditor::resized()
{
    auto sliderLeft = 200;
    loudnessSlider.setBounds(sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    rhoSlider.setBounds(sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
    decayStretchSlider.setBounds(sliderLeft, 80, getWidth() - sliderLeft - 10, 20);
    tailoffSlider.setBounds(sliderLeft, 110, getWidth() - sliderLeft - 10, 20);
    pitchBendRangeSlider.setBounds(sliderLeft, 140, getWidth() - sliderLeft - 10, 20);
    pickStrengthSlider.setBounds(sliderLeft, 170, getWidth() - sliderLeft - 10, 20);
    pickPositionSlider.setBounds(sliderLeft, 200, getWidth() - sliderLeft - 10, 20);
}

void KarplusStrongAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &loudnessSlider)
    {
        audioProcessor.setL(slider->getValue());
    }
    if (slider == &rhoSlider)
    {
        audioProcessor.setRho(slider->getValue());
    }
    if (slider == &decayStretchSlider)
    {
        audioProcessor.setS(slider->getValue());
    }
    if (slider == &tailoffSlider)
    {
        audioProcessor.setT60(slider->getValue());
    }
    if (slider == &pitchBendRangeSlider)
    {
        audioProcessor.setPitchBend((int)slider->getValue());
    }
    if (slider == &pickStrengthSlider)
    {
        audioProcessor.setPickStrength(slider->getValue());
    }
    if (slider == &pickPositionSlider)
    {
        audioProcessor.setMu(slider->getValue());
    }
}
