/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
peak1FreqSlider(*audioProcessor.apvts.getParameter("Peak1 Freq"), "Hz"),
peak1GainSlider(*audioProcessor.apvts.getParameter("Peak1 Gain"), "dB"),
peak1QualitySlider(*audioProcessor.apvts.getParameter("Peak1 Quality"), ""),
peak2FreqSlider(*audioProcessor.apvts.getParameter("Peak2 Freq"), "Hz"),
peak2GainSlider(*audioProcessor.apvts.getParameter("Peak2 Gain"), "dB"),
peak2QualitySlider(*audioProcessor.apvts.getParameter("Peak2 Quality"), ""),
peak3FreqSlider(*audioProcessor.apvts.getParameter("Peak3 Freq"), "Hz"),
peak3GainSlider(*audioProcessor.apvts.getParameter("Peak3 Gain"), "dB"),
peak3QualitySlider(*audioProcessor.apvts.getParameter("Peak3 Quality"), ""),
lowCutFreqSlider(*audioProcessor.apvts.getParameter("LowCut Freq"), "Hz"),
highCutFreqSlider(*audioProcessor.apvts.getParameter("HighCut Freq"), "Hz"),
lowCutSlopeSlider(*audioProcessor.apvts.getParameter("LowCut Slope"), "dB/Oct"),
highCutSlopeSlider(*audioProcessor.apvts.getParameter("HighCut Slope"), "db/Oct"),

responseCurveComponent(audioProcessor),

peak1FreqSliderAttachment(audioProcessor.apvts, "Peak1 Freq", peak1FreqSlider),
peak1GainSliderAttachment(audioProcessor.apvts, "Peak1 Gain", peak1GainSlider),
peak1QualitySliderAttachment(audioProcessor.apvts, "Peak1 Quality", peak1QualitySlider),
peak2FreqSliderAttachment(audioProcessor.apvts, "Peak2 Freq", peak2FreqSlider),
peak2GainSliderAttachment(audioProcessor.apvts, "Peak2 Gain", peak2GainSlider),
peak2QualitySliderAttachment(audioProcessor.apvts, "Peak2 Quality", peak2QualitySlider),
peak3FreqSliderAttachment(audioProcessor.apvts, "Peak3 Freq", peak3FreqSlider),
peak3GainSliderAttachment(audioProcessor.apvts, "Peak3 Gain", peak3GainSlider),
peak3QualitySliderAttachment(audioProcessor.apvts, "Peak3 Quality", peak3QualitySlider),
lowCutFreqSliderAttachment(audioProcessor.apvts, "LowCut Freq", lowCutFreqSlider),
highCutFreqSliderAttachment(audioProcessor.apvts, "HighCut Freq", highCutFreqSlider),
lowCutSlopeSliderAttachment(audioProcessor.apvts, "LowCut Slope", lowCutSlopeSlider),
highCutSlopeSliderAttachment(audioProcessor.apvts, "HighCut Slope", highCutSlopeSlider),

