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
// GainParameter Declaration
// example of custom parameter (overwriting to and fromString)
//------------------------------------------------------------------------
class GainParameter : public Parameter
{
public:
	GainParameter (int32 flags, int32 id);

	virtual void toString (ParamValue normValue, String128 string) const;
	virtual bool fromString (const TChar* string, ParamValue& normValue) const;
};

//------------------------------------------------------------------------
// GainParameter Implementation
//------------------------------------------------------------------------
GainParameter::GainParameter (int32 flags, int32 id)
{
	Steinberg::UString (info.title, USTRINGSIZE (info.title)).assign (USTRING ("Gain"));
	Steinberg::UString (info.units, USTRINGSIZE (info.units)).assign (USTRING ("dB"));

	info.flags = flags;
	info.id = id;
	info.stepCount = 0;
	info.defaultNormalizedValue = 0.5f;
	info.unitId = kRootUnitId;

	setNormalized (1.f);
}

//------------------------------------------------------------------------
void GainParameter::toString (ParamValue normValue, String128 string) const
{
	char text[32];
	if (normValue > 0.0001)
	{
		sprintf (text, "%.2f", 20 * log10f ((float)normValue));
	}
	else
	{
		strcpy (text, "-oo");
	}

	Steinberg::UString (string, 128).fromAscii (text);
}

//------------------------------------------------------------------------
bool GainParameter::fromString (const TChar* string, ParamValue& normValue) const
{
	String wrapper ((TChar*)string); // don't know buffer size here!
	double tmp = 0.0;
	if (wrapper.scanFloat (tmp))
	{
		// allow only values between -oo and 0dB
		if (tmp > 0.0)
		{
			tmp = -tmp;
		}

		normValue = expf (logf (10.f) * (float)tmp / 20.f);
		return true;
	}
	return false;
}

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

	//--- Create Units-------------
	UnitInfo unitInfo;
	Unit* unit;

	// create root only if you want to use the programListId
/*	unitInfo.id = kRootUnitId;	// always for Root Unit
	unitInfo.parentUnitId = kNoParentUnitId;	// always for Root Unit
	Steinberg::UString (unitInfo.name, USTRINGSIZE (unitInfo.name)).assign (USTRING ("Root"));
	unitInfo.programListId = kNoProgramListId;

	unit = new Unit (unitInfo);
	addUnitInfo (unit);*/

	// create a unit1 for the gain
	unitInfo.id = 1;
	unitInfo.parentUnitId = kRootUnitId;	// attached to the root unit

	Steinberg::UString (unitInfo.name, USTRINGSIZE (unitInfo.name)).assign (USTRING ("Unit1"));

	unitInfo.programListId = kNoProgramListId;

	unit = new Unit (unitInfo);
	addUnit (unit);

	//---Create Parameters------------

	//---Gain parameter--
	GainParameter* gainParam = new GainParameter (ParameterInfo::kCanAutomate, kGainId);
	parameters.addParameter (gainParam);

	gainParam->setUnitID (1);

	//---VuMeter parameter---
	int32 stepCount = 0;
	ParamValue defaultVal = 0;
	int32 flags = ParameterInfo::kIsReadOnly;
	int32 tag = kVuPPMId;
	parameters.addParameter (STR16 ("VuPPM"), 0, stepCount, defaultVal, flags, tag);

	//---Bypass parameter---
	stepCount = 1;
	defaultVal = 0;
	flags = ParameterInfo::kCanAutomate|ParameterInfo::kIsBypass;
	tag = kBypassId;
	parameters.addParameter (STR16 ("Bypass"), 0, stepCount, defaultVal, flags, tag);

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
	if (state)
	{
		float savedGain = 0.f;
		if (state->read (&savedGain, sizeof (float)) != kResultOk)
		{
			return kResultFalse;
		}

	#if BYTEORDER == kBigEndian
		SWAP_32 (savedGain)
	#endif
		setParamNormalized (kGainId, savedGain);

		// jump the GainReduction
		state->seek (sizeof (float), IBStream::kIBSeekCur);

		// read the bypass
		int32 bypassState;
		if (state->read (&bypassState, sizeof (bypassState)) == kResultTrue)
		{
		#if BYTEORDER == kBigEndian
			SWAP_32 (bypassState)
		#endif
			setParamNormalized (kBypassId, bypassState ? 1 : 0);
		}
	}

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
	if (text)
	{
		fprintf (stderr, "[MathReverbController] received: ");
		fprintf (stderr, "%s", text);
		fprintf (stderr, "\n");
	}
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
		tag = kGainId;
		return kResultTrue;
	}
	return kResultFalse;
}

//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg
