#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <thread>         
#include <chrono>
#include </home/pi/Desktop/NDI SDK for Linux/include/Processing.NDI.Embedded.h>
#include <raspicam/raspicam.h>

	struct setting {			//declaring a global struct that will contain the information of the camera module
		int brightness_val;
		int sharpness_val;
		int contrast_val;
		int saturation_val;
		int shutter_speed_val;
		int ISO_val;
		bool stabilization_val;
		int exposure_compensation_val;
		int exposure_val;
		int awb_val;
		int setAWB_R;
		int setAWB_G;
	};

void ClearScreen(){				//a simple function to clear the terminal 
	for(int i = 0; i<100; i++){
		std::cout<<std::endl;
	}
}

void setNDI(int *x_resolution, int *y_resolution, int *frame_rate, short int *format_type){		//set up parametres for the stream
	using std::cout;
	using std::cin;
	using std::endl;
	
	int select;				//is the switcher variable
	bool fpchk = false;		//to check that the letter is I or P in the char ft
	short int i =0;			//because passing a short int is better than a full char
	short int p =1;
	char ft;				//to contain the choice between I or P, check by fpchk
	
	//building a simple menu with major format used
	cout<<"select format source"<<endl<<endl;
	cout<<"1	1280x720 60i"<<endl;
	cout<<"2	1280x720 60p"<<endl;
	cout<<"3	1280x720 50i"<<endl;
	cout<<"4	1280x720 50p"<<endl;
	cout<<"5	1280x720 30i"<<endl;
	cout<<"6	1280x720 30p"<<endl;
	cout<<"7	1280x720 25i"<<endl;
	cout<<"8	1280x720 25p"<<endl;
	cout<<endl;
	cout<<"11	1920x1080 60i		<bug YUV in 1080>"<<endl;
	cout<<"12	1920x1080 60p		<bug YUV in 1080>"<<endl;
	cout<<"13	1920x1080 50i		<bug YUV in 1080>"<<endl;
	cout<<"14	1920x1080 50p		<bug YUV in 1080>"<<endl;
	cout<<"15	1920x1080 30i		<bug YUV in 1080>"<<endl;
	cout<<"16	1920x1080 30p		<bug YUV in 1080>"<<endl;
	cout<<"17	1920x1080 25i		<bug YUV in 1080>"<<endl;
	cout<<"18	1920x1080 25p		<bug YUV in 1080>"<<endl;
	cout<<endl;
	cout<<"select 0 to insert youre format"<<endl;
	
	cin>>select;
	//set the values according to the choice selected
	switch (select){
		case 1:
			*y_resolution = 720;
			*x_resolution = 1280;
			*frame_rate = 60;
			*format_type = i;
			break;
		case 2:
			*y_resolution = 720;
			*x_resolution = 1280;
			*frame_rate = 60;
			*format_type = p;
			break;
		case 3:
			*y_resolution = 720;
			*x_resolution = 1280;
			*frame_rate = 50;
			*format_type = i;
			break;
		case 4:
			*y_resolution = 720;
			*x_resolution = 1280;
			*frame_rate = 50;
			*format_type = p;
			break;
		case 5:
			*y_resolution = 720;
			*x_resolution = 1280;
			*frame_rate = 30;
			*format_type = i;
			break;
		case 6:
			*y_resolution = 720;
			*x_resolution = 1280;
			*frame_rate = 30;
			*format_type = p;
			break;
		case 7:
			*y_resolution = 720;
			*x_resolution = 1280;
			*frame_rate = 25;
			*format_type = i;
			break;
		case 8:
			*y_resolution = 720;
			*x_resolution = 1280;
			*frame_rate = 25;
			*format_type = p;
			break;
		case 11:
			*y_resolution = 1080;
			*x_resolution = 1920;
			*frame_rate = 60;
			*format_type = i;
			break;
		case 12:
			*y_resolution = 1080;
			*x_resolution = 1920;
			*frame_rate = 60;
			*format_type = p;
			break;
		case 13:
			*y_resolution = 1080;
			*x_resolution = 1920;
			*frame_rate = 50;
			*format_type = i;
			break;
		case 14:
			*y_resolution = 1080;
			*x_resolution = 1920;
			*frame_rate = 50;
			*format_type = p;
			break;
		case 15:
			*y_resolution = 1080;
			*x_resolution = 1920;
			*frame_rate = 30;
			*format_type = i;
			break;
		case 16:
			*y_resolution = 1080;
			*x_resolution = 1920;
			*frame_rate = 30;
			*format_type = p;
			break;
		case 17:
			*y_resolution = 1080;
			*x_resolution = 1920;
			*frame_rate = 25;
			*format_type = i;
			break;
		case 18:
			*y_resolution = 1080;
			*x_resolution = 1920;
			*frame_rate = 25;
			*format_type = p;
			break;
			
		default:
		//in the default request to inser manually all the information
			cout<<"insert y resolution	";
			cin>>*y_resolution;
			cout<<endl;
			cout<<"insert x resolution	";
			cin>>*x_resolution;
			cout<<endl;
			cout<<"insert video frame rate	";
			cin>>*frame_rate;
			cout<<endl;
				while(fpchk ==  false){
					cout<<"insert video typedef (i for interleave, p for progressive)	  ";
					cin>>ft;
					if(ft == 'i' || ft == 'I') {*format_type= i; fpchk=true; cout<<endl;}
					if(ft == 'p' || ft == 'P') {*format_type= p; fpchk=true; cout<<endl;}
					if(fpchk == false){cout<<endl<<"retry using valid value"<<endl;}
				}
	}
	
}

void setCamera( struct setting *setting_camera ){		//set up parametres for the camera
	using std::cout;
	using std::cin;
	using std::endl;
	
	int selecter;				//is the switcher variable
	char stabint;				//to request at the activation of stabilization
	bool exit_value = false;	//stay in the loop until 0 exit
	
	while(exit_value == false){
	
	//building a simple menu to select the submenu to assign values
	cout<<"select a modifier to change values, enter 0 to exit"<<endl;
	
	cout<<"1 	to change brightness"<<endl;
	cout<<"2 	to change sharpness"<<endl;
	cout<<"3 	to change contrast"<<endl;
	cout<<"4 	to change saturation"<<endl;
	cout<<"5 	to change shutter speed"<<endl;
	cout<<"6 	to change ISO"<<endl;
	cout<<"7 	to change stabilization"<<endl;
	cout<<"8 	to change exposure compensation"<<endl;
	cout<<"9 	to change exposure"<<endl;
	cout<<"10 	to change white balance temperature"<<endl;
	cout<<"11 	to change white balance red component"<<endl;
	cout<<"12 	to change white balance green component"<<endl;
	
	cout<<endl;
	cin>>selecter;
	
	switch(selecter){
		case 1:
			cout<<"insert a brightness value between 0 and 100		";
			cin>>setting_camera->brightness_val;
			cout<<endl;
			break;
		case 2:
			cout<<"inser a sharpness value between -100 and +100 	";
			cin>>setting_camera->sharpness_val;
			cout<<endl;
			break;
		case 3:
			cout<<"inser a contrast value between -100 and +100 	";
			cin>>setting_camera->contrast_val;
			cout<<endl;
			break;
		case 4:
			cout<<"inser a saturation value between -100 and +100 	";
			cin>>setting_camera->saturation_val;
			cout<<endl;
			break;
		case 5:
			cout<<"inser a shutter speed value in microsecs max 330000	";
			cin>>setting_camera->shutter_speed_val;
			cout<<endl;
			break;
		case 6:
			cout<<"inser a iso speed value between 100 and 800 		";
			cin>>setting_camera->ISO_val;
			cout<<endl;
			break;
		case 7:
			cout<<"activate camera stabilization? S/N 		";
			cin>>stabint;
			if (stabint =='S' || stabint =='s') {setting_camera->stabilization_val = true;}
			if (stabint =='N' || stabint =='n') {setting_camera->stabilization_val = false;}
			cout<<endl;
			break;
		case 8:
			cout<<"inser a exposure compensation value between -10 and 10 		";
			cin>>setting_camera->exposure_compensation_val;
			cout<<endl;
			break;
		case 9:											//giving a number is more efficient than pass a Raspicam::object
			cout<<"0	exposure auto"<<endl;
			cout<<"1	exposure off"<<endl;
			cout<<"2	exposure night"<<endl;
			cout<<"3	exposure nightpreview"<<endl;
			cout<<"4	exposure backlight"<<endl;
			cout<<"5	exposure spotlight"<<endl;
			cout<<"6	exposure sports"<<endl;
			cout<<"7	exposure snow"<<endl;
			cout<<"8	exposure beach"<<endl;
			cout<<"9	exposure very long"<<endl;
			cout<<"10	exposure fixed fps"<<endl;
			cout<<"11	exposure antishake"<<endl;
			cout<<"12	exposure fireworks"<<endl;
			cout<<endl<<"select one exposure preset 	";
			cin>>setting_camera->exposure_val;
			cout<<endl;
			break;
		case 10:										//giving a number is more efficient than pass a Raspicam::object
			cout<<"0	awb auto"<<endl;
			cout<<"1	awb off"<<endl;
			cout<<"2	awb sunlight"<<endl;
			cout<<"3	awb cloudy"<<endl;
			cout<<"4	awb shade"<<endl;
			cout<<"5	awb tungsten"<<endl;
			cout<<"6	awb fluorescent"<<endl;
			cout<<"7	awb incandescent"<<endl;
			cout<<"8	awb flash"<<endl;
			cout<<"9	awb horizon"<<endl;
			cout<<endl<<"select one white balance temperature preset 	";
			cin>>setting_camera->awb_val;
			cout<<endl;
			break;
		case 11:
			cout<<"inser a white balance red component value between 0 and 8 		";
			cin>>setting_camera->setAWB_R;
			cout<<endl;
			break;
		case 12:
			cout<<"inser a green balance red component value between 0 and 8 		";
			cin>>setting_camera->setAWB_G;
			cout<<endl;
			break;
		case 0://exit to the menu
			exit_value = true;
			break;
		default:
			break;
		ClearScreen();
		}

	}
	
}

