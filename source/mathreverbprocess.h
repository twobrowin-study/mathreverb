#pragma once

namespace Steinberg {
namespace Vst {

//------------------------------------------------------------------------
template <typename SampleType>
SampleType MAthreverb::processAudio (SampleType** in, SampleType** out, int32 numChannels,
                                     int32 sampleFrames, float gain)
{
	SampleType vuPPM = 0;

	// in real Plug-in it would be better to do dezippering to avoid jump (click) in gain value
	for (int32 i = 0; i < numChannels; i++)
	{
		int32 samples = sampleFrames;
		SampleType* ptrIn = (SampleType*)in[i];
		SampleType* ptrOut = (SampleType*)out[i];
		SampleType tmp;
		while (--samples >= 0)
		{
			// apply gain
			tmp = (*ptrIn++) * gain;
			(*ptrOut++) = tmp;

			// check only positive values
			if (tmp > vuPPM)
			{
				vuPPM = tmp;
			}
		}
	}
	return vuPPM;
}

} // Vst
} // Steinberg
