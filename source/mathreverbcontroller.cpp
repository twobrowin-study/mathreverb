#include "mathreverbcontroller.h"
#include "mathreverbparamids.h"

#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/base/ustring.h"
#include "pluginterfaces/vst/ivstmidicontrollers.h"

#include "base/source/fstring.h"

#include "vstgui/uidescription/delegationcontroller.h"

#include <stdio.h>
#include <math.h>

namespace Steinberg {
namespace Vst {

//------------------------------------------------------------------------
// MathReverbController Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API MathReverbController::initialize (FUnknown* context)
{
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}

	//---VuMeter parameter---
	int32 stepCount = 0;
	ParamValue defaultVal = 0;
	int32 flags = ParameterInfo::kIsReadOnly;
	int32 tag = kVuPPMId;
	parameters.addParameter (STR16 ("VuPPM"), 0, stepCount, defaultVal, flags, tag);

	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MathReverbController::terminate  ()
{
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API MathReverbController::setComponentState (IBStream* state)
{
	// we receive the current state of the component (processor part)
	// we read only the gain and bypass value...
	// if (state)
	// {
	// 	float savedGain = 0.f;
	// 	if (state->read (&savedGain, sizeof (float)) != kResultOk)
	// 	{
	// 		return kResultFalse;
	// 	}
	//
	// #if BYTEORDER == kBigEndian
	// 	SWAP_32 (savedGain)
	// #endif
	// 	setParamNormalized (kGainId, savedGain);
	//
	// 	// jump the GainReduction
	// 	state->seek (sizeof (float), IBStream::kIBSeekCur);
	//
	// 	// read the bypass
	// 	int32 bypassState;
	// 	if (state->read (&bypassState, sizeof (bypassState)) == kResultTrue)
	// 	{
	// 	#if BYTEORDER == kBigEndian
	// 		SWAP_32 (bypassState)
	// 	#endif
	// 		setParamNormalized (kBypassId, bypassState ? 1 : 0);
	// 	}
	// }

	return kResultOk;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API MathReverbController::createView (const char* name)
{
	// someone wants my editor
	if (name && strcmp (name, "editor") == 0)
	{
		VST3Editor* view = new VST3Editor (this, "view", "mathreverb.uidesc");
		return view;
	}
	return 0;
}

//------------------------------------------------------------------------
tresult MathReverbController::receiveText (const char* text)
{
	// received from Component
	// if (text)
	// {
	// 	fprintf (stderr, "[MathReverbController] received: ");
	// 	fprintf (stderr, "%s", text);
	// 	fprintf (stderr, "\n");
	// }
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MathReverbController::setParamNormalized (ParamID tag, ParamValue value)
{
	// called from host to update our parameters state
	tresult result = EditControllerEx1::setParamNormalized (tag, value);
	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API MathReverbController::getParamStringByValue (ParamID tag, ParamValue valueNormalized, String128 string)
{
	return EditControllerEx1::getParamStringByValue (tag, valueNormalized, string);
}

//------------------------------------------------------------------------
tresult PLUGIN_API MathReverbController::getParamValueByString (ParamID tag, TChar* string, ParamValue& valueNormalized)
{
	return EditControllerEx1::getParamValueByString (tag, string, valueNormalized);
}

//------------------------------------------------------------------------
tresult PLUGIN_API MathReverbController::queryInterface (const char* iid, void** obj)
{
	QUERY_INTERFACE (iid, obj, IMidiMapping::iid, IMidiMapping)
	return EditControllerEx1::queryInterface (iid, obj);
}

//------------------------------------------------------------------------
tresult PLUGIN_API MathReverbController::getMidiControllerAssignment (int32 busIndex, int16 /*midiChannel*/,
																 CtrlNumber midiControllerNumber, ParamID& tag)
{
	// we support for the Gain parameter all MIDI Channel but only first bus (there is only one!)
	if (busIndex == 0 && midiControllerNumber == kCtrlVolume)
	{
		// tag = kGainId;
		return kResultTrue;
	}
	return kResultFalse;
}

//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg
