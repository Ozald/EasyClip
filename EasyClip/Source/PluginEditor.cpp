/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EasyClipAudioProcessorEditor::EasyClipAudioProcessorEditor (EasyClipAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 20);
	addAndMakeVisible(gainSlider);

	gainLabel.setText("Out Gain", juce::dontSendNotification);
	gainLabel.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(gainLabel);

    thresholdSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    thresholdSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 20);
    addAndMakeVisible(thresholdSlider);

    thresholdLabel.setText("Threshold", juce::dontSendNotification);
    thresholdLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(thresholdLabel);

    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 20);
    addAndMakeVisible(driveSlider);

    driveLabel.setText("Drive", juce::dontSendNotification);
    driveLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(driveLabel);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "OUTGAIN", gainSlider);
    thresholdAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "THRESHOLD", thresholdSlider);
	driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "DRIVE", driveSlider);


    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

EasyClipAudioProcessorEditor::~EasyClipAudioProcessorEditor()
{
}

//==============================================================================
void EasyClipAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //g.setColour (juce::Colours::white);
    //g.setFont (juce::FontOptions (15.0f));
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EasyClipAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	auto bounds = getLocalBounds().reduced(20);

	int columnWidth = bounds.getWidth() / 3;

	auto leftColumn = bounds.removeFromLeft(columnWidth).reduced(10);
	auto middleColumn = bounds.removeFromLeft(columnWidth).reduced(10);
	auto rightColumn = bounds.reduced(10);

	driveLabel.setBounds(leftColumn.removeFromTop(20));
    driveSlider.setBounds(leftColumn);

	thresholdLabel.setBounds(middleColumn.removeFromTop(20));
    thresholdSlider.setBounds(middleColumn);

    gainLabel.setBounds(rightColumn.removeFromTop(20));
    gainSlider.setBounds(rightColumn);
}