void setCameraDefault (struct setting *setting_camera){		//set up default parametres for the camera
		
		setting_camera->brightness_val = 50;
		setting_camera->sharpness_val = 0;
		setting_camera->contrast_val = 0;
		setting_camera->saturation_val = 0;
		setting_camera->shutter_speed_val = 0;
		setting_camera->ISO_val = 400;
		setting_camera->stabilization_val = false;
		setting_camera->exposure_compensation_val = 0;
		setting_camera->exposure_val = 0;
		setting_camera->awb_val = 0;
		setting_camera->setAWB_R = 1;
		setting_camera->setAWB_G = 1;
	
}

void processCamera (raspicam::RaspiCam &Camera, int x_resolution, int y_resolution, int frame_rate, struct setting setting_camera) {	//processing the set up parametres in a camera istance
	
    Camera.setWidth ( x_resolution );
    Camera.setHeight ( y_resolution );
	Camera.setFrameRate( frame_rate );
	//the format is locked at YUV, but also RGB is supported (but is heavier)
	Camera.setFormat(raspicam::RASPICAM_FORMAT_YUV420);
	
    Camera.setBrightness ( setting_camera.brightness_val ); 							
    Camera.setSharpness ( setting_camera.sharpness_val ); 								
    Camera.setContrast ( setting_camera.contrast_val ); 								
    Camera.setSaturation ( setting_camera.saturation_val ); 							
    Camera.setShutterSpeed ( setting_camera.shutter_speed_val ); 							
    Camera.setISO ( setting_camera.ISO_val ); 																	
    Camera.setVideoStabilization (setting_camera.stabilization_val);					
    Camera.setExposureCompensation (setting_camera.exposure_compensation_val);  
	//because was lighter pass a int than a raspicam object now recreate the report following the menu instruction
	if(setting_camera.exposure_val == 0) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_AUTO);}
	if(setting_camera.exposure_val == 1) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_OFF);}
	if(setting_camera.exposure_val == 2) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_NIGHT);}
	if(setting_camera.exposure_val == 3) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_NIGHTPREVIEW);}
	if(setting_camera.exposure_val == 4) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_BACKLIGHT);}
	if(setting_camera.exposure_val == 5) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_SPOTLIGHT);}
	if(setting_camera.exposure_val == 6) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_SPORTS);}
	if(setting_camera.exposure_val == 7) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_SNOW);}
	if(setting_camera.exposure_val == 8) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_BEACH);}
	if(setting_camera.exposure_val == 9) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_VERYLONG);}
	if(setting_camera.exposure_val == 10) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_FIXEDFPS);}
	if(setting_camera.exposure_val == 11) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_ANTISHAKE);}
	if(setting_camera.exposure_val == 12) {Camera.setExposure (raspicam::RASPICAM_EXPOSURE_FIREWORKS);}
 
	if(setting_camera.awb_val == 0) {Camera.setAWB(raspicam::RASPICAM_AWB_AUTO);}
	if(setting_camera.awb_val == 1) {Camera.setAWB(raspicam::RASPICAM_AWB_OFF);}
	if(setting_camera.awb_val == 2) {Camera.setAWB(raspicam::RASPICAM_AWB_SUNLIGHT);}
	if(setting_camera.awb_val == 3) {Camera.setAWB(raspicam::RASPICAM_AWB_CLOUDY);}
	if(setting_camera.awb_val == 4) {Camera.setAWB(raspicam::RASPICAM_AWB_SHADE);}
	if(setting_camera.awb_val == 5) {Camera.setAWB(raspicam::RASPICAM_AWB_TUNGSTEN);}
	if(setting_camera.awb_val == 6) {Camera.setAWB(raspicam::RASPICAM_AWB_FLUORESCENT);}
	if(setting_camera.awb_val == 7) {Camera.setAWB(raspicam::RASPICAM_AWB_INCANDESCENT);}
	if(setting_camera.awb_val == 8) {Camera.setAWB(raspicam::RASPICAM_AWB_FLASH);}
	if(setting_camera.awb_val == 9) {Camera.setAWB(raspicam::RASPICAM_AWB_HORIZON);}
	
    Camera.setAWB_RB(setting_camera.setAWB_R,setting_camera.setAWB_G); 										

}