lowcutBypassButtonAttachment(audioProcessor.apvts, "LowCut Bypassed", lowcutBypassButton),
peak1BypassButtonAttachment(audioProcessor.apvts, "Peak1 Bypassed", peak1BypassButton),
peak2BypassButtonAttachment(audioProcessor.apvts, "Peak2 Bypassed", peak2BypassButton),
peak3BypassButtonAttachment(audioProcessor.apvts, "Peak3 Bypassed", peak3BypassButton),
highcutBypassButtonAttachment(audioProcessor.apvts, "HighCut Bypassed", highcutBypassButton),
analyzerEnabledButtonAttachment(audioProcessor.apvts, "Analyzer Enabled", analyzerEnabledButton)
{
    peak1FreqSlider.labels.add({0.f, "20Hz"});
    peak1FreqSlider.labels.add({1.f, "20kHz"});
    
    peak1GainSlider.labels.add({0.f, "-24dB"});
    peak1GainSlider.labels.add({1.f, "+24dB"});
    
    peak1QualitySlider.labels.add({0.f, "0.1"});
    peak1QualitySlider.labels.add({1.f, "10.0"});
    
    peak2FreqSlider.labels.add({0.f, "20Hz"});
    peak2FreqSlider.labels.add({1.f, "20kHz"});
    
    peak2GainSlider.labels.add({0.f, "-24dB"});
    peak2GainSlider.labels.add({1.f, "+24dB"});
    
    peak2QualitySlider.labels.add({0.f, "0.1"});
    peak2QualitySlider.labels.add({1.f, "10.0"});
    
    peak3FreqSlider.labels.add({0.f, "20Hz"});
    peak3FreqSlider.labels.add({1.f, "20kHz"});
    
    peak3GainSlider.labels.add({0.f, "-24dB"});
    peak3GainSlider.labels.add({1.f, "+24dB"});
    
    peak3QualitySlider.labels.add({0.f, "0.1"});
    peak3QualitySlider.labels.add({1.f, "10.0"});
    
    lowCutFreqSlider.labels.add({0.f, "20Hz"});
    lowCutFreqSlider.labels.add({1.f, "20kHz"});
    
    highCutFreqSlider.labels.add({0.f, "20Hz"});
    highCutFreqSlider.labels.add({1.f, "20kHz"});
    
    lowCutSlopeSlider.labels.add({0.0f, "12"});
    lowCutSlopeSlider.labels.add({1.f, "48"});
    
    highCutSlopeSlider.labels.add({0.0f, "12"});
    highCutSlopeSlider.labels.add({1.f, "48"});
    
    for( auto* comp : getComps() )
    {
        addAndMakeVisible(comp);
    }
    
    peak1BypassButton.setLookAndFeel(&lnf);
    peak2BypassButton.setLookAndFeel(&lnf);
    peak3BypassButton.setLookAndFeel(&lnf);
    highcutBypassButton.setLookAndFeel(&lnf);
    lowcutBypassButton.setLookAndFeel(&lnf);

    analyzerEnabledButton.setLookAndFeel(&lnf);
    
    auto safePtr = juce::Component::SafePointer<SimpleEQAudioProcessorEditor>(this);
    peak1BypassButton.onClick = [safePtr]()
    {
        if( auto* comp = safePtr.getComponent() )
        {
            auto bypassed = comp->peak1BypassButton.getToggleState();
            
            comp->peak1FreqSlider.setEnabled( !bypassed );
            comp->peak1GainSlider.setEnabled( !bypassed );
            comp->peak1QualitySlider.setEnabled( !bypassed );
        }
    };
    
    peak2BypassButton.onClick = [safePtr]()
    {
        if( auto* comp = safePtr.getComponent() )
        {
            auto bypassed = comp->peak2BypassButton.getToggleState();
            
            comp->peak2FreqSlider.setEnabled( !bypassed );
            comp->peak2GainSlider.setEnabled( !bypassed );
            comp->peak2QualitySlider.setEnabled( !bypassed );
        }
    };
    
    peak3BypassButton.onClick = [safePtr]()
    {
        if( auto* comp = safePtr.getComponent() )
        {
            auto bypassed = comp->peak3BypassButton.getToggleState();
            
            comp->peak3FreqSlider.setEnabled( !bypassed );
            comp->peak3GainSlider.setEnabled( !bypassed );
            comp->peak3QualitySlider.setEnabled( !bypassed );
        }
    };
    

    lowcutBypassButton.onClick = [safePtr]()
    {
        if( auto* comp = safePtr.getComponent() )
        {
            auto bypassed = comp->lowcutBypassButton.getToggleState();
            
            comp->lowCutFreqSlider.setEnabled( !bypassed );
            comp->lowCutSlopeSlider.setEnabled( !bypassed );
        }
    };
    
    highcutBypassButton.onClick = [safePtr]()
    {
        if( auto* comp = safePtr.getComponent() )
        {
            auto bypassed = comp->highcutBypassButton.getToggleState();
            
            comp->highCutFreqSlider.setEnabled( !bypassed );
            comp->highCutSlopeSlider.setEnabled( !bypassed );
        }
    };

    analyzerEnabledButton.onClick = [safePtr]()
    {
        if( auto* comp = safePtr.getComponent() )
        {
            auto enabled = comp->analyzerEnabledButton.getToggleState();
            comp->responseCurveComponent.toggleAnalysisEnablement(enabled);
        }
    };
    
    setSize (700, 520);
}

