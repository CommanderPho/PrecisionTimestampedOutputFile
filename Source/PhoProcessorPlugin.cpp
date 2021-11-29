#include "PhoProcessorPlugin.h"
#include "PhoDatetimeTimestampHelper.h"
#include "PhoTimesyncFileHelper.h"

using namespace ProcessorPluginSpace;

#define DEBUGLOGGING 1
// #define DRYRUN 1
#define CUSTOMFILE 1

//Change all names for the relevant ones, including "Processor Name"
PhoProcessorPlugin::PhoProcessorPlugin() : GenericProcessor("PhoStartTimestamp Processor"), isProcessing(false), isRecording(false), hasRecorded(false), needsWriteToCustomTimstampSyncFile(false), timestamp(-1), recordingStartTime(std::chrono::system_clock::time_point())
{
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::PhoProcessorPlugin(...)");
	#endif
}

PhoProcessorPlugin::~PhoProcessorPlugin()
{
	#ifdef CUSTOMFILE
		//TODO: this obviously shouldn't be here for efficiency reasons
		this->writeCustomTimestampFileIfNeeded();
	#endif
}

void PhoProcessorPlugin::writeCustomTimestampFileIfNeeded()
{
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::writeCustomTimestampFileIfNeeded(...)");
	#endif
	// Called whenever a new data array is provided:
	if (needsWriteToCustomTimstampSyncFile) {
		#ifdef DRYRUN
			std::cout << "PhoProcessorPlugin::writeCustomTimestampFileIfNeeded(...): not writing file out because this is a dry-run, change #define DRYRUN 1 line." << std::endl;
			#ifdef DEBUGLOGGING
				CoreServices::sendStatusMessage("\t PhoProcessorPlugin::writeCustomTimestampFileIfNeeded(...): not writing file out because this is a dry-run, change #define DRYRUN 1 line.");
			#endif

			bool wasWritingSuccess = true;
		#else
			bool wasWritingSuccess = PhoTimesyncFileHelperSpace::writeOutCustomFile(recordingStartTime, false, true);
			
		#endif
		if (wasWritingSuccess) {
			needsWriteToCustomTimstampSyncFile = false;
			#ifdef DEBUGLOGGING
				CoreServices::sendStatusMessage("\t PhoProcessorPlugin::writeCustomTimestampFileIfNeeded(...): Writing success!");
			#endif

		}
		else {
			// ERROR
			needsWriteToCustomTimstampSyncFile = false;
			#ifdef DEBUGLOGGING
				std::cout << "Couldn't succeed in writing out file, aborting custom file write anyway!" << std::endl;
				CoreServices::sendStatusMessage("\t PhoProcessorPlugin::writeCustomTimestampFileIfNeeded(...): Couldn't succeed in writing out file, aborting custom file write anyway!");
			#endif
		}
	}
}


void PhoProcessorPlugin::process(AudioSampleBuffer& buffer)
{
	/**
	 * @brief THIS IS CALLED OVER AND OVER during recording and playback!!!
	 * 
	If the processor needs to handle events, this method must be called onyl once per process call
	If spike processing is also needing, set the argument to true
	*/
	// #ifdef DEBUGLOGGING
	// 	CoreServices::sendStatusMessage("PhoProcessorPlugin::process(...)");
	// #endif

	isProcessing = true;

	// #ifdef CUSTOMFILE
	// 	//TODO: this obviously shouldn't be here for efficiency reasons
	// 	this->writeCustomTimestampFileIfNeeded();
	// #endif


	//checkForEvents(false);
	// int numChannels = getNumOutputs();

	// for (int chan = 0; chan < numChannels; chan++)
	// {
	// 	int numSamples = getNumSamples(chan);
	// 	int64 timestamp = getTimestamp(chan);

	// 	//Do whatever processing needed
	// }
	
}



