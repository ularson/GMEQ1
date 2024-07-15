/*
  ==============================================================================

    CustomButtons.h
    Created: 8 Apr 2024 11:38:56pm
    Author:  Ulf Larsson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct PowerButton : juce::ToggleButton { };

struct AnalyzerButton : juce::ToggleButton
{
    void resized() override;
    
    juce::Path randomPath;
};
