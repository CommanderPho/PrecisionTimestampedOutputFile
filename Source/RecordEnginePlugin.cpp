#include "RecordEnginePlugin.h"
#include "date/date.h" // For precise timestamp functionality
#include <iostream> // Testing only:

// #include <RecordNode.h>
// #include <RecordEngine.h>


RecordEnginePlugin::RecordEnginePlugin() 
{

}
	
RecordEnginePlugin::~RecordEnginePlugin() 
{

}

String RecordEnginePlugin::getEngineID() const 
{
	return "PHOTIMESTAMPED";
}

void RecordEnginePlugin::setParameter(EngineParameter& parameter)
{

}

std::chrono::system_clock::time_point RecordEnginePlugin::getPreciseFileTime()
{
	// Returns a pointer to a FILETIME structure that contains the current system date and time in UTC format.
	// GetSystemTimePreciseAsFileTime([out] LPFILETIME lpSystemTimeAsFileTime);
	// Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).

	// To convert a FILETIME structure into a time that is easy to display to a user, use the FileTimeToSystemTime function.
	using namespace date;
    using namespace std;
    using namespace std::chrono;

	// microsecondSystemTime: std::chrono::system_clock::time_point
	auto microsecondSystemTime = floor<microseconds>(system_clock::now());
	cout << format("%d-%m-%Y %T", microsecondSystemTime) << '\n'; // prints a string like "29-11-2018 14:45:03.679098"
	return microsecondSystemTime; // return the timestamp
}

void RecordEnginePlugin::openFiles(File rootFolder, int experimentNumber, int recordingNumber)
{
	// called when files should be opened
}

void RecordEnginePlugin::closeFiles()
{
	// called when files should be closed
}

void RecordEnginePlugin::startChannelBlock(bool lastBlock)
{

}

void RecordEnginePlugin:: writeData(int writeChannel, int realChannel, const float* buffer, int size)
{

}

void RecordEnginePlugin::writeSynchronizedData(int writeChannel, 
											   int realChannel, 
											   const float* dataBuffer, 
											   const double* ftsBuffer, 
											   int size)
{

}

void RecordEnginePlugin::endChannelBlock(bool lastBlock)
{

}

void RecordEnginePlugin::writeEvent(int eventChannel, const MidiMessage& event)
{

}

void RecordEnginePlugin::writeTimestampSyncText(uint16 sourceID, uint16 sourceIdx, int64 timestamp, float sourceSampleRate, String text)
{

}

void RecordEnginePlugin::registerProcessor(const GenericProcessor* processor)
{

}

void RecordEnginePlugin::addDataChannel(int index, const DataChannel* chan)
{

}

void RecordEnginePlugin::addEventChannel(int index, const EventChannel* chan)
{

}

void RecordEnginePlugin::registerSpikeSource(const GenericProcessor* processor)
{

}

void RecordEnginePlugin::addSpikeElectrode(int index, const SpikeChannel* elec)
{

}

void RecordEnginePlugin::writeSpike(int electrodeIndex, const SpikeEvent* spike)
{

}

void RecordEnginePlugin::resetChannels()
{

}

void RecordEnginePlugin::updateTimestamps(const Array<int64>& timestamps, int channel)
{

}

void RecordEnginePlugin::setChannelMapping (const Array<int>& channels, 
										    const Array<int>& chanProcessor, 
											const Array<int>& chanOrder, 
											OwnedArray<RecordProcessorInfo>& processors)
{

}

void RecordEnginePlugin::registerRecordNode(RecordNode* node)
{

}

void RecordEnginePlugin::startAcquisition()
{

}

void RecordEnginePlugin::directoryChanged()
{

}

RecordEngineManager* RecordEnginePlugin::getEngineManager()
{
    RecordEngineManager* man = new RecordEngineManager("PHOTIMESTAMPED", "Pho Precise Timestampped",
                                                       &(engineFactory<RecordEnginePlugin>));
    EngineParameter* param;
    param = new EngineParameter(EngineParameter::BOOL, 0, "Test Bool Parameter", true);
    man->addParameter(param);
    return man;
}

