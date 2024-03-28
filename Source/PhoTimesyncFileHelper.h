//This prevents include loops. We recommend changing the macro to a name suitable for your plugin
#ifndef PhoTimesyncFileHelper_H_DEFINED
#define PhoTimesyncFileHelper_H_DEFINED
// PhoTimesyncFileHelper.h

#include <chrono>
#include <iostream>
// #include <string>
#include <JuceHeader.h>

//class String;

//namespace must be an unique name for your plugin
namespace PhoTimesyncFileHelperSpace
{
/** Custom Methods: */
// std::chrono::system_clock::time_point getPreciseFileTime();
// String formatPreciseFileTimeAsString(std::chrono::system_clock::time_point aTimepoint);
// String getPreciseFileTimeString();

// PhoTimesyncFileHelperSpace::PhoTimesyncFileHelper::writeOutCustomFile(recordingStartTime)
bool writeOutCustomFile(std::chrono::system_clock::time_point recordingStartSavedTimestamp, bool is_dry_run, bool enable_debug_printing) {
	// Note that this destDirectory finds a subfolder!
	// const File destDirectory (File::getCurrentWorkingDirectory()
	// 							.getChildFile (String ("DestDirName").unquoted()));


	// const File destDirectory (File::getCurrentWorkingDirectory());
	const File destDirectory (CoreServices::getRecordingParentDirectory());
	// const File destDirectory (CoreServices::getRecordingPath());
	// const File destDirectory (CoreServices::RecordNode::getRecordingPath());
	
	int curr_experiment_number = CoreServices::RecordNode::getExperimentNumber(0); //2024-03-27 - Default to recording nodeid == 0. 
	bool curr_recording_thread_status = CoreServices::RecordNode::getRecordThreadStatus();

	if (enable_debug_printing) {
		CoreServices::sendStatusMessage("\t PhoTimesyncFileHelper::writeOutCustomFile: destDirectory: " + destDirectory.getFullPathName());
		CoreServices::sendStatusMessage("\t \t curr_experiment_number: " + String(curr_experiment_number));
		CoreServices::sendStatusMessage("\t \t curr_recording_thread_status: " + String(curr_recording_thread_status));
	}

	if (!destDirectory.isDirectory())
	{
		std::cout << "PhoTimesyncFileHelper::writeOutCustomFile: Destination directory doesn't exist: "
				<< destDirectory.getFullPathName() << std::endl << std::endl;

		// Create the directory if it doesn't exist
		// destDirectory.createDirectory();
		if (enable_debug_printing) {
			CoreServices::sendStatusMessage("\t PhoTimesyncFileHelper::writeOutCustomFile: destDirectory " + destDirectory.getFullPathName() + "doesn't exist. Aborting.");
		}
		return false;
	}

	const auto outputFilePath = destDirectory.getChildFile("RecordingStartSystemDatetime").withFileExtension (".txt");
	
	if (is_dry_run) {
		if (enable_debug_printing) {
			CoreServices::sendStatusMessage("\t PhoTimesyncFileHelper::writeOutCustomFile: outputFilePath: " + String(outputFilePath.getFullPathName()));
		}
		String formattedRecordingStartTimeString = PhoDatetimeTimestampHelperSpace::formatPreciseFileTimeAsString(recordingStartSavedTimestamp);
		auto outputLine = "curr_experiment_number: " + String(curr_experiment_number) + "; startTime: " + formattedRecordingStartTimeString + "\r\n";
		if (enable_debug_printing) {
			CoreServices::sendStatusMessage(outputLine);
		}
	}
	else {
		const File outputTimestampFile (outputFilePath);
		std::cout << "Creating " << outputTimestampFile.getFullPathName() << "..." << std::endl << std::endl;
		if (enable_debug_printing) {
			// CoreServices::sendStatusMessage(String(outputTimestampFile.getFullPathName()));
			CoreServices::sendStatusMessage("\t PhoTimesyncFileHelper::writeOutCustomFile: outputFilePath: " + String(outputFilePath.getFullPathName()));
		}

		juce::int64 write_sw_timestamp = CoreServices::getGlobalTimestamp();

		// outputTimestampFile.deleteFile(); // This empties (deletes the contents of) the file
		std::unique_ptr<OutputStream> outputStream (outputTimestampFile.createOutputStream());
		if (outputStream == nullptr)
		{
			// std::cout << "Couldn't open " << outputTimestampFile.getFullPathName() << " for writing" << std::endl << std::endl;
			if (enable_debug_printing) {
				CoreServices::sendStatusMessage("!! ERROR: Couldn't open " + String(outputTimestampFile.getFullPathName()) +  " for writing");
			}
			return false;
		}

		//// Actual Output Portion:
		String formattedRecordingStartTimeString = PhoDatetimeTimestampHelperSpace::formatPreciseFileTimeAsString(recordingStartSavedTimestamp);
		// Finally, actually write to the output stream:
		*outputStream << "startTime:\t" << formattedRecordingStartTimeString << ", curr_experiment_number: " << String(curr_experiment_number) << "\r\n";
		outputStream = nullptr; // This closes the stream and should make sure the values are flushed out to the file
		// auto outputLine = "curr_experiment_number: " + String(curr_experiment_number) + "; startTime: " + formattedRecordingStartTimeString + "\r\n";

		// std::cout << std::endl << " PhoTimesyncFileHelper::writeOutCustomFile: wrote to " << outputTimestampFile.getFullPathName() << ". Complete." << std::endl;
		CoreServices::sendStatusMessage("\t PhoTimesyncFileHelper::writeOutCustomFile: wrote to " + String(outputTimestampFile.getFullPathName()) + ". Complete.");
	}


	return true;

	// // Create the timestamp child element:
	// XmlElement* recordingStartTimestampNode = new XmlElement("RecordingStartTimestamp");
	// recordingStartTimestampNode->setAttribute("test", "test_id");
	// if (hasRecorded) {
	// 	String formattedRecordingStartTimeString = PhoDatetimeTimestampHelperSpace::formatPreciseFileTimeAsString(recordingStartTime);
	// 	recordingStartTimestampNode->setAttribute("startTime", formattedRecordingStartTimeString);
	// }
	// else {
	// 	recordingStartTimestampNode->setAttribute("startTime", "");
	// }
	// // Now that we have the Xml to write, do it!
	// ProcessScopedLock pl (createProcessLock());

	// if (pl != nullptr && ! pl->isLocked())
	//     return false; // locking failure..

	// if (doc.writeToFile (file, String()))
	// {
	//     needsWriting = false;
	//     return true;
	// }

	// return false;
}


//  ScopedPointer<PropertiesFile> userProps

// Looks like juce_PropertiesFile is what I want:
/* PropertiesFile: Wrapper on a file that stores a list of key/value data pairs.
	it keeps all the values in memory and writes them out to disk lazily when they are changed
*/

// From juce_File.h:

//  String createLegalPathName (const String& pathNameToFix);

// FileOutputStream* createOutputStream (size_t bufferSize = 0x8000) const;



// ScopedPointer<OutputStream> out (tempFile.getFile().createOutputStream());

//     if (out != nullptr)
//     {
//         if (options.storageFormat == storeAsCompressedBinary)
//         {
//             out->writeInt (PropertyFileConstants::magicNumberCompressed);
//             out->flush();

//             out = new GZIPCompressorOutputStream (out.release(), 9, true);
//         }
//         else
//         {
//             // have you set up the storage option flags correctly?
//             jassert (options.storageFormat == storeAsBinary);

//             out->writeInt (PropertyFileConstants::magicNumber);
//         }

//         const StringPairArray& props = getAllProperties();
//         const int numProperties   = props.size();
//         const StringArray& keys   = props.getAllKeys();
//         const StringArray& values = props.getAllValues();

//         out->writeInt (numProperties);

//         for (int i = 0; i < numProperties; ++i)
//         {
//             out->writeString (keys[i]);
//             out->writeString (values[i]);
//         }

//         out = nullptr;

//         if (tempFile.overwriteTargetFileWithTemporary())
//         {
//             needsWriting = false;
//             return true;
//         }
//     }


// bool PhoTimesyncFileHelper::saveAsXml()
// {
//     XmlElement doc (PropertyFileConstants::fileTag);
//     const StringPairArray& props = getAllProperties();

//     for (int i = 0; i < props.size(); ++i)
//     {
//         XmlElement* const e = doc.createNewChildElement (PropertyFileConstants::valueTag);
//         e->setAttribute (PropertyFileConstants::nameAttribute, props.getAllKeys() [i]);

//         // if the value seems to contain xml, store it as such..
//         if (XmlElement* const childElement = XmlDocument::parse (props.getAllValues() [i]))
//             e->addChildElement (childElement);
//         else
//             e->setAttribute (PropertyFileConstants::valueAttribute, props.getAllValues() [i]);
//     }

//     ProcessScopedLock pl (createProcessLock());

//     if (pl != nullptr && ! pl->isLocked())
//         return false; // locking failure..

//     if (doc.writeToFile (file, String()))
//     {
//         needsWriting = false;
//         return true;
//     }

//     return false;
// }


} // end namespace


#endif
