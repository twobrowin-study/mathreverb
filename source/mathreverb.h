MathReverb#pragma once

// must always come first
#include "public.sdk/source/vst/vstsinglecomponenteffect.h"
//------------------------------------------------------------------------

#include "public.sdk/source/vst/vstguieditor.h"
#include "pluginterfaces/vst/ivstcontextmenu.h"
#include "pluginterfaces/vst/ivstplugview.h"

#include "vstgui/plugin-bindings/vst3editor.h"

namespace Steinberg {
namespace Vst {

template <typename T>
class MathReverbUIMessageController;

//------------------------------------------------------------------------
// MathReverb as combined processor and controller
//------------------------------------------------------------------------
class MathReverb : public SingleComponentEffect, public VST3EditorDelegate
{
public:
//------------------------------------------------------------------------
	typedef MathReverbUIMessageController<MathReverb> UIMessageController;

	MathReverb ();

	static FUnknown* createInstance (void* context) { return (IAudioProcessor*)new AGainSimple; }

	tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;
	tresult PLUGIN_API terminate () SMTG_OVERRIDE;
	tresult PLUGIN_API setActive (TBool state) SMTG_OVERRIDE;
	tresult PLUGIN_API process (ProcessData& data) SMTG_OVERRIDE;
	tresult PLUGIN_API setState (IBStream* state) SMTG_OVERRIDE;
	tresult PLUGIN_API getState (IBStream* state) SMTG_OVERRIDE;
	tresult PLUGIN_API setupProcessing (ProcessSetup& newSetup) SMTG_OVERRIDE;
	tresult PLUGIN_API setBusArrangements (SpeakerArrangement* inputs, int32 numIns,
	                                       SpeakerArrangement* outputs,
	                                       int32 numOuts) SMTG_OVERRIDE;

	IPlugView* PLUGIN_API createView (const char* name) SMTG_OVERRIDE;
	tresult PLUGIN_API setEditorState (IBStream* state) SMTG_OVERRIDE;
	tresult PLUGIN_API getEditorState (IBStream* state) SMTG_OVERRIDE;
	tresult PLUGIN_API setParamNormalized (ParamID tag, ParamValue value) SMTG_OVERRIDE;
	tresult PLUGIN_API getParamStringByValue (ParamID tag, ParamValue valueNormalized,
	                                          String128 string) SMTG_OVERRIDE;
	tresult PLUGIN_API getParamValueByString (ParamID tag, TChar* string,
	                                          ParamValue& valueNormalized) SMTG_OVERRIDE;

	//---from VST3EditorDelegate-----------
	IController* createSubController (UTF8StringPtr name, const IUIDescription* description,
	                                  VST3Editor* editor) SMTG_OVERRIDE;

	//---Internal functions-------
	void addUIMessageController (UIMessageController* controller);
	void removeUIMessageController (UIMessageController* controller);
	void setDefaultMessageText (String128 text);
	TChar* getDefaultMessageText ();

//------------------------------------------------------------------------
private:
	// our model values
	float fGain;
	float fGainReduction;
	float fVuPPMOld;

	int32 currentProcessMode;

	bool bHalfGain;
	bool bBypass;

	typedef std::vector<UIMessageController*> UIMessageControllerList;
	UIMessageControllerList uiMessageControllers;

	String128 defaultMessageText;
};

//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg
