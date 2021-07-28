#pragma once
#pragma warning(disable : 4996)

/*
*	Log Class	log for console and file	header file for c++				By Cerutti Davide
* 
*	this log class provides 3 differtent level of log: [event] [warning] [error]
*	and 3 different level of information:	 Low -> report -> [event] [warning] [error]
*										  Medium -> report -> [event] [warning] [error]
*										    High -> report -> [event] [warning] [error]
* 
*	the log reporting is based on 2 layers: Console message and print on file
*	the level of information reporting could be different for Console and FileLog
* 
*	currentDateTime provides the actual time for every log
*	all logs message for file are stored in a std::string, and new message are appended to it
*	the distructor create the file, streams in output the strings and then close the file
* 
*	the constructor requires the level of information for console and file
*	public methods are error warning and event, they requires a string as input pharameters (const char* from the super in exceptions casted)
*/

#include <string>
#include <iostream>
#include <fstream>



enum class logLevelConsideration {
	Low,
	Medium,
	High
};
/*
* log level enum, low=0 , medium = 1 and high = 2
* clas to define object as logLevelConsideration::name
*/


class logClass {

private:

	logLevelConsideration logLevelConsole;
	logLevelConsideration logLevelPrint;

	std::string outputLogStream;	//the buffer to streaming to file

public:

	logClass(logLevelConsideration logLevelConsole, logLevelConsideration logLevelPrint) {	//new logClass(logLevelConsideration::VAL, logLevelConsideration::VAL)
		this->logLevelConsole = logLevelConsole;
		this->logLevelPrint = logLevelPrint;

		outputLogStream.append(currentDateTime());
		outputLogStream.append(" [Starting new log file]\n");	//default opening for stream output
	}

	~logClass() {	//usually called by the ending of scope, for log suggestion is to put in main thread, so live for all the program life to report log

		outputLogStream.append(currentDateTime());
		outputLogStream.append(" [Closing log file]");	//default closing for stream output

		std::ofstream outputFileLog("LogFile.txt");		//if the file not exist create one
		outputFileLog << outputLogStream;	//send to the file out streaming the string with datas			
		outputFileLog.close();
	}

	void event(std::string message) {
		/*
		* executed if the level for this methods is higher than the level for log information passed by constructor
		* event will be wrote if the level is low
		*/

		if (this->logLevelConsole <= logLevelConsideration::Low) {
			std::cout << currentDateTime() << " [Event] " << message << std::endl;		//stream in std::cout with date, marker and message
		}
		if (this->logLevelPrint <= logLevelConsideration::Low) {
			outputLogStream.append(currentDateTime());			//append to the string the current date (returned as string)
			outputLogStream.append(" [Event] ");				//append to the string the marker []
			outputLogStream.append(message);					//append to the string the message passed (pased to method as string)
			outputLogStream.append("\n");						//end line 
		}
	}

	void warning(std::string message) {
		/*
		* executed if the level for this methods is higher than the level for log information passed by constructor
		* warning will be wrote if the level is medium or low
		*/

		if (this->logLevelConsole <= logLevelConsideration::Medium) {
			std::cout << currentDateTime() << " [Warning] " << message << std::endl;
		}
		if (this->logLevelPrint <= logLevelConsideration::Medium) {
			outputLogStream.append(currentDateTime());
			outputLogStream.append(" [Warning] ");
			outputLogStream.append(message);
			outputLogStream.append("\n");
		}
	}

	void error(std::string message) {
		/*
		* executed if the level for this methods is higher than the level for log information passed by constructor
		* error will be wrote if the level is high, medium or low; so ever
		*/
		if (this->logLevelConsole <= logLevelConsideration::High) {
			std::cout << currentDateTime() << " [Error] " << message << std::endl;
		}
		if (this->logLevelPrint <= logLevelConsideration::High) {
			outputLogStream.append(currentDateTime());
			outputLogStream.append(" [Error] ");
			outputLogStream.append(message);
			outputLogStream.append("\n");
		}
	}

private:

	//private method to return the current time for log, called from public methods
	const std::string currentDateTime() {
		time_t now = time(0);
		struct tm tstruct;
		char buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
		return buf;
	}

};

