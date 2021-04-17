#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <thread>         
#include <chrono>
#include </home/pi/Desktop/NDI SDK for Linux/include/Processing.NDI.Embedded.h>
#include <raspicam/raspicam.h>

#define X_RESOLUTION 1280
#define Y_RESOLUTION 720


using namespace std;

//*****list of exposure avaiable
    // raspicam::RASPICAM_EXPOSURE_OFF;
    // raspicam::RASPICAM_EXPOSURE_NIGHT;
    // raspicam::RASPICAM_EXPOSURE_NIGHTPREVIEW;
    // raspicam::RASPICAM_EXPOSURE_BACKLIGHT;
    // raspicam::RASPICAM_EXPOSURE_SPOTLIGHT;
    // raspicam::RASPICAM_EXPOSURE_SPORTS;
    // raspicam::RASPICAM_EXPOSURE_SNOW;
    // raspicam::RASPICAM_EXPOSURE_BEACH;
    // raspicam::RASPICAM_EXPOSURE_VERYLONG;
    // raspicam::RASPICAM_EXPOSURE_FIXEDFPS;
    // raspicam::RASPICAM_EXPOSURE_ANTISHAKE;
    // raspicam::RASPICAM_EXPOSURE_FIREWORKS;
/*default*/ // raspicam::RASPICAM_EXPOSURE_AUTO;


//*****list of awb avaiable
	// raspicam::RASPICAM_AWB_OFF;
	// raspicam::RASPICAM_AWB_SUNLIGHT;
	// raspicam::RASPICAM_AWB_CLOUDY;
	// raspicam::RASPICAM_AWB_SHADE;
	// raspicam::RASPICAM_AWB_TUNGSTEN;
	// raspicam::RASPICAM_AWB_FLUORESCENT;
	// raspicam::RASPICAM_AWB_INCANDESCENT;
	// raspicam::RASPICAM_AWB_FLASH;
	// raspicam::RASPICAM_AWB_HORIZON;
/*default*/ //return raspicam::RASPICAM_AWB_AUTO;


void processCommandLine ( int argc,char **argv,raspicam::RaspiCam &Camera ) {
	
    Camera.setWidth ( X_RESOLUTION );
    Camera.setHeight ( Y_RESOLUTION );
    Camera.setBrightness ( 50 ); 								//brightness_val(0,100)
    Camera.setSharpness ( 0 ); 									//sharpness_val (-100 to 100)
    Camera.setContrast ( 0 ); 									//contrast_val (-100 to 100)
    Camera.setSaturation ( 0 ); 								//saturation_val (-100 to 100)
    Camera.setShutterSpeed ( 0 ); 								//shutter_speed_val value in microsecs (max 330000)
    Camera.setISO ( 400 ); 									//ISO_val  (100 to 800)
    Camera.setFrameRate( 25 );									//framerate_val (1 to 90)
    Camera.setVideoStabilization (false);	
    Camera.setExposureCompensation (0); 							//exposure_compensation_value(-10 to 10)
    Camera.setFormat(raspicam::RASPICAM_FORMAT_YUV420); 					//RASPICAM_FORMAT_YUV420 or RASPICAM_FORMAT_RGB
    Camera.setExposure (raspicam::RASPICAM_EXPOSURE_AUTO);					//list 
    Camera.setAWB(raspicam::RASPICAM_AWB_AUTO);							//list 
    Camera.setAWB_RB(1,1); 									//val (0 to 8),(0 to 8) set the value for the red,green component of white balance

}


int main ( int argc,char **argv ) {
	


    raspicam::RaspiCam Camera;
	
    processCommandLine ( argc,argv,Camera );
    //"Connecting to camera"
    if ( !Camera.open() ) {
        cerr<<"Error opening camera"<<endl;
        return -1;
    }
    std::cout<<"Connected to camera "<<std::endl;
    unsigned char *data=new unsigned char[  Camera.getImageBufferSize( )];
    
    
    if (!NDIlib_initialize())
	{	
		std::cout<<"Cannot run NDI."<<std::endl;
		return -1;
	} 
	
	NDIlib_send_create_t source_send;
		source_send.p_ndi_name = "Raspicam";
		source_send.p_groups = NULL;
		source_send.clock_video = true;
		
	NDIlib_send_instance_t Pi_Sender = NDIlib_send_create(&source_send);
	if (!Pi_Sender){
		std::cout<<"Error creating NDI sender";
		return -1;
	} else std::cout<<"Connected to NDI"<<std::endl;

	NDIlib_video_frame_v2_t video_frame;
		video_frame.xres = X_RESOLUTION;
		video_frame.yres = Y_RESOLUTION;
		video_frame.FourCC = NDIlib_FourCC_type_I420;
		video_frame.frame_rate_N = 60000;
		video_frame.frame_rate_D = 1200;
		video_frame.picture_aspect_ratio = 16.0f/9.0f;
		video_frame.line_stride_in_bytes =   X_RESOLUTION * sizeof(uint8_t) ;
		video_frame.frame_format_type = NDIlib_frame_format_type_progressive;
		video_frame.timecode = 0;
		video_frame.p_metadata = "<Raspicam/>";
		
		double Frame_rate_send = (1/(video_frame.frame_rate_N / video_frame.frame_rate_D))*1000;
	
	
	while (true){
		
	auto Start_time = std::chrono::high_resolution_clock::now();
		
	Camera.grab();
	Camera.retrieve ( data );       
  
	video_frame.p_data = data;
	NDIlib_send_send_video_v2(Pi_Sender, &video_frame);
	
	
	auto Finish_time = std::chrono::high_resolution_clock::now();
	
		std::chrono::duration<double, std::milli> Counting_time = Finish_time - Start_time;
	
	if (Counting_time.count() < Frame_rate_send){
				int Sleeping_time = (int)Frame_rate_send - (int)Counting_time.count();
				std::this_thread::sleep_for (std::chrono::milliseconds(Sleeping_time));
		}
	
	
}


    Camera.release();

	NDIlib_destroy();

}