void processNDI (NDIlib_video_frame_v2_t *video_frame, int x_resolution, int y_resolution, int frame_rate, short int format_type){	//processing the set up parametres in a NDI istance
	
	video_frame->xres = x_resolution;
	video_frame->yres = y_resolution;
	
	//the format is locked at YUV, but also RGB is supported (but is heavier)
	video_frame->FourCC = NDIlib_FourCC_type_I420;
	
	//according to video forma type selcet the frame rate in a different scale if I or P (same framerate I = P / 2)
	if(format_type == 0){
		
		video_frame->frame_format_type = NDIlib_frame_format_type_interleaved;
		
		if(frame_rate == 60){video_frame->frame_rate_N = 30000; video_frame->frame_rate_D = 1100;video_frame->picture_aspect_ratio = 16.0f/9.0f;}
		else if(frame_rate == 50){video_frame->frame_rate_N = 30000; video_frame->frame_rate_D = 1200;video_frame->picture_aspect_ratio = 16.0f/9.0f;}
		else if(frame_rate == 30){video_frame->frame_rate_N = 15000; video_frame->frame_rate_D = 1100;video_frame->picture_aspect_ratio = 16.0f/9.0f;}
		else if(frame_rate == 25){video_frame->frame_rate_N = 15000; video_frame->frame_rate_D = 1200;video_frame->picture_aspect_ratio = 16.0f/9.0f;}
		else {video_frame->frame_rate_N = frame_rate*1000; video_frame->frame_rate_D = 2000;}
		
	}else{
		
		video_frame->frame_format_type = NDIlib_frame_format_type_progressive;
		
		if(frame_rate == 60){video_frame->frame_rate_N = 60000; video_frame->frame_rate_D = 1100;video_frame->picture_aspect_ratio = 16.0f/9.0f;}
		else if(frame_rate == 50){video_frame->frame_rate_N = 60000; video_frame->frame_rate_D = 1200;video_frame->picture_aspect_ratio = 16.0f/9.0f;}
		else if(frame_rate == 30){video_frame->frame_rate_N = 30000; video_frame->frame_rate_D = 1100;video_frame->picture_aspect_ratio = 16.0f/9.0f;}
		else if(frame_rate == 25){video_frame->frame_rate_N = 30000; video_frame->frame_rate_D = 1200;video_frame->picture_aspect_ratio = 16.0f/9.0f;}
		else {video_frame->frame_rate_N = frame_rate*1000; video_frame->frame_rate_D = 1000;}
	}
	
	video_frame->line_stride_in_bytes =   video_frame->xres * sizeof(uint8_t) ;
	
	video_frame->timecode = 0;
	//not important metadata instruction yet implemented
	video_frame->p_metadata = "<Raspicam/>";
		
}


int main ( int argc,char **argv ) {		//main function
	
	int x_resolution, y_resolution, frame_rate;
	short int format_type;
	struct setting setting_camera;
	char set_camera_choice;
	double Frame_rate_send;
	
			//setup zone
			
			//setup the ndi	
			ClearScreen();
			setNDI( &x_resolution, &y_resolution, &frame_rate, &format_type);
			ClearScreen();
			
			//setup the camera (maby not needed, if not run in default)
			std::cout<<"open camera setup or running with default?	Y/N		";
			std::cin>>set_camera_choice;
			if(set_camera_choice == 'Y' || set_camera_choice == 'y'){ClearScreen(); setCamera( &setting_camera );ClearScreen();}
				else {ClearScreen(); setCameraDefault( &setting_camera);}
	
	//create a new istance of the camera
    raspicam::RaspiCam Camera;
	//initialize the camera istance with the assigned setting
    processCamera (Camera, x_resolution, y_resolution, frame_rate, setting_camera);
	
    //try to connecting to camera
    if ( !Camera.open() ) {
        std::cout<<"Error opening camera"<<std::endl;
        return -1;
		}else std::cout<<"Connected to camera "<<std::endl<<std::endl;
	//create a data storage on the size of the camera buffer
    unsigned char *data=new unsigned char[Camera.getImageBufferSize( )];
    
    //try to connecting to ndi
    if (!NDIlib_initialize()){	
		std::cout<<"Cannot run NDI."<<std::endl;
		return -1;
		} 
	//create a new istance of a source to initialize this source on the NDI network 
	NDIlib_send_create_t source_send;
		source_send.p_ndi_name = "Raspicam";
		source_send.clock_video = true;
	//create a new istance of a sender from this source on the NDI network	
	NDIlib_send_instance_t Pi_Sender = NDIlib_send_create(&source_send);
	if (!Pi_Sender){
		std::cout<<"Error creating NDI sender";
		return -1;
		} else std::cout<<"Connected to NDI"<<std::endl;
	//create the istance of the frame of streaming
	NDIlib_video_frame_v2_t video_frame;
	//initialize the streaming istance with the assigned setting	
	processNDI(&video_frame, x_resolution, y_resolution, frame_rate, format_type);
	
	if(format_type == 0){std<<"running in "<<x_resolution<<"x"<<y_resolution<<" at "frame_rate<<" interleaved frames per seconds"<<std::endl;}
	else {std<<"running in "<<x_resolution<<"x"<<y_resolution<<" at "frame_rate<<" progressive frames per seconds"<<std::endl;}
	
	//using <milliseconds> for the high res clock by chrono	
	Frame_rate_send = (1/frame_rate)*1000;
	
	
	//start the cicle of streaming, also calculating the time to do that
	while (true){
		
	auto Start_time = std::chrono::high_resolution_clock::now();	
		//grab the camera images and submitting on the data buffer
		Camera.grab();
		Camera.retrieve ( data );       
		//submitting the NDI buffer with the camera data buffer and send it
		video_frame.p_data = data;
		NDIlib_send_send_video_v2(Pi_Sender, &video_frame);
	
	auto Finish_time = std::chrono::high_resolution_clock::now();
		//check the time used to do a single task
		std::chrono::duration<double, std::milli> Counting_time = Finish_time - Start_time;
		//if the task is faster than the fram rate sleep this thread 
		if (Counting_time.count() < Frame_rate_send){
				int Sleeping_time = (int)Frame_rate_send - (int)Counting_time.count();
				std::this_thread::sleep_for (std::chrono::milliseconds(Sleeping_time));
		}
	
}
	//release camera data buffer
    	Camera.release();
	//destroy the ndi source
	NDIlib_destroy();
	

}



