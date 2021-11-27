//This prevents include loops. We recommend changing the macro to a name suitable for your plugin
#ifndef PhoTimesyncFileHelper_H_DEFINED
#define PhoTimesyncFileHelper_H_DEFINED
// PhoTimesyncFileHelper.h

#include <chrono>
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
	bool PhoTimesyncFileHelper::writeOutCustomFile(std::chrono::system_clock::time_point recordingStartSavedTimestamp)
		// Note that this destDirectory finds a subfolder!
		// const File destDirectory (File::getCurrentWorkingDirectory()
		// 							.getChildFile (String ("DestDirName").unquoted()));
		const File destDirectory (File::getCurrentWorkingDirectory());
		if (! destDirectory.isDirectory())
		{
			std::cout << "Destination directory doesn't exist: "
					<< destDirectory.getFullPathName() << std::endl << std::endl;
			return 0;
		}

		const File headerFile (destDirectory.getChildFile("RecordingStartSystemDatetime").withFileExtension (".txt"));
		std::cout << "Creating " << headerFile.getFullPathName()
					<< "..." << std::endl << std::endl;

		headerFile.deleteFile(); // This empties (deletes the contents of) the file
		std::unique_ptr<OutputStream> header (headerFile.createOutputStream());

		if (header == nullptr)
		{
			std::cout << "Couldn't open "
					<< headerFile.getFullPathName() << " for writing" << std::endl << std::endl;
			return 0;
		}

		String formattedRecordingStartTimeString = PhoDatetimeTimestampHelperSpace::formatPreciseFileTimeAsString(recordingStartSavedTimestamp);

		// Finally, actually write to the output stream:
		*header << "startTime:\t" << formattedRecordingStartTimeString << "\r\n";
		header = nullptr; // This closes the stream and should make sure the values are flushed out to the file

		std::cout << std::endl << " PhoTimesyncFileHelper::writeOutCustomFile: wrote to " << headerFile.getFullPathName() << ". Complete." << std::endl;
		return 0;

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
