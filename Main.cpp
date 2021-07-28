#include <iostream>

#include </home/pi/Desktop/NDI SDK for Linux/include/Processing.NDI.Embedded.h>
#include <raspicam/raspicam.h>

#include "reading_from_file_UI.h"
#include "log_for_console_and_file.h"
#include "set_camera_and_streaming.h"



int main() {

	logClass log(logLevelConsideration::Low, logLevelConsideration::Low);
	log.warning("starting main thread");

	raspicam::RaspiCam Camera;

	try {

		if (!NDIlib_initialize()) {
			throw "impossible to run NDI";
		}

	}
	catch (const char* exception) {
		log.error((std::string)exception);
	}

	NDIlib_send_create_t sourceSend;
	log.event("creating source NDI as RaspicamNDI");

	sourceSend.p_ndi_name = "RaspicamNDI";
	sourceSend.p_groups = NULL;
	sourceSend.clock_video = true;

	NDIlib_send_instance_t PiSender;

	try {

		PiSender = NDIlib_send_create(&sourceSend);

		if (!PiSender) {
			throw "impossible to istance a sender";
		}

		log.event("creating NDI sender instance");
	}
	catch (const char* exception) {
		log.error((std::string)exception);
	}

	NDIlib_video_frame_v2_t videoFrame;

	setCameraNDI(&log, &Camera, &videoFrame);
	log.event("submit camera and frame to user's settings");

	try {

		if (!Camera.open()) {
			throw "impossible to open raspberryPi camera";
		}
	}
	catch (const char* exception) {
		log.error((std::string)exception);
	}

	unsigned char* data = new unsigned char[Camera.getImageBufferSize()];

	log.warning("start submitting buffer and sending NDI stream");

	log.~logClass();

	while (true) {

		Camera.grab();
		Camera.retrieve(data);

		videoFrame.p_data = data;
		NDIlib_send_send_video_v2(PiSender, &videoFrame);

	}


	Camera.release();

	NDIlib_destroy();


	return 0;
}



