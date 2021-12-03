#include "PhoProcessorPlugin.h"
#include "PhoDatetimeTimestampHelper.h"
#include "PhoTimesyncFileHelper.h"

using namespace ProcessorPluginSpace;

// #define DEBUGLOGGING 1
// #define DRYRUN 1
#define CUSTOMFILE 1

//Change all names for the relevant ones, including "Processor Name"
PhoProcessorPlugin::PhoProcessorPlugin() : GenericProcessor("PhoStartTimestamp Processor"), curr_experiment_number(-1), isProcessing(false), isRecording(false), hasRecorded(false), needsWriteToCustomTimstampSyncFile(false), recordingStartSoftwareTimestamp(-1), recordingStartTime(std::chrono::system_clock::time_point()), pluginInitializationTime(std::chrono::system_clock::now())
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
				CoreServices::sendStatusMessage("\t PhoProcessorPlugin::writeCustomTimestampFileIfNeeded(...): ERROR: Couldn't succeed in writing out file, aborting custom file write anyway!");
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
	isProcessing = true;
}



// called by GenericProcessor::update()
void PhoProcessorPlugin::updateSettings()
{
	// Called whenever any part of the processing chain is updated:
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::updateSettings(...)");
	#endif
	this->curr_experiment_number = CoreServices::RecordNode::getExperimentNumber();
	// >curr_recording_thread_status = CoreServices::RecordNode::curr_recording_thread_status();
	#ifdef CUSTOMFILE
		this->writeCustomTimestampFileIfNeeded();
	#endif
}

// GenericProcessor Parameter Methods:
void PhoProcessorPlugin::saveCustomParametersToXml(XmlElement *parentElement)
{
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::saveCustomParametersToXml(...)");
	#endif

	#ifdef CUSTOMFILE
		this->writeCustomTimestampFileIfNeeded();
	#endif
	XmlElement* mainNode = parentElement->createNewChildElement("PhoStartTimestampPlugin");
   	// Create the timestamp child element:
   	XmlElement* recordingStartTimestampNode = new XmlElement("RecordingStartTimestamp");
	// recordingStartTimestampNode->setAttribute("test", "test_id");
	if (hasRecorded) {
		String formattedRecordingStartTimeString = PhoDatetimeTimestampHelperSpace::formatPreciseFileTimeAsString(recordingStartTime);
		recordingStartTimestampNode->setAttribute("startTime", formattedRecordingStartTimeString);
		recordingStartTimestampNode->setAttribute("softwareStartTime", String(this->recordingStartSoftwareTimestamp));
	}
	else {
		recordingStartTimestampNode->setAttribute("startTime", "");
		recordingStartTimestampNode->setAttribute("softwareStartTime", "");
	}
	mainNode->addChildElement(recordingStartTimestampNode);
}

void PhoProcessorPlugin::loadCustomParametersFromXml()
{
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::loadCustomParametersFromXml(...)");
	#endif
	this->curr_experiment_number = CoreServices::RecordNode::getExperimentNumber();
	// this->curr_recording_thread_status = CoreServices::RecordNode::curr_recording_thread_status();
} // end function loadCustomParametersFromXml()


// called by GenericProcessor::setRecording()
void PhoProcessorPlugin::startRecording()
{
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::startRecording(...)");
	#endif
	isRecording = true;
	this->recordingStartTime = PhoDatetimeTimestampHelperSpace::getPreciseFileTime();
	this->recordingStartSoftwareTimestamp = CoreServices::getGlobalTimestamp();
	this->curr_experiment_number = CoreServices::RecordNode::getExperimentNumber();
	// this->curr_recording_thread_status = CoreServices::RecordNode::curr_recording_thread_status();
	hasRecorded = true;
	needsWriteToCustomTimstampSyncFile = true;

	#ifdef CUSTOMFILE
		//TODO: this obviously shouldn't be here for efficiency reasons
		this->writeCustomTimestampFileIfNeeded();
	#endif

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
