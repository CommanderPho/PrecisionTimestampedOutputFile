//This prevents include loops. We recommend changing the macro to a name suitable for your plugin
#ifndef PhoDatetimeTimestampHelper_H_DEFINED
#define PhoDatetimeTimestampHelper_H_DEFINED
// PhoDatetimeTimestampHelper.h

#include <chrono>
#include <JuceHeader.h>
//class String;

//namespace must be an unique name for your plugin
namespace PhoDatetimeTimestampHelperSpace
{
	/** Custom Methods: */
	std::chrono::system_clock::time_point getPreciseFileTime();

	String getPreciseFileTimeString();

} // end namespace


#endif