SimpleEQAudioProcessorEditor::~SimpleEQAudioProcessorEditor()
{
    peak1BypassButton.setLookAndFeel(nullptr);
    peak2BypassButton.setLookAndFeel(nullptr);
    peak3BypassButton.setLookAndFeel(nullptr);
    highcutBypassButton.setLookAndFeel(nullptr);
    lowcutBypassButton.setLookAndFeel(nullptr);

    analyzerEnabledButton.setLookAndFeel(nullptr);
}

//==============================================================================
void SimpleEQAudioProcessorEditor::paint(juce::Graphics &g)
{
    using namespace juce;
    
    g.fillAll(ColorScheme::getModuleBackgroundColor());
    
    g.setFont(Font("Iosevka Term Slab", 30, 0)); //https://github.com/be5invis/Iosevka
    
    String title { "GM EQ 1" };
    g.setFont(20);
    
    auto bounds = getLocalBounds().withTrimmedTop(5);
    
    g.setColour(ColorScheme::getTitleColor());
    g.drawFittedText(title, bounds, juce::Justification::centredTop, 1);
}

void SimpleEQAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromTop(4);
    
    auto analyzerEnabledArea = bounds.removeFromTop(25);
    
    analyzerEnabledArea.setWidth(50);
    analyzerEnabledArea.setX(5);
    analyzerEnabledArea.removeFromTop(2);
    
    analyzerEnabledButton.setBounds(analyzerEnabledArea);
    
    bounds.removeFromTop(5);
    

    auto responseArea = bounds.removeFromTop(180);

    responseCurveComponent.setBounds(responseArea);
    
    bounds.removeFromTop(5);
    
    auto lowCutArea = bounds.removeFromLeft(bounds.getWidth() * 0.25);
    auto peak1Area = bounds.removeFromLeft(bounds.getWidth() * 0.2);
    auto peak2Area = bounds.removeFromLeft(bounds.getWidth() * 0.3);
    auto peak3Area = bounds.removeFromLeft(bounds.getWidth() * 0.4);
    auto highCutArea = bounds.removeFromRight(bounds.getWidth() * 1.2);
    
    lowcutBypassButton.setBounds(lowCutArea.removeFromTop(25));
    lowCutFreqSlider.setBounds(lowCutArea.removeFromTop(lowCutArea.getHeight() * 0.5));
    lowCutSlopeSlider.setBounds(lowCutArea);
    
    highcutBypassButton.setBounds(highCutArea.removeFromTop(25));
    highCutFreqSlider.setBounds(highCutArea.removeFromTop(highCutArea.getHeight() * 0.5));
    highCutSlopeSlider.setBounds(highCutArea);
    
    peak1BypassButton.setBounds(peak1Area.removeFromTop(25));
    peak1FreqSlider.setBounds(peak1Area.removeFromTop(peak1Area.getHeight() * 0.33));
    peak1GainSlider.setBounds(peak1Area.removeFromTop(peak1Area.getHeight() * 0.5));
    peak1QualitySlider.setBounds(peak1Area);
    
    peak2BypassButton.setBounds(peak2Area.removeFromTop(25));
    peak2FreqSlider.setBounds(peak2Area.removeFromTop(peak2Area.getHeight() * 0.33));
    peak2GainSlider.setBounds(peak2Area.removeFromTop(peak2Area.getHeight() * 0.5));
    peak2QualitySlider.setBounds(peak2Area);
    
    peak3BypassButton.setBounds(peak3Area.removeFromTop(25));
    peak3FreqSlider.setBounds(peak3Area.removeFromTop(peak3Area.getHeight() * 0.33));
    peak3GainSlider.setBounds(peak3Area.removeFromTop(peak3Area.getHeight() * 0.5));
    peak3QualitySlider.setBounds(peak3Area);
}

std::vector<juce::Component*> SimpleEQAudioProcessorEditor::getComps()
{
    return
    {
        &peak1FreqSlider,
        &peak1GainSlider,
        &peak1QualitySlider,
        &peak2FreqSlider,
        &peak2GainSlider,
        &peak2QualitySlider,
        &peak3FreqSlider,
        &peak3GainSlider,
        &peak3QualitySlider,
        &lowCutFreqSlider,
        &highCutFreqSlider,
        &lowCutSlopeSlider,
        &highCutSlopeSlider,
        &responseCurveComponent,
        
        &lowcutBypassButton,
        &peak1BypassButton,
        &peak2BypassButton,
        &peak3BypassButton,
        &highcutBypassButton,
        &analyzerEnabledButton
    };
}
