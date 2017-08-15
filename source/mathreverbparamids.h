#pragma once

enum
{
	/** parameter ID */
	kGainId,	///< for the gain value (is automatable)
	kVuPPMId = 0,		///< for the Vu value return to host (ReadOnly parameter for our UI)
	kBypassId		///< Bypass value (we will handle the bypass process) (is automatable)
};
