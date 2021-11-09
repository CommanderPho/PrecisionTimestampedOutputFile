#include "PhoProcessorPlugin.h"

using namespace ProcessorPluginSpace;

//Change all names for the relevant ones, including "Processor Name"
PhoProcessorPlugin::PhoProcessorPlugin() : GenericProcessor("Pho StartTimestamp Processor")
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

}

// GenericProcessor Parameter Methods:
void PhoProcessorPlugin::saveCustomParametersToXml(XmlElement *parentElement)
{
	XmlElement* mainNode = parentElement->createNewChildElement("PhoProcessorPlugin");

   	// Create the timestamp child element:
   	XmlElement* recordingStartTimestampNode = new XmlElement("RecordingStartTimestamp");
	recordingStartTimestampNode->setAttribute("test", "test_id");

	mainNode->addChildElement(recordingStartTimestampNode);
}

void PhoProcessorPlugin::loadCustomParametersFromXml()
{
   if (parametersAsXml != nullptr)
   {
       forEachXmlChildElement (*parametersAsXml, mainNode)
       {
           if (mainNode->hasTagName("PhoProcessorPlugin"))
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
}

// called by GenericProcessor::setRecording()
void PhoProcessorPlugin::stopRecording()
{
	isRecording = false;

}