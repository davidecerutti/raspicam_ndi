#pragma once

/*
*	setCameraNDI void function
*	
*	takes in input:	pointer to main log class
*					pointer to raspicam object
*					pointer to video frame from ndi
* 
*	instanciate a new user input object and an array to deposit user's input
*	fill the array from the user's input, check the integrity of data
* 
*	if the flag for ECC error checking and CORRECTING, correct user's data where is necessary, replacing with default 
*/

#include </home/pi/Desktop/NDI SDK for Linux/include/Processing.NDI.Embedded.h>
#include <raspicam/raspicam.h>

#include "reading_from_file_UI.h"
#include "log_for_console_and_file.h"



void setCameraNDI(logClass* log, raspicam::RaspiCam* Camera, NDIlib_video_frame_v2_t* videoFrame) {

	UserInput UserInput(log, true);		//object userinput ( logClass, flag ECC boolean ) 

	int array[12];
	UserInput.arrayFillerFromFile(array);	//fill the array with all the input from user's data

	UserInput::ckeckInputIntegrityStructure checkFlagIntegrity = UserInput.ckeckInputIntegrity();

	if (checkFlagIntegrity.absolute == true) {		//all the data are checked and ok for be passed

		/*
		* for every method of raspicam, set the correct value from the user's inputs data in the array
		* 
		* for every varaible coming from NDI frame instance give the correct value from user's input data
		*/

			Camera->setWidth(UserInput.getwidthFromUI(array[0]));	//calculus for the x axes from y axes
			Camera->setHeight(array[0]);
			Camera->setBrightness(array[3]);
			Camera->setSharpness(array[4]);
			Camera->setContrast(array[5]);
			Camera->setSaturation(array[6]);
			Camera->setShutterSpeed(array[7]);
			Camera->setISO(array[8]);
			Camera->setFrameRate(array[1]);
			Camera->setVideoStabilization(false);
			Camera->setExposureCompensation(array[9]);
			Camera->setFormat(raspicam::RASPICAM_FORMAT_YUV420);		//YUV420 compatible with NDI
			Camera->setExposure(raspicam::RASPICAM_EXPOSURE_AUTO);
			Camera->setAWB(raspicam::RASPICAM_AWB_AUTO);
			Camera->setAWB_RB(array[10], array[11]);

			videoFrame->xres = UserInput.getwidthFromUI(array[0]);
			videoFrame->yres = array[0];
			videoFrame->FourCC = NDIlib_FourCC_type_I420;		//I420 compatible with Raspicam

			videoFrame->picture_aspect_ratio = 16.0f / 9.0f;	
			videoFrame->line_stride_in_bytes = videoFrame->xres * sizeof(uint8_t);

			videoFrame->timecode = 0;
			videoFrame->p_metadata = "<Raspicam/>";


			if (array[2] == 0) {	//calculus for format type and frame rate		array[2] is format, 0 = i, 1 = p

				videoFrame->frame_format_type = NDIlib_frame_format_type_interleaved;

				if (array[1] == 60) {
					videoFrame->frame_rate_N = 30000;
					videoFrame->frame_rate_D = 1100;
				}
				else if (array[1] == 50) {
					videoFrame->frame_rate_N = 30000;
					videoFrame->frame_rate_D = 1200;
				}
				else if (array[1] == 30) {
					videoFrame->frame_rate_N = 15000;
					videoFrame->frame_rate_D = 1100;
				}
				else if (array[1] == 25) {
					videoFrame->frame_rate_N = 15000;
					videoFrame->frame_rate_D = 1200;
				}

			}
			else {

				videoFrame->frame_format_type = NDIlib_frame_format_type_progressive;

				if (array[1] == 60) {
					videoFrame->frame_rate_N = 60000;
					videoFrame->frame_rate_D = 1100;
				}
				else if (array[1] == 50) {
					videoFrame->frame_rate_N = 60000;
					videoFrame->frame_rate_D = 1200;
				}
				else if (array[1] == 30) {
					videoFrame->frame_rate_N = 30000;
					videoFrame->frame_rate_D = 1100;
				}
				else if (array[1] == 25) {
					videoFrame->frame_rate_N = 30000;
					videoFrame->frame_rate_D = 1200;
				}

			}
		
	}
	else {

		if (UserInput.errorCorrection == true) {	//check the falg for ECC, if true then correct error, replace with default

			if (checkFlagIntegrity.array[0] == false) {
				array[0] = 720;
			}
			if (checkFlagIntegrity.array[1] == false) {
				array[1] = 25;
			}
			if (checkFlagIntegrity.array[2] == false) {
				array[2] = 1;
			}
			for (int i = 3; i < 12; i++) {
				if (checkFlagIntegrity.array[i] == false) {
					array[i] = 0;
				}
			}
			if (checkFlagIntegrity.array[8] == false) {
				array[8] = 450;
			}

			log->event("invalid input values found and corrected");
		}
		else {
			log->warning("invalid input values found and not corrected");
		}

		Camera->setWidth(UserInput.getwidthFromUI(array[0]));
		Camera->setHeight(array[0]);
		Camera->setBrightness(array[3]);
		Camera->setSharpness(array[4]);
		Camera->setContrast(array[5]);
		Camera->setSaturation(array[6]);
		Camera->setShutterSpeed(array[7]);
		Camera->setISO(array[8]);
		Camera->setFrameRate(array[1]);
		Camera->setVideoStabilization(false);
		Camera->setExposureCompensation(array[9]);
		Camera->setFormat(raspicam::RASPICAM_FORMAT_YUV420);
		Camera->setExposure(raspicam::RASPICAM_EXPOSURE_AUTO);
		Camera->setAWB(raspicam::RASPICAM_AWB_AUTO);
		Camera->setAWB_RB(array[10], array[11]);

		videoFrame->xres = UserInput.getwidthFromUI(array[0]);
		videoFrame->yres = array[0];
		videoFrame->FourCC = NDIlib_FourCC_type_I420;

		videoFrame->picture_aspect_ratio = 16.0f / 9.0f;
		videoFrame->line_stride_in_bytes = videoFrame->xres * sizeof(uint8_t);

		videoFrame->timecode = 0;
		videoFrame->p_metadata = "<Raspicam/>";


		if (array[2] == 0) {

			videoFrame->frame_format_type = NDIlib_frame_format_type_interleaved;

			if (array[1] == 60) {
				videoFrame->frame_rate_N = 30000;
				videoFrame->frame_rate_D = 1100;
			}
			else if (array[1] == 50) {
				videoFrame->frame_rate_N = 30000;
				videoFrame->frame_rate_D = 1200;
			}
			else if (array[1] == 30) {
				videoFrame->frame_rate_N = 15000;
				videoFrame->frame_rate_D = 1100;
			}
			else if (array[1] == 25) {
				videoFrame->frame_rate_N = 15000;
				videoFrame->frame_rate_D = 1200;
			}

		}
		else {

			videoFrame->frame_format_type = NDIlib_frame_format_type_progressive;

			if (array[1] == 60) {
				videoFrame->frame_rate_N = 60000;
				videoFrame->frame_rate_D = 1100;
			}
			else if (array[1] == 50) {
				videoFrame->frame_rate_N = 60000;
				videoFrame->frame_rate_D = 1200;
			}
			else if (array[1] == 30) {
				videoFrame->frame_rate_N = 30000;
				videoFrame->frame_rate_D = 1100;
			}
			else if (array[1] == 25) {
				videoFrame->frame_rate_N = 30000;
				videoFrame->frame_rate_D = 1200;
			}

		}
	}

	log->event("Raspicam and frame settings loaded");
}

