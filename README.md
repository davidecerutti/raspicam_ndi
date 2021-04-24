# raspicam_ndi

raspicamndi use a open source raspicam libraries, This library allows to use the Raspberry Pi Camera under BSD License, project started by the AVA research group. http://www.uco.es/investiga/grupos/ava/node/40

!!! IMPORTANT : in some version of Raspbian this library is just maked, if is not present please get it from https://github.com/cedricve/raspicam
#


# raspicamndi version history


raspicamndi - V1.0.0
	is the first released version, now with a command line interface to set up the stream an camera
	
		*new feature:	new command line interface, all the usage of the raspicamndi implemented as UI
		-fixed bug:	cleaned al the code coming from alfa testing
		+bug report:	no controls in incorrect value in setndi
		+bug report:	no controls in incorrect values in set camera
		.bug report:	error in YUV420 sent by NDI (shifting down UV channels line = xres * sizeof(unit8))
		
		V1.0.2 -fixed video type single setting error message even with acceptable value
		V1.0.3 -fixed setting camera lack for not setted value in the struct using default values
		
raspicamndi - V0.2.0 
	is a pre release verion, including a benchmark test for devices

		-fixed bug:	error in the whyle cicle for the timing of std::chrono::sleep_thread(V0.1.0)
		.bug report:	difficult usages: commands only in the code
		.bug report:	error in YUV420 sent by NDI (shifting down UV channels line = xres * sizeof(unit8))

raspicamndi - V0.1.0 
	is a pre release version where all the comands are editable only before compiling, in the code

		+bug report:	error in the whyle cicle for the timing of std::chrono::sleep_thread
		+bug report:	difficult usages: commands only in the code
		+bug report:	error in YUV420 sent by NDI (shifting down UV channels line = xres * sizeof(unit8))

alpha testing
	using raspicam librarie and first basic version of the raspistill over ndi