// called by GenericProcessor::update()
void PhoProcessorPlugin::updateSettings()
{
	// PhoDatetimeTimestampHelperSpace::getPreciseFileTimeString();
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::updateSettings(...)");
	#endif
	// Called whenever any part of the processing chain is updated:
	// if (needsWriteToCustomTimstampSyncFile) {
	// 	bool wasWritingSuccess = PhoTimesyncFileHelperSpace::writeOutCustomFile(recordingStartTime);
	// 	if (wasWritingSuccess) {
	// 		needsWriteToCustomTimstampSyncFile = false;
	// 	}
	// 	else {
	// 		// ERROR
	// 		needsWriteToCustomTimstampSyncFile = false;
	// 		std::cout << "Couldn't succeed in writing out file, aborting custom file write anyway!" << std::endl;
	// 	}
	// }

}

// GenericProcessor Parameter Methods:
void PhoProcessorPlugin::saveCustomParametersToXml(XmlElement *parentElement)
{
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::saveCustomParametersToXml(...)");
	#endif


	// #ifdef CUSTOMFILE
	// 	//TODO: this obviously shouldn't be here for efficiency reasons
	// 	this->writeCustomTimestampFileIfNeeded();
	// #endif


	XmlElement* mainNode = parentElement->createNewChildElement("PhoStartTimestampPlugin");

   	// Create the timestamp child element:
   	XmlElement* recordingStartTimestampNode = new XmlElement("RecordingStartTimestamp");
	recordingStartTimestampNode->setAttribute("test", "test_id");
	// if (recordingStartTime != nullptr) {
	if (hasRecorded) {
		String formattedRecordingStartTimeString = PhoDatetimeTimestampHelperSpace::formatPreciseFileTimeAsString(recordingStartTime);
		recordingStartTimestampNode->setAttribute("startTime", formattedRecordingStartTimeString);
	}
	else {
		recordingStartTimestampNode->setAttribute("startTime", "");
	}

	// if (isRecording) {

	// }
	// else {
	// 	// If it has never recorded before, don't include the output
	// }
	mainNode->addChildElement(recordingStartTimestampNode);
}

void PhoProcessorPlugin::loadCustomParametersFromXml()
{
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::loadCustomParametersFromXml(...)");
	#endif
   if (parametersAsXml != nullptr)
   {
       forEachXmlChildElement (*parametersAsXml, mainNode)
       {
           if (mainNode->hasTagName("PhoStartTimestampPlugin"))
           {
               forEachXmlChildElement(*mainNode, aRecordingStartTimestampNode)
               {
                //    int id = aRecordingStartTimestampNode->getIntAttribute("id");
                   String test = aRecordingStartTimestampNode->getStringAttribute("test");
                //    double phase1 = aRecordingStartTimestampNode->getDoubleAttribute("phase1");
                //    int link21 = aRecordingStartTimestampNode->getIntAttribute("link2trigger1");
                //    m_test[id] = test;
                //    m_phase1Duration[id] = phase1;
                //    m_phase2Duration[id] = phase2;
               } // end forEachXmlChildElement
           } // end if (mainNode->hasTagName(...))
       } // end forEachXmlChildElement
   } // end if (parametersAsXml != nullptr)
} // end function loadCustomParametersFromXml()


// called by GenericProcessor::setRecording()
void PhoProcessorPlugin::startRecording()
{
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::startRecording(...)");
	#endif
	isRecording = true;
	recordingStartTime = PhoDatetimeTimestampHelperSpace::getPreciseFileTime();
	hasRecorded = true;
	needsWriteToCustomTimstampSyncFile = true;

	// #ifdef CUSTOMFILE
	// 	//TODO: this obviously shouldn't be here for efficiency reasons
	// 	this->writeCustomTimestampFileIfNeeded();
	// #endif

}

// called by GenericProcessor::setRecording()
void PhoProcessorPlugin::stopRecording()
{
	//TODO: this never seems to be called!
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::stopRecording(...)");
	#endif
	isRecording = false;

	#ifdef CUSTOMFILE
		//TODO: this obviously shouldn't be here for efficiency reasons
		this->writeCustomTimestampFileIfNeeded();
	#endif

}
