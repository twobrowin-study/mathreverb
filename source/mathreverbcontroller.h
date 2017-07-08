#pragma once

#include "vstgui/plugin-bindings/vst3editor.h"
#include "public.sdk/source/vst/vsteditcontroller.h"

#include <vector>

namespace Steinberg {
namespace Vst {

template <typename T>
class MathReverbUIMessageController;

//------------------------------------------------------------------------
// MathReverbController
//------------------------------------------------------------------------
class MathReverbController : public EditControllerEx1, public IMidiMapping, public VST3EditorDelegate
{
public:
	typedef MathReverbUIMessageController<MathReverbController> UIMessageController;
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
	tresult PLUGIN_API setState (IBStream* state) SMTG_OVERRIDE;
	tresult PLUGIN_API getState (IBStream* state) SMTG_OVERRIDE;
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

	//---from VST3EditorDelegate-----------
	IController* createSubController (UTF8StringPtr name, const IUIDescription* description,
	                                  VST3Editor* editor) SMTG_OVERRIDE;

	DELEGATE_REFCOUNT (EditController)
	tresult PLUGIN_API queryInterface (const char* iid, void** obj) SMTG_OVERRIDE;

	//---Internal functions-------
	void addUIMessageController (UIMessageController* controller);
	void removeUIMessageController (UIMessageController* controller);

	void setDefaultMessageText (String128 text);
	TChar* getDefaultMessageText ();
//------------------------------------------------------------------------

private:
	typedef std::vector<UIMessageController*> UIMessageControllerList;
	UIMessageControllerList uiMessageControllers;

	String128 defaultMessageText;
};

//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg
