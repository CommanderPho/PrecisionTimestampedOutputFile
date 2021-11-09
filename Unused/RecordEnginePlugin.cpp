#include "RecordEnginePlugin.h"
#include "date/date.h" // For precise timestamp functionality
#include <iostream> // Testing only:

// #include <RecordNode.h>
// #include <RecordEngine.h>


RecordEnginePlugin::RecordEnginePlugin() 
{
	LOGDD("RecordEnginePlugin Initializer");
	CoreServices::sendStatusMessage("RecordEnginePlugin Initializer");
}
	
RecordEnginePlugin::~RecordEnginePlugin() 
{
	LOGDD("RecordEnginePlugin Deinitializer");
}

String RecordEnginePlugin::getEngineID() const 
{
	return "PHOTIMESTAMPED";
}

void RecordEnginePlugin::setParameter(EngineParameter& parameter)
{

}

void RecordEnginePlugin::openFiles(File rootFolder, int experimentNumber, int recordingNumber)
{
	// called when files should be opened
	LOGDD("RecordEnginePlugin::openFiles()");
	auto microsecondSystemTime = getPreciseFileTime();
	buildTimestampOutputFile(rootFolder, experimentNumber, recordingNumber);
	writeTimestampOutputText(0, microsecondSystemTime, "START");
}

void RecordEnginePlugin::closeFiles()
{
	// called when files should be closed
	LOGDD("RecordEnginePlugin::closeFiles()");
	resetChannels();
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
//	int64 ts = spike->getTimestamp();
//	rec->timestampFile->writeData(&ts, sizeof(int64));
}

void RecordEnginePlugin::resetChannels()
{
	LOGDD("RecordEnginePlugin::resetChannels()");
	m_outputTextFile = nullptr;
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
	LOGDD("RecordEnginePlugin::startAcquisition()");
	CoreServices::sendStatusMessage("RecordEnginePlugin::startAcquisition()");
}

void RecordEnginePlugin::directoryChanged()
{
	LOGDD("RecordEnginePlugin::directoryChanged()");
	CoreServices::sendStatusMessage("RecordEnginePlugin::directoryChanged()");
	std::chrono::system_clock::time_point currTime = getPreciseFileTime();
}

RecordEngineManager* RecordEnginePlugin::getEngineManager()
{
	LOGDD("RecordEnginePlugin::getEngineManager()");
    RecordEngineManager* man = new RecordEngineManager("PHOTIMESTAMPED", "Pho Precise Timestampped",
                                                       &(engineFactory<RecordEnginePlugin>));
    EngineParameter* param;
    param = new EngineParameter(EngineParameter::BOOL, 0, "Test Bool Parameter", true);
    man->addParameter(param);
    return man;
}

// GenericProcessor Parameter Methods:
void RecordEnginePlugin::saveCustomParametersToXml(XmlElement *parentElement)
{
//    XmlElement* mainNode = parentElement->createNewChildElement("RecordEnginePlugin");
//    for (int i=0; i<PULSEPALCHANNELS; i++)
//    {
//        XmlElement* chan = new XmlElement(String("Channel_")+=String(i+1));
//        chan->setAttribute("id", i);
//        chan->setAttribute("biphasic", m_isBiphasic[i]);
//        chan->setAttribute("phase1", m_phase1Duration[i]);
//        chan->setAttribute("phase2", m_phase1Duration[i]);
//        chan->setAttribute("interphase", m_interPhaseInterval[i]);
//        chan->setAttribute("voltage1", m_phase1Voltage[i]);
//        chan->setAttribute("voltage2", m_phase2Voltage[i]);
//        chan->setAttribute("restingvoltage", m_restingVoltage[i]);
//        chan->setAttribute("interpulse", m_interPulseInterval[i]);
//        chan->setAttribute("burstduration", m_burstDuration[i]);
//        chan->setAttribute("interburst", m_interBurstInterval[i]);
//        chan->setAttribute("trainduration", m_trainDuration[i]);
//        chan->setAttribute("traindelay", m_trainDelay[i]);
//        chan->setAttribute("link2trigger1", m_linkTriggerChannel1[i]);
//        chan->setAttribute("link2trigger2", m_linkTriggerChannel2[i]);
//        chan->setAttribute("triggermode", m_triggerMode[i]);
//		chan->setAttribute("continuous", m_continuous[i]);
//        mainNode->addChildElement(chan);
//    }
}

void RecordEnginePlugin::loadCustomParametersFromXml()
{
//    if (parametersAsXml != nullptr)
//    {
//        forEachXmlChildElement (*parametersAsXml, mainNode)
//        {
//            if (mainNode->hasTagName ("RecordEnginePlugin"))
//            {
//                forEachXmlChildElement(*mainNode, chan)
//                {
//                    int id = chan->getIntAttribute("id");
//                    int biphasic = chan->getIntAttribute("biphasic");
//                    double phase1 = chan->getDoubleAttribute("phase1");
//                    double phase2 = chan->getDoubleAttribute("phase2");
//                    double interphase = chan->getDoubleAttribute("interphase");
//                    double voltage1 = chan->getDoubleAttribute("voltage1");
//                    double voltage2 = chan->getDoubleAttribute("voltage2");
//                    double resting = chan->getDoubleAttribute("restingvoltage");
//                    double interpulse = chan->getDoubleAttribute("interpulse");
//                    double burst = chan->getDoubleAttribute("burstduration");
//                    double interburst = chan->getDoubleAttribute("interburst");
//                    double trainduration = chan->getDoubleAttribute("trainduration");
//                    double traindelay = chan->getDoubleAttribute("traindelay");
//                    int link21 = chan->getIntAttribute("link2trigger1");
//                    int link22 = chan->getIntAttribute("link2trigger2");
//                    int trigger = chan->getIntAttribute("triggermode");
//					int contd = chan->getIntAttribute("continuous");
//                    m_isBiphasic[id] = biphasic;
//                    m_phase1Duration[id] = phase1;
//                    m_phase2Duration[id] = phase2;
//                    m_interPhaseInterval[id] = interphase;
//                    m_phase1Voltage[id] = voltage1;
//                    m_phase2Voltage[id] = voltage2;
//                    m_restingVoltage[id] = resting;
//                    m_interPulseInterval[id] = interpulse;
//                    m_burstDuration[id] = burst;
//                    m_interBurstInterval[id] = interburst;
//                    m_trainDuration[id] = trainduration;
//                    m_trainDelay[id] = traindelay;
//                    m_linkTriggerChannel1[id] = link21;
//                    m_linkTriggerChannel2[id] = link22;
//                    m_triggerMode[id] = trigger;
//					m_continuous[id] = contd;
//                }
//            }
//        }
//    }
}



/* Usage:
	auto microsecondSystemTime = getPreciseFileTime();
	buildTimestampOutputFile(File rootFolder, int experimentNumber, int recordingNumber);
	writeTimestampOutputText(int64 softwareTimestamp, microsecondSystemTime, "START");
 */

std::chrono::system_clock::time_point RecordEnginePlugin::getPreciseFileTime()
{
	// Returns a pointer to a FILETIME structure that contains the current system date and time in UTC format.
	// GetSystemTimePreciseAsFileTime([out] LPFILETIME lpSystemTimeAsFileTime);
	// Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).

	// To convert a FILETIME structure into a time that is easy to display to a user, use the FileTimeToSystemTime function.
	using namespace date;
    using namespace std;
    using namespace std::chrono;

	LOGDD("Got precise system time");
	// microsecondSystemTime: std::chrono::system_clock::time_point
	auto microsecondSystemTime = floor<microseconds>(system_clock::now());
	// auto microsecondSystemTimeFormattedString = format("%d-%m-%Y %T", microsecondSystemTime);
	auto microsecondSystemTimeFormattedString = format("%Y-%m-%d_%T", microsecondSystemTime);

	cout << microsecondSystemTimeFormattedString << '\n'; // prints a string like "29-11-2018 14:45:03.679098"
	LOGDD("precise system time: ", microsecondSystemTimeFormattedString);
	CoreServices::sendStatusMessage(microsecondSystemTimeFormattedString);

	return microsecondSystemTime; // return the timestamp
}


void RecordEnginePlugin::buildTimestampOutputFile(File rootFolder, int experimentNumber, int recordingNumber)
{
	String basepath = rootFolder.getFullPathName() + rootFolder.separatorString + "experiment" + String(experimentNumber) + File::separatorString + "recording" + String(recordingNumber + 1) + File::separatorString;

	File outputFile = File(basepath + "RecordingStartSystemDatetime.csv");
    Result res = outputFile.create();
    if (res.failed())
    {
        std::cerr << "Error creating sync text file:" << res.getErrorMessage() << std::endl;
    }
    else
    {
        m_outputTextFile = outputFile.createOutputStream();
		m_outputTextFile->writeText("softwareTimestamp, microsecondSystemTimeFormattedString, textDescription\n", false, false); // Write the header line
    }
}

void RecordEnginePlugin::writeTimestampOutputText(int64 softwareTimestamp, std::chrono::system_clock::time_point systemDatetime, String text)
{
	if (!m_outputTextFile)
		return;

	auto microsecondSystemTimeFormattedString = date::format("%Y-%m-%d_%T", systemDatetime);
//	m_outputTextFile->writeData(&softwareTimestamp, sizeof(int64));
	m_outputTextFile->writeText(String(softwareTimestamp) + ", " + microsecondSystemTimeFormattedString + ", " + text + "\n", false, false);
}


