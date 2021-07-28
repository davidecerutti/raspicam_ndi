#pragma once

#include <fstream>
#include <string>
#include "log_for_console_and_file.h"

class UserInput {

private:
    std::string arrayInputFile[12];     //array made of string to put the user input from files
    logClass* log;

public:
    bool errorCorrection;   //if apply errorcorrection in setting time (runtime)

public:

    UserInput(logClass *logClassFromMain, bool errorCorrcetion) {
        this->log = logClassFromMain;
        this->errorCorrection = errorCorrcetion;
    }

    void arrayFillerFromFile(int* arrayToFillFromFile) {    //the reference of an array will be taken as input value

        log->event("Fill the array with user's input from file");
        std::ifstream myReadFile;   //initialize the streaming input variable

        try {
            myReadFile.open("CameraSettings.txt");
            if (!myReadFile) {
                throw "file CameraSettings is not found";
            }
            /*
            * try if the file exsit and could be open, open it
            * if file could not be open throw an exception "file not found"
            */

            log->event("File exist, start loading");
            for (int i = 0; i < 12; i++) {  //all of user input files has 12 rows

                std::getline(myReadFile, arrayInputFile[i]);    //function to get one line from the stream

                if (i != 2) {
                    arrayToFillFromFile[i] = std::stoi(arrayInputFile[i]);
                }
                else {
                    if (arrayInputFile[i] == "p") {
                        arrayToFillFromFile[i] = 1;
                    }
                    else {
                        arrayToFillFromFile[i] = 0;
                    }
                }
                /*
                * in the 3th row (pos 2 in array) the value is a char "p" or "i", replace the char with number p=1 i=0
                */
            }

        }
        catch (const char* exception) {
            log->error((std::string)exception);
        }
        /*
        * if the exception was thrown by the try block, handle the exception, print out the error value
        */

        log->event("Array filled with User's input, closing CameraSettings file");
        myReadFile.close(); //close file in stream

    }

    typedef struct ckeckInputIntegrityStructure {
        bool absolute;
        bool array[12];
    };
    /*
    * a public type for the variable to return the integrity of the file
    * recall in other threads as UserInput::ckeckInputIntegrityStructure
    * absolute to controll tha all the value will be true, array to identify what value in input was incorrect (if absolute is true, ignore array)
    */

    ckeckInputIntegrityStructure ckeckInputIntegrity() {

        log->event("Array filled with User's input passed to check integrity");

        ckeckInputIntegrityStructure tokenToProveAutenticity;
        for (int i = 0; i < 12; i++) {
            tokenToProveAutenticity.array[i] = true;
        }
        tokenToProveAutenticity.absolute = true;
        /*
        * initialize all the structure with true values
        * then check every single element in the array if is valit, if is not, mark the absolute as false, also in the correct array position mark as false
        */

       {
        if (std::stoi(this->arrayInputFile[0]) != 480 &&
            std::stoi(this->arrayInputFile[0]) != 720 &&
            std::stoi(this->arrayInputFile[0]) != 1080) {

            tokenToProveAutenticity.absolute = tokenToProveAutenticity.array[0] = false;
            log->warning("User input loaded resolution is not valid, index 0 of array");
        }
        if (std::stoi(this->arrayInputFile[1]) != 25 &&
            std::stoi(this->arrayInputFile[1]) != 30 &&
            std::stoi(this->arrayInputFile[1]) != 50 &&
            std::stoi(this->arrayInputFile[1]) != 60) {

            tokenToProveAutenticity.absolute = tokenToProveAutenticity.array[1] = false;
            log->warning("User input loaded framerate is not valid, index 1 of array");
        }
        if (this->arrayInputFile[2] != "p" &&
            this->arrayInputFile[2] != "i") {

            tokenToProveAutenticity.absolute = tokenToProveAutenticity.array[2] = false;
            log->warning("User input loaded formatype is not valid, index 2 of array");
        }
        if (std::stoi(this->arrayInputFile[3]) < 0 ||
            std::stoi(this->arrayInputFile[3]) > 100) {

            tokenToProveAutenticity.absolute = tokenToProveAutenticity.array[3] = false;
            log->warning("User input loaded brightness is not valid, index 3 of array");
        }
        if (std::stoi(this->arrayInputFile[4]) < -100 ||
            std::stoi(this->arrayInputFile[4]) > 100) {

            tokenToProveAutenticity.absolute = tokenToProveAutenticity.array[4] = false;
            log->warning("User input loaded sharpness is not valid, index 4 of array");
        }
        if (std::stoi(this->arrayInputFile[5]) < -100 ||
            std::stoi(this->arrayInputFile[5]) > 100) {

            tokenToProveAutenticity.absolute = tokenToProveAutenticity.array[5] = false;
            log->warning("User input loaded contrast is not valid, index 5 of array");
        }
        if (std::stoi(this->arrayInputFile[6]) < -100 ||
            std::stoi(this->arrayInputFile[6]) > 100) {

            tokenToProveAutenticity.absolute = tokenToProveAutenticity.array[6] = false;
            log->warning("User input loaded saturation is not valid, index 6 of array");
        }
        if (std::stoi(this->arrayInputFile[7]) < 0 ||
            std::stoi(this->arrayInputFile[7]) > 330000) {

            tokenToProveAutenticity.absolute = tokenToProveAutenticity.array[7] = false;
            log->warning("User input loaded shutter speed is not valid, index 7 of array");
        }
        if (std::stoi(this->arrayInputFile[8]) < 100 ||
            std::stoi(this->arrayInputFile[8]) > 800) {

            tokenToProveAutenticity.absolute = tokenToProveAutenticity.array[8] = false;
            log->warning("User input loaded ISO is not valid, index 8 of array");
        }
        if (std::stoi(this->arrayInputFile[9]) < -10 ||
            std::stoi(this->arrayInputFile[9]) > 10) {

            tokenToProveAutenticity.absolute = tokenToProveAutenticity.array[9] = false;
            log->warning("User input loaded exposoure compensation is not valid, index 9 of array");
        }
        if (std::stoi(this->arrayInputFile[10]) < 0 ||
            std::stoi(this->arrayInputFile[10]) > 8) {

            tokenToProveAutenticity.absolute = tokenToProveAutenticity.array[10] = false;
            log->warning("User input loaded WB red is not valid, index 10 of array");
        }
        if (std::stoi(this->arrayInputFile[11]) < 0 ||
            std::stoi(this->arrayInputFile[11]) > 8) {

            tokenToProveAutenticity.absolute = tokenToProveAutenticity.array[11] = false;
            log->warning("User input loaded WB green is not valid, index 11 of array");
        }
    }

       log->event("Return token to prove autenticy of user's inputs");
        return tokenToProveAutenticity;
    }

    int getwidthFromUI(int eigthFromUI) {   //input is the file first, array position 0     -> array[0]

        /*
        * resolution calcolus for x axes, user's data are only about y axes, common lenguage for resolution, as "1080, 720, ecc"
        */

        switch (eigthFromUI) {
            case (480):
                return 640;
            case (720):
                return 1280;
            case (1080):
                return 1920;
            default:
                return 1280;
        }
        
    }
    


};