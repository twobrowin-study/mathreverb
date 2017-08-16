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
tresult PLUGIN_API MathReverbController::initialize (FUnknown* context) {
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk) {
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
IPlugView* PLUGIN_API MathReverbController::createView (const char* name) {
	// someone wants my editor
	if (name && strcmp (name, "editor") == 0) {
		VST3Editor* view = new VST3Editor (this, "view", "mathreverb.uidesc");
		return view;
	}
	return 0;
}

//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg
