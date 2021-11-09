#include "PhoDatetimeTimestampHelper.h"
#include "date/date.h" // For precise timestamp functionality
#include <iostream> // Testing only:


//namespace must be an unique name for your plugin
namespace PhoDatetimeTimestampHelperSpace
{
	/** Custom Methods: */
	std::chrono::system_clock::time_point getPreciseFileTime()
	{
		using namespace date;
		using namespace std;
		using namespace std::chrono;
		// microsecondSystemTime: std::chrono::system_clock::time_point
		return floor<microseconds>(system_clock::now());
	} // end function getPreciseFileTime()

	String getPreciseFileTimeString()
	{
		return date::format("%Y-%m-%d_%T", getPreciseFileTime());
	} // end function getPreciseFileTimeString()



} // end namespace
