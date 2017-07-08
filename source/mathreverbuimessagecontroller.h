#pragma once

#include "vstgui/lib/iviewlistener.h"
#include "vstgui/uidescription/icontroller.h"

//------------------------------------------------------------------------
namespace Steinberg {
namespace Vst {

//------------------------------------------------------------------------
// MathReverbUIMessageController
//------------------------------------------------------------------------
template <typename ControllerType>
class MathReverbUIMessageController : public VSTGUI::IController, public VSTGUI::IViewListenerAdapter
{
public:
	enum Tags
	{
		kSendMessageTag = 1000
	};

	MathReverbUIMessageController (ControllerType* mathreverbController) : mathreverbController (mathreverbController), textEdit (nullptr)
	{
	}
	~MathReverbUIMessageController ()
	{
		viewWillDelete (textEdit);
		mathreverbController->removeUIMessageController (this);
	}

	void setMessageText (String128 msgText)
	{
		if (!textEdit)
			return;
		String str (msgText);
		str.toMultiByte (kCP_Utf8);
		textEdit->setText (str.text8 ());
	}

private:
	typedef VSTGUI::CControl CControl;
	typedef VSTGUI::CView CView;
	typedef VSTGUI::CTextEdit CTextEdit;
	typedef VSTGUI::UTF8String UTF8String;

	//--- from IControlListener ----------------------
	void valueChanged (CControl* /*pControl*/) VSTGUI_OVERRIDE_VMETHOD {}
	void controlBeginEdit (CControl* /*pControl*/) VSTGUI_OVERRIDE_VMETHOD {}
	void controlEndEdit (CControl* pControl) VSTGUI_OVERRIDE_VMETHOD
	{
		if (pControl->getTag () == kSendMessageTag)
		{
			if (pControl->getValueNormalized () > 0.5f)
			{
				mathreverbController->sendTextMessage (textEdit->getText ().get ());
				pControl->setValue (0.f);
				pControl->invalid ();

				//---send a binary message
				if (IPtr<IMessage> message = owned (mathreverbController->allocateMessage ()))
				{
					message->setMessageID ("BinaryMessage");
					uint32 size = 100;
					char8 data[100];
					memset (data, 0, size * sizeof (char));
					// fill my data with dummy stuff
					for (uint32 i = 0; i < size; i++)
						data[i] = i;
					message->getAttributes ()->setBinary ("MyData", data, size);
					mathreverbController->sendMessage (message);
				}
			}
		}
	}
	//--- from IControlListener ----------------------
	//--- is called when a view is created -----
	CView* verifyView (CView* view, const UIAttributes& /*attributes*/,
	                   const IUIDescription* /*description*/) VSTGUI_OVERRIDE_VMETHOD
	{
		if (CTextEdit* te = dynamic_cast<CTextEdit*> (view))
		{
			// this allows us to keep a pointer of the text edit view
			textEdit = te;

			// add this as listener in order to get viewWillDelete and viewLostFocus calls
			textEdit->registerViewListener (this);

			// initialize it content
			String str (mathreverbController->getDefaultMessageText ());
			str.toMultiByte (kCP_Utf8);
			textEdit->setText (str.text8 ());
		}
		return view;
	}
	//--- from IViewListenerAdapter ----------------------
	//--- is called when a view will be deleted: the editor is closed -----
	void viewWillDelete (CView* view) VSTGUI_OVERRIDE_VMETHOD
	{
		if (dynamic_cast<CTextEdit*> (view) == textEdit)
		{
			textEdit->unregisterViewListener (this);
			textEdit = nullptr;
		}
	}
	//--- is called when the view is loosing the focus -----------------
	void viewLostFocus (CView* view) VSTGUI_OVERRIDE_VMETHOD
	{
		if (dynamic_cast<CTextEdit*> (view) == textEdit)
		{
			// save the last content of the text edit view
			const UTF8String& text = textEdit->getText ();
			String128 messageText;
			String str;
			str.fromUTF8 (text.get ());
			str.copyTo (messageText, 128);
			mathreverbController->setDefaultMessageText (messageText);
		}
	}
	ControllerType* mathreverbController;
	CTextEdit* textEdit;
};

//------------------------------------------------------------------------
} // Vst
} // Steinberg
