#include "PhoProcessorPlugin.h"
#include "PhoDatetimeTimestampHelper.h"

using namespace ProcessorPluginSpace;

//Change all names for the relevant ones, including "Processor Name"
PhoProcessorPlugin::PhoProcessorPlugin() : GenericProcessor("PhoStartTimestamp Processor")
{

}

PhoProcessorPlugin::~PhoProcessorPlugin()
{

}

void PhoProcessorPlugin::process(AudioSampleBuffer& buffer)
{
	/** 
	If the processor needs to handle events, this method must be called onyl once per process call
	If spike processing is also needing, set the argument to true
	*/
	isProcessing = true;

	//checkForEvents(false);
	int numChannels = getNumOutputs();

	for (int chan = 0; chan < numChannels; chan++)
	{
		int numSamples = getNumSamples(chan);
		int64 timestamp = getTimestamp(chan);

		//Do whatever processing needed
	}
	 
}



// called by GenericProcessor::update()
void PhoProcessorPlugin::updateSettings()
{
	// PhoDatetimeTimestampHelperSpace::getPreciseFileTimeString();
}

// GenericProcessor Parameter Methods:
void PhoProcessorPlugin::saveCustomParametersToXml(XmlElement *parentElement)
{
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
	isRecording = true;
	recordingStartTime = PhoDatetimeTimestampHelperSpace::getPreciseFileTime();
	hasRecorded = true;
}

// called by GenericProcessor::setRecording()
void PhoProcessorPlugin::stopRecording()
{
	isRecording = false;

}
