#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"

namespace Steinberg {
namespace Vst {

//------------------------------------------------------------------------
// MathReverb: directly derived from the helper class AudioEffect
//------------------------------------------------------------------------
class MathReverb : public AudioEffect
{
public:
	MathReverb ();
	virtual ~MathReverb (); // do not forget virtual here

	//--- ---------------------------------------------------------------------
	// create function required for Plug-in factory,
	// it will be called to create new instances of this Plug-in
	//--- ---------------------------------------------------------------------
	static FUnknown* createInstance (void* /*context*/) { return (IAudioProcessor*)new MathReverb; }

	//--- ---------------------------------------------------------------------
	// AudioEffect overrides:
	//--- ---------------------------------------------------------------------
	/** Called at first after constructor */
	tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;

	/** Here we go...the process call */
	tresult PLUGIN_API process (ProcessData& data) SMTG_OVERRIDE;

	/** Bus arrangement managing: in this example the 'mathreverb' will be mono for mono input/output and
	 * stereo for other arrangements. */
	tresult PLUGIN_API setBusArrangements (SpeakerArrangement* inputs, int32 numIns,
	                                       SpeakerArrangement* outputs,
	                                       int32 numOuts) SMTG_OVERRIDE;

	/** Asks if a given sample size is supported see \ref SymbolicSampleSizes. */
	tresult PLUGIN_API canProcessSampleSize (int32 symbolicSampleSize) SMTG_OVERRIDE;

//------------------------------------------------------------------------
protected:
	//==============================================================================
	template <typename SampleType>
	SampleType processAudio (SampleType** input, SampleType** output, int32 numChannels,
	                         int32 sampleFrames);

	// our model values
	// float fGain;
	// float fGainReduction;
	float fVuPPMOld;

	// int32 currentProcessMode;
	//
	// bool bHalfGain;
	// bool bBypass;
};

//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg
