/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GUI/LookAndFeel.h"
#include "GUI/CustomButtons.h"
#include "GUI/RotarySliderWithLabels.h"
#include "GUI/ResponseCurveComponent.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SimpleEQAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor&);
    ~SimpleEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleEQAudioProcessor& audioProcessor;

    
    RotarySliderWithLabels peak1FreqSlider,
    peak1GainSlider,
    peak1QualitySlider,
    peak2FreqSlider,
    peak2GainSlider,
    peak2QualitySlider,
    peak3FreqSlider,
    peak3GainSlider,
    peak3QualitySlider,
    lowCutFreqSlider,
    highCutFreqSlider,
    lowCutSlopeSlider,
    highCutSlopeSlider;
    
    ResponseCurveComponent responseCurveComponent;
    
    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;
    
    Attachment peak1FreqSliderAttachment,
                peak1GainSliderAttachment,
                peak1QualitySliderAttachment,
                peak2FreqSliderAttachment,
                peak2GainSliderAttachment,
                peak2QualitySliderAttachment,
                peak3FreqSliderAttachment,
                peak3GainSliderAttachment,
                peak3QualitySliderAttachment,
                lowCutFreqSliderAttachment,
                highCutFreqSliderAttachment,
                lowCutSlopeSliderAttachment,
                highCutSlopeSliderAttachment;

    std::vector<juce::Component*> getComps();
    
    PowerButton lowcutBypassButton, peak1BypassButton, peak2BypassButton, peak3BypassButton, highcutBypassButton;
    AnalyzerButton analyzerEnabledButton;
    
    using ButtonAttachment = APVTS::ButtonAttachment;
    
    ButtonAttachment lowcutBypassButtonAttachment,
                        peak1BypassButtonAttachment,
                        peak2BypassButtonAttachment,
                        peak3BypassButtonAttachment,
                        highcutBypassButtonAttachment,
                        analyzerEnabledButtonAttachment;
    
    LookAndFeel lnf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessorEditor)
};
