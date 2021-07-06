const express = require('express')
const app = express()
const bodyParser = require('body-parser')
const port = 80;
const fs = require('fs');
const execFile = require('child_process').execFile;
const expressLayouts = require('express-ejs-layouts');


app.use(bodyParser());
app.use(expressLayouts);
app.use(express.static('public'))
app.use('/css', express.static(__dirname +'public/css'))
app.use('/js', express.static(__dirname +'public/js'))


app.set('views', './views')
app.set('view engine', 'ejs')

let date_ob = new Date();
var live_track = 0;
let tally_visibility, liveprod_button;

app.get('', (req, res) => {
	fs.readFile("CameraSetting.JSON", "UTF8", (err, preloadJSON)=>{
		if(err) { return console.error(err); }
		console.log("pre-loading: " + preloadJSON + "\n");
		var preloadOBJ = JSON.parse(preloadJSON);

		if(preloadOBJ.multicast_enable == 'on'){
			preloadOBJ.multicast_enable = 'checked';}

		if(preloadOBJ.discovery_enable == 'on'){
			preloadOBJ.discovery_enable = 'checked';}

		var sel_480, sel_720, sel_1080;
		switch (preloadOBJ.resolution){
			case '480':
				sel_480 = 'selected';
			break;
			case '720':
				sel_720 = 'selected';
			break;
			case '1080':
				sel_1080 = 'selected';
			break;
		}

		var sel_25, sel_30, sel_50, sel_60;
		switch (preloadOBJ.framerate){
			case '25':
				sel_25 = 'selected';
			break;
			case '30':
				sel_30 = 'selected';
			break;
			case '50':
				sel_50 = 'selected';
			break;
			case '60':
				sel_60 = 'selected';
			break;
		}

		var sel_p, sel_i;
		switch (preloadOBJ.formatype){
			case 'p':
				sel_p = 'selected';
			break;
			case 'i':
				sel_i = 'selected';
			break;
		}

		if(live_track == 0 && live_track != 1) {
			 tally_visibility = "none";
			 liveprod_button = "START LIVE PRODUCTION";
		}
		if(live_track == 1 && live_track != 0) {
			 tally_visibility = "inline-block";
			 liveprod_button = "STOP LIVE PRODUCTION";
		}


	res.render('index',{preloadOBJ, sel_480, sel_720, sel_1080, sel_25, sel_30, sel_50, sel_60, sel_p, sel_i, tally_visibility, liveprod_button});
	console.log("LOG: " + date_ob.getHours()+":"+date_ob.getMinutes()+":"+date_ob.getSeconds() +" connections in entrance from " + req.ip + "\n");
	});
})

app.post('', (req, res) => {

	if (live_track == 0 && live_track != 1){

			var requestJSON = (JSON.stringify(req.body));
			var requestOBJ = JSON.parse(requestJSON);
			console.log(requestOBJ);

			console.log("LOG: Submitted request");

			var FileFormat = requestOBJ.resolution +"\n"+
						 	 requestOBJ.framerate +"\n"+
							 requestOBJ.formatype;

			var FileCamera = requestOBJ.Brightness +"\n"+
							 requestOBJ.Sharpness +"\n"+
							 requestOBJ.Contrast +"\n"+
							 requestOBJ.Saturation +"\n"+
							 requestOBJ.ShutterSpeed +"\n"+
							 requestOBJ.ISO +"\n"+
							 requestOBJ.ExposureCompensation +"\n"+
							 requestOBJ.AWB_R +"\n"+ requestOBJ.AWB_G;

			var FileStream = FileFormat + "\n\n" + FileCamera;

			fs.writeFile("CameraSetting.txt", FileStream , function(err) {
				if(err) { return console.error(err); }
				console.log("LOG: CameraSetting written");
			})

			fs.writeFile("CameraSetting.JSON", requestJSON , function(err) {
				if(err) { return console.error(err); }
				console.log("LOG: CameraSetting.JSON written");
			})

			fs.readFile('ndiconfigmodel.JSON', 'utf-8', (err, ndiconfigData)=>{
				if(err) {return console.error(err); }
				var ndiconfigOBJ = JSON.parse(ndiconfigData);
				
				if (requestOBJ.discovery_enable == 'on'){
					ndiconfigOBJ.ndi.networks.discovery = requestOBJ.discovery_server;}
				else{
					ndiconfigOBJ.ndi.networks.discovery = "";}

				if (requestOBJ.multicast_enable == 'on'){
					ndiconfigOBJ.ndi.multicast.send.enable = "true";
					ndiconfigOBJ.ndi.multicast.send.ttl = requestOBJ.multicast_TTL;
					ndiconfigOBJ.ndi.multicast.send.netmask = requestOBJ.multicast_MASK;
					ndiconfigOBJ.ndi.multicast.send.netprefix = requestOBJ.multicast_IP;
					}
				else{
					ndiconfigOBJ.ndi.multicast.send.enable = "false";
					ndiconfigOBJ.ndi.multicast.send.ttl = "";
					ndiconfigOBJ.ndi.multicast.send.netmask = "";
					ndiconfigOBJ.ndi.multicast.send.netprefix = "";
					}
					

				console.log(ndiconfigOBJ);

				var ndiconfigJSON = JSON.stringify(ndiconfigOBJ);
				
				fs.writeFile('ndiconfig.JSON', ndiconfigJSON , function(err) {
					if(err) { return console.error(err); }
					console.log("LOG: ndiconfig.JSON written");
				})
				
			})
			

		//execFile('./test.exe');		//inserire il main.exe in c++ di raspicamndi

		live_track = 1;
		tally_visibility = "inline-block";
		liveprod_button = "STOP LIVE PRODUCTION";

	}

		else if(live_track == 1 && live_track != 0){

		//execFile('./test.exe');		//inserire il clear.exe in c++ di raspicamndi per chiudere e pulire il buffer

		live_track = 0;
		tally_visibility = "none";
		liveprod_button = "START LIVE PRODUCTION";
	}


	fs.readFile("CameraSetting.JSON", "UTF8", (err, preloadJSON)=>{
		if(err) { return console.error(err); }
		console.log("pre-loading: " + preloadJSON + "\n");
		var preloadOBJ = JSON.parse(preloadJSON);

		if(preloadOBJ.multicast_enable == 'on'){
			preloadOBJ.multicast_enable = 'checked';}

		if(preloadOBJ.discovery_enable == 'on'){
			preloadOBJ.discovery_enable = 'checked';}

		var sel_480, sel_720, sel_1080;
		switch (preloadOBJ.resolution){
			case '480':
				sel_480 = 'selected';
			break;
			case '720':
				sel_720 = 'selected';
			break;
			case '1080':
				sel_1080 = 'selected';
			break;
		}

		var sel_25, sel_30, sel_50, sel_60;
		switch (preloadOBJ.framerate){
			case '25':
				sel_25 = 'selected';
			break;
			case '30':
				sel_30 = 'selected';
			break;
			case '50':
				sel_50 = 'selected';
			break;
			case '60':
				sel_60 = 'selected';
			break;
		}

		var sel_p, sel_i;
		switch (preloadOBJ.formatype){
			case 'p':
				sel_p = 'selected';
			break;
			case 'i':
				sel_i = 'selected';
			break;
		}

	res.render('index',{preloadOBJ, sel_480, sel_720, sel_1080, sel_25, sel_30, sel_50, sel_60, sel_p, sel_i, tally_visibility, liveprod_button});
});

})



app.listen(port, ()=> console.info('server is listening on port 80'))
