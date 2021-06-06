var show_raspicam_controll = 0;


function show_control_function(){
  if(show_raspicam_controll == 0){
    document.getElementById("camerasettings").style.visibility = 'visible';
    document.getElementById("show_control").innerHTML = "HIDE CAMERA CONTROL";
    var id = null;
    var elem = document.getElementById("camerasettings");
    var pos = 50;
    clearInterval(id);
    id = setInterval(frame, 1);
    function frame() {
      if (pos == 250) {
        clearInterval(id);
        } else {
        pos = pos + 2.5;
        elem.style.left = pos + 'px';
        }
      }
    show_raspicam_controll = 1;
    }

  else if(show_raspicam_controll == 1){
    var id = null;
    var elem = document.getElementById("camerasettings");
    var pos = 200;
    clearInterval(id);
    id = setInterval(frame, 1);
    function frame() {
      if (pos == 0) {
        clearInterval(id);
        } else {
        pos = pos - 5;
        elem.style.left = pos + 'px';
        }
      }
    document.getElementById("camerasettings").style.visibility = 'hidden';
    document.getElementById("show_control").innerHTML = "SHOW CAMERA CONTROL";
    show_raspicam_controll = 0;
    }

}

function show_control_multicast(){
    if (document.getElementById("multicast_enable").checked == true){
      document.getElementById("multicast_TTL").disabled = false;
      document.getElementById("multicast_IP").disabled = false;
      document.getElementById("multicast_MASK").disabled = false;
    } else {
      document.getElementById("multicast_TTL").disabled = true;
      document.getElementById("multicast_IP").disabled = true;
      document.getElementById("multicast_MASK").disabled = true;
    }
}

function show_control_discovery(){
  if (document.getElementById("discovery_enable").checked == true){
    document.getElementById("discovery_server").disabled = false;
  } else {
    document.getElementById("discovery_server").disabled = true;
  }
}



  var sli_brightness = document.getElementById("sli_brightness");
  var val_brightness = document.getElementById("val_brightness");
  val_brightness.innerHTML = sli_brightness.value;
    sli_brightness.oninput = function() {
    val_brightness.innerHTML = this.value;
    }

  var sli_sharpness = document.getElementById("sli_sharpness");
  var val_sharpness = document.getElementById("val_sharpness");
  val_sharpness.innerHTML = sli_sharpness.value;
    sli_sharpness.oninput = function() {
    val_sharpness.innerHTML = this.value;
  }

  var sli_contrast = document.getElementById("sli_contrast");
  var val_contrast = document.getElementById("val_contrast");
  val_contrast.innerHTML = sli_contrast.value;
    sli_contrast.oninput = function() {
    val_contrast.innerHTML = this.value;
  }

  var sli_Saturation = document.getElementById("sli_Saturation");
  var val_Saturation = document.getElementById("val_Saturation");
  val_Saturation.innerHTML = sli_Saturation.value;
    sli_Saturation.oninput = function() {
    val_Saturation.innerHTML = this.value;
  }

  var sli_ShutterSpeed = document.getElementById("sli_ShutterSpeed");
  var val_ShutterSpeed = document.getElementById("val_ShutterSpeed");
  val_ShutterSpeed.innerHTML = sli_ShutterSpeed.value + " μs";
    sli_ShutterSpeed.oninput = function() {
    val_ShutterSpeed.innerHTML = this.value + " μs";
  }

  var sli_ISO = document.getElementById("sli_ISO");
  var val_ISO = document.getElementById("val_ISO");
  val_ISO.innerHTML = sli_ISO.value;
    sli_ISO.oninput = function() {
    val_ISO.innerHTML = this.value;
  }

  var sli_ExposureCompensation = document.getElementById("sli_ExposureCompensation");
  var val_ExposureCompensation = document.getElementById("val_ExposureCompensation");
  val_ExposureCompensation.innerHTML = sli_ExposureCompensation.value;
    sli_ExposureCompensation.oninput = function() {
    val_ExposureCompensation.innerHTML = this.value;
  }

  var sli_AWB_R = document.getElementById("sli_AWB_R");
  var val_AWB_R = document.getElementById("val_AWB_R");
  val_AWB_R.innerHTML = sli_AWB_R.value;
    sli_AWB_R.oninput = function() {
    val_AWB_R.innerHTML = this.value;
    colorbox()
  }

  var sli_AWB_G = document.getElementById("sli_AWB_G");
  var val_AWB_G = document.getElementById("val_AWB_G");
  val_AWB_G.innerHTML = sli_AWB_G.value;
    sli_AWB_G.oninput = function() {
    val_AWB_G.innerHTML = this.value;
    colorbox()
  }

  var sli_AWB_B = document.getElementById("sli_AWB_B");
  var val_AWB_B = document.getElementById("val_AWB_B");
  val_AWB_B.innerHTML = sli_AWB_B.value;
    sli_AWB_B.oninput = function() {
    val_AWB_B.innerHTML = this.value;
    colorbox()
  }

function colorbox(){
  var Red, Green, Blue;
  Red = (255 - 31.25 * sli_AWB_R.value )
  Green = (255 - 31.25 * sli_AWB_G.value )
  Blue = (255 - 31.25 * sli_AWB_B.value )
  document.getElementById("box").style.background = "rgb("+ Red + ","+ Green + ","+ Blue + ")"
}

colorbox();

//format of the NDI stream
var resolution = document.getElementById("resolution");
var framerate = document.getElementById("framerate");
var formatype = document.getElementById("formatype");

var format = document.getElementById("format");
format.innerHTML = resolution.value +" "+ framerate.value + formatype.value;

resolution.oninput = function() {
format.innerHTML = this.value +" "+ framerate.value + formatype.value;
}

framerate.oninput = function() {
format.innerHTML = resolution.value +" "+ this.value + formatype.value;
}

formatype.oninput = function() {
format.innerHTML = resolution.value +" "+ framerate.value + this.value;
}
