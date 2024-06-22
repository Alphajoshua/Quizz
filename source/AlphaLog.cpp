#include "AlphaLog.h"

#include <iostream>
#include <fstream>
#include <ctime>

#include <filesystem>

#include "Constants.h"
#include "StringToolBox.h"

namespace Alpha
{
	const auto CURRENT_DIRECTORY{ std::filesystem::current_path() };
	const auto LOG_FILE_PATH{ CURRENT_DIRECTORY / SOFTWARE_DIRECTORY / "alpha.log" };

	void logSeparator()
	{
		log(LOG_SEPARATOR);
	}
	void logMessage(const UnicodeString& message)
	{
		const auto logText = getDateAndTime() + L" " + message;
		log(logText);
	}
	void logError(const UnicodeString& message)
	{
		const auto logText = getDateAndTime() + L" !ERROR!: " + message;
		log(logText);
	}
	void logWarning(const UnicodeString& message)
	{
		const auto logText = getDateAndTime() + L" /!\\WARNING: " + message;
		log(logText);
	}
	UnicodeString getDateAndTime()
	{
		std::time_t currentTime;
		std::time(&currentTime);

		std::tm timeInfo;
		localtime_s(&timeInfo, &currentTime);

		AlphaChar buffer[80];
		std::strftime(buffer, sizeof(buffer), "%d/%m/%Y | [%H:%M:%S]", &timeInfo);

		return StringToolBox::getUnicodeString(buffer);
	}
	void checkLogFile()
	{
		if ( !std::filesystem::exists(LOG_FILE_PATH) || !std::filesystem::is_regular_file(LOG_FILE_PATH))
		{
			writeLog(L"################## Creation of alpha.log ##################");
		}
	}

	void log(const UnicodeString& message)
	{
		checkLogFile();
		debugDisplayLog(message);
		writeLog(message);
	}
	void debugDisplayLog(const UnicodeString& message)
	{
#ifdef _DEBUG
		displayLog(message);
#endif
	}
	void displayLog(const UnicodeString& message)
	{
		std::wcout << StringToolBox::getUtf8(message).c_str() << std::endl;
	}
	void writeLog(const UnicodeString& message)
	{
		if ( std::wofstream outputFile; isFileOpened(outputFile) )
		{
			outputFile << StringToolBox::getUtf8(message).c_str() << std::endl;
			outputFile.close();
		}
		
	}
	bool isFileOpened(std::wofstream& outputFile)
	{
		outputFile.open(LOG_FILE_PATH, std::ios_base::app);
		return outputFile.is_open();
	}
}