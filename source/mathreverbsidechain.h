#pragma once

#include "mathreverb.h"

namespace Steinberg {
namespace Vst {

//------------------------------------------------------------------------
// MathReverbWithSideChain: directly derived from MathReverb
//------------------------------------------------------------------------
class MathReverbWithSideChain : public MathReverb
{
public:
	// just overwrite some functions
	static FUnknown* createInstance (void* /*context*/)
	{
		return (IAudioProcessor*)new MathReverbWithSideChain;
	}

	tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;
	tresult PLUGIN_API process (ProcessData& data) SMTG_OVERRIDE;
	tresult PLUGIN_API setBusArrangements (SpeakerArrangement* inputs, int32 numIns,
	                                       SpeakerArrangement* outputs,
	                                       int32 numOuts) SMTG_OVERRIDE;

protected:
	//==============================================================================
	template <typename SampleType>
	SampleType processAudioWithSideChain (SampleType** in, SampleType** out, SampleType** aux,
	                                      int32 numChannels, int32 sampleFrames, float gain);
};

//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg
