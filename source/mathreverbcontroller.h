#pragma once

#include "vstgui/plugin-bindings/vst3editor.h"
#include "public.sdk/source/vst/vsteditcontroller.h"

#include <vector>

namespace Steinberg {
namespace Vst {

//------------------------------------------------------------------------
// MathReverbController
//------------------------------------------------------------------------
class MathReverbController : public EditControllerEx1, public IMidiMapping
{
public:
	//--- ---------------------------------------------------------------------
	// create function required for Plug-in factory,
	// it will be called to create new instances of this controller
	//--- ---------------------------------------------------------------------
	static FUnknown* createInstance (void* /*context*/)
	{
		return (IEditController*)new MathReverbController;
	}

	//---from IPluginBase--------
	tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;
	tresult PLUGIN_API terminate () SMTG_OVERRIDE;

	//---from EditController-----
	tresult PLUGIN_API setComponentState (IBStream* state) SMTG_OVERRIDE;
	IPlugView* PLUGIN_API createView (const char* name) SMTG_OVERRIDE;
	tresult PLUGIN_API setParamNormalized (ParamID tag, ParamValue value) SMTG_OVERRIDE;
	tresult PLUGIN_API getParamStringByValue (ParamID tag, ParamValue valueNormalized,
	                                          String128 string) SMTG_OVERRIDE;
	tresult PLUGIN_API getParamValueByString (ParamID tag, TChar* string,
	                                          ParamValue& valueNormalized) SMTG_OVERRIDE;

	//---from ComponentBase-----
	tresult receiveText (const char* text) SMTG_OVERRIDE;

	//---from IMidiMapping-----------------
	tresult PLUGIN_API getMidiControllerAssignment (int32 busIndex, int16 channel,
	                                                CtrlNumber midiControllerNumber,
	                                                ParamID& tag) SMTG_OVERRIDE;

	DELEGATE_REFCOUNT (EditController)
	tresult PLUGIN_API queryInterface (const char* iid, void** obj) SMTG_OVERRIDE;
};

//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg
