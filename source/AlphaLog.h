#pragma once

#include "AlphaString.h"

namespace Alpha
{
	void logSeparator();
	void logMessage(const UnicodeString& message);
	void logError(const UnicodeString& message);
	void logWarning(const UnicodeString& message);

	UnicodeString getDateAndTime();
	void checkLogFile();

	void log(const UnicodeString& message);
	void debugDisplayLog(const UnicodeString& message);
	void displayLog(const UnicodeString& message);
	void writeLog(const UnicodeString& message);

	bool isFileOpened(std::wofstream& outputFile);
}