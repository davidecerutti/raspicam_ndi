# raspicam_ndi

raspicamndi use a open source raspicam libraries, This library allows to use the Raspberry Pi Camera under BSD License, project started by the AVA research group
#


raspicamndi version history
#
alpha testing
	using raspicam librarie and first basic version of the raspistill over ndi


raspicamndi - V0.1.0 
	is a pre release version where all the comands are editable only before compiling, in the code

		+bug report:	error in the whyle cicle for the timing of std::chrono::sleep_thread
		+bug report:	difficult usages: commands only in the code
		+bug report:	error in YUV420 sent by NDI (shifting down UV channels line = xres * sizeof(unit8) )


raspicamndi - V0.2.0 
	is a pre release verion, including a benchmark test for devices

		-fixed bug:	error in the whyle cicle for the timing of std::chrono::sleep_thread(V0.1.0)
		.bug report:	difficult usages: commands only in the code
		.bug report:	error in YUV420 sent by NDI (shifting down UV channels line = xres * sizeof(unit8) )

