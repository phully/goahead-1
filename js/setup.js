
function OSDParam()
{
	this.mem = new Array(
		[ 's1_text1', 0 ],
		[ 's1_text1_width', 0 ],
		[ 's1_text1_size', 0 ],
		[ 's1_text1_high', 0 ],
		[ 's1_text1_startx', 0 ],
		[ 's1_text1_starty', 0 ],
		[ 's1_text1_outline', 0 ],
		[ 's1_text1_color', 0 ],
		[ 's1_text1_bold', 0 ],
		[ 's1_text1_italic', 0 ],
		[ 's1_text1_type', 0 ],
		[ 's1_text1_rotate', 0 ],
		
		[ 's1_text2', 0 ],
		[ 's1_text2_width', 0 ],
		[ 's1_text2_size', 0 ],
		[ 's1_text2_high', 0 ],
		[ 's1_text2_startx', 0 ],
		[ 's1_text2_starty', 0 ],
		[ 's1_text2_outline', 0 ],
		[ 's1_text2_color', 0 ],
		[ 's1_text2_bold', 0 ],
		[ 's1_text2_italic', 0 ],
		[ 's1_text2_type', 0 ],
		[ 's1_text2_rotate', 0 ],
		
		[ 's1_text3', 0 ],
		[ 's1_text3_width', 0 ],
		[ 's1_text3_size', 0 ],
		[ 's1_text3_high', 0 ],
		[ 's1_text3_startx', 0 ],
		[ 's1_text3_starty', 0 ],
		[ 's1_text3_outline', 0 ],
		[ 's1_text3_color', 0 ],
		[ 's1_text3_bold', 0 ],
		[ 's1_text3_italic', 0 ],
		[ 's1_text3_type', 0 ],
		[ 's1_text3_rotate', 0 ],
		
		[ 'text_clean', 0 ],
		[ 'text_judge', 0 ]
	);
	this.count = this.mem.length;
}

function PrivacyParam()
{
	this.mem = new Array(
		[ 'ColorY', 0 ],
		[ 'ColorU', 0 ],
		[ 'ColorV', 0 ],
		[ 'PosX', 0 ],
		[ 'PosY', 0 ],
		[ 'Width', 0 ],
		[ 'Height', 0 ]
	);
	this.count = this.mem.length;
}

function SysTimeParam()         //系统时间
{
	this.mem = new Array(
		[ 'SystemTime', 0 ]
	);
	this.count = this.mem.length;
}


function TimeSetParam()
{
	this.mem = new Array(
	  [ 'ClientTime',   0 ],         //本机时间
	  [ 'SystemTime',   0 ],         //系统时间   
	  [ 'NTPradiotime', 0 ],         //radotime
		[ 'NTPaddress',   0 ]          //NTPaddress
	);
	this.count = this.mem.length;
}



function EncodeParam()
{
	this.mem = new Array(
		[ 'type', 0 ],
		[ 'FPS', 0 ],
		[ 'resolution', 0 ],
		[ 'IDR', 0 ],
		[ 'GOP', 0 ],
		[ 'bitratectrl', 0 ],
		[ 'avgbitrate', 0 ],
		[ 'quality', 0 ]
	);
	this.count = this.mem.length;
}


function ImageParam()
{
	this.mem = new Array(
		[ 'Hue', 0 ],
		[ 'Bright', 0 ],
		[ 'Sharp', 0 ],
		[ 'Denoise', 0 ],
		[ 'Contrast', 0 ],
		[ 'Saturation', 0 ],
		[ 'Backlight', 0 ],
		[ 'DayNight', 0 ],
		[ 'Antiflicker', 0 ],
		[ 'Exposure', 0 ]
	);
	this.count = this.mem.length;
}

var g_OSDParam = new OSDParam();
var g_PrivacyParam = new PrivacyParam();

function get_page_data(Param)
{
	for (var i = 0; i < Param.count; i++) {
		var obj = document.getElementById(Param.mem[i][0]);
		if (obj != undefined) {
			switch (obj.type) {
			case "text" :
			case "select-one" :
				Param.mem[i][1] = obj.value;
				break;
			case "radio" :
				var radio = document.getElementsByName("n_" + Param.mem[i][0]);
				for (var j = 0; j < radio.length; j++) {
					if (radio[j].checked) {
						Param.mem[i][1] = radio[j].value;
					}
				}
				break;
			case "checkbox" :
				if (obj.checked) {
					Param.mem[i][1] = 1;
				} else {
					Param.mem[i][1] = 0;
				}
				break;
			default :
				alert("Unknown obj name : [" + Param.mem[i][0] + "], type is : ["+obj.type+"].\n");
				break;
			}
		}
	}
}

function set_page_data(Param, responseXML)
{
	var i;
	for (i = 0; i < Param.count; i++) {
		var val = responseXML.getElementsByTagName(Param.mem[i][0])[0].childNodes[0].nodeValue;
		var obj = document.getElementById(Param.mem[i][0]);
		if (obj != undefined) {
			switch (obj.type) {
			case "text" :
			case "select-one" :
				obj.value = val;
				break;
			case "radio" :
				var radio = document.getElementsByName("n_" + Param.mem[i][0]);
				for (var j = 0; j < radio.length; j++) {
					if (val == radio[j].value) {
						radio[j].checked = true;
					} else {
						radio[j].checked = false;
					}
				}
				break;
			case "checkbox" :
				if (val == 1) {
					obj.checked = true;
				} else {
					obj.checked = false;
				}
				break;
			default :
				alert("Unknown type is : ["+obj.type+"].\n");
				break;
			}
		}
	}
}

function Pack()
{
	this.mem = '';
}

function add_to_pack(pack, name, value)
{
	pack.mem += '&' + name + '=' + encodeURIComponent(value);
}

function setOSD()
{
	try {
		var i, content;
		var new_OSDParam = new OSDParam();
		get_page_data(new_OSDParam);
		var OSDPack = new Pack();
		for (i = 0; i < new_OSDParam.count; i++) {
			if (new_OSDParam.mem[i][1] != g_OSDParam.mem[i][1]) {
					add_to_pack(OSDPack, new_OSDParam.mem[i][0], new_OSDParam.mem[i][1]);
			}
		}

		if (OSDPack.mem == '') {
			alert("Nothing changed");
			return;
		}

		//showStatus("Setting OSD parameters ....");
		var url = "/goform/osd?";
		var ai = new AJAXInteraction(url, display);
		
		var postData = "Operate=set";
		postData += OSDPack.mem;
		
		ai.doPost(postData);
	} catch (error) {
		alert(error);
	}

	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseXML.documentElement;
	}
}

function getOSD()
{
	try {
		//showStatus("Getting OSD parameters ....");
		var url = "/goform/osd?";
		var ai = new AJAXInteraction(url, display);
		var postData = '';
		postData = "Operate=get";
		ai.doPost(postData);
	} catch (error) {
		alert(error);
	}

	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseXML.documentElement;
		set_page_data(g_OSDParam, xmlDoc);
	}
}


function setPrivacy(opt)
{
	try {
		var i, content;
		var new_PrivacyParam = new PrivacyParam();
		get_page_data(new_PrivacyParam);
		var PrivacyPack = new Pack();
		for (i = 0; i < new_PrivacyParam.count; i++) {
			if (new_PrivacyParam.mem[i][1] != g_PrivacyParam.mem[i][1]) {
				if (new_PrivacyParam.mem[i][0].substring(2) != "_text") {
					add_to_pack(PrivacyPack, new_PrivacyParam.mem[i][0], new_PrivacyParam.mem[i][1]);
				} else {
					content = '"' + new_PrivacyParam.mem[i][1] + '"';
					add_to_pack(PrivacyPack, new_PrivacyParam.mem[i][0], content);
				}
			}
		}

		if (PrivacyPack.mem == '') {
			alert("Nothing changed");
			return;
		}

		//showStatus("Setting Privacy parameters ....");
		var url = "/goform/privacy?";
		var ai = new AJAXInteraction(url, display);
		
		var postData = "Operate=" + opt;
		postData += PrivacyPack.mem;
		
		ai.doPost(postData);
	} catch (error) {
		alert(error);
	}

	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseXML.documentElement;
	}
}

function getPrivacy()
{
	try {
		//showStatus("Getting Privacy mask parameters ....");
		var url = "/goform/privacy?";
		var ai = new AJAXInteraction(url, display);
		var postData = '';
		postData = "Operate=get";
		ai.doPost(postData);
	} catch (error) {
		alert(error);
	}

	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseXML.documentElement;
		set_page_data(g_OSDParam, xmlDoc);
	}
}

function Reboot()
{
	try {
		var url = "/goform/system?";
		var ai = new AJAXInteraction(url, display);
		var postData = '';
		postData = "Operate=reboot";
		ai.doPost(postData);
		ShowRebootInfo();
	} catch (error) {
		alert(error);
	}

	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseText;
		ShowRebootInfo();
	}
}

var nTime = 90;
var clock;

function ShowRebootInfo() 
{
	if (0 >= nTime) {
		clearTimeout(clock);
		document.location.href = "./upgrade.asp";
		return;
	}
	
	var str="<h3>系统将在 " + nTime + " 秒后重启完成 ......";
	$('#sideset').html(str);
  clock = setTimeout("ShowRebootInfo()", 1000);
  nTime--;
}

var g_SysTimeParam = new SysTimeParam();
function getSysTime()
{
try {
		var url = "/goform/SysTime?";
		var ai = new AJAXInteraction(url, display);
		var postData = '';
		postData = "Operate=get";
		ai.doPost(postData);
	} catch (error) {
		alert(error);
	}

	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseXML.documentElement;
		set_page_data(g_SysTimeParam, xmlDoc);
	}
}



var g_TimeSetParam = new TimeSetParam();
function getTimeSet()
{
	try {
		var url = "/goform/FTimeSet?";
		var ai = new AJAXInteraction(url, display);
		var postData = '';
		postData = "Operate=get";
		ai.doPost(postData);
	} catch (error) {
		alert(error);
	}

	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseXML.documentElement;
		set_page_data(g_TimeSetParam, xmlDoc);
	}
}

function setTimeSet()
{
	try {
		var i, content;
		var new_TimeSetParam = new TimeSetParam();
		get_page_data(new_TimeSetParam);
		var NTPPack = new Pack();
		for (i = 0; i < new_TimeSetParam.count; i++) {
			if (new_TimeSetParam.mem[i][1] != g_TimeSetParam.mem[i][1]) {
				if (new_TimeSetParam.mem[i][0].substring(2) != "_text") {
					add_to_pack(NTPPack, new_TimeSetParam.mem[i][0], new_TimeSetParam.mem[i][1]);
				} else {
					content = '"' + new_TimeSetParam.mem[i][1] + '"';
					add_to_pack(NTPPack, new_TimeSetParam.mem[i][0], content);
				}
			}
		}

		if (NTPPack.mem == '') {
			alert("Nothing changed");
			return;
		}

		var url = "/goform/FTimeSet?";
		var ai = new AJAXInteraction(url, display);
		
		var postData = "Operate=set";
		postData += NTPPack.mem;
		
		ai.doPost(postData);
	} catch (error) {
		alert(error);
	}
	
	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseText;
	}
}


var g_EncodeParam = new EncodeParam();
function setEncode()
{
	try {
		var i, content;
		var new_EncodeParam = new EncodeParam();
		get_page_data(new_EncodeParam);
		var EncodePack = new Pack();
		for (i = 0; i < new_EncodeParam.count; i++) {
			if (new_EncodeParam.mem[i][1] != g_EncodeParam.mem[i][1]) {
				if (new_EncodeParam.mem[i][0].substring(2) != "_text") {
					add_to_pack(EncodePack, new_EncodeParam.mem[i][0], new_EncodeParam.mem[i][1]);
				} else {
					content = '"' + new_EncodeParam.mem[i][1] + '"';
					add_to_pack(EncodePack, new_EncodeParam.mem[i][0], content);
				}
			}
		}
		if (EncodePack.mem == '') {
			alert("Nothing changed");
			return;
		}
		
		var url = "/goform/EncodeSet?";
		var ai = new AJAXInteraction(url, display);
		
		var postData = "Operate=set";
		postData += EncodePack.mem;
		ai.doPost(postData);
	} catch (error) {
		alert(error);
	}

	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseXML.documentElement;
	}
}

function getTimeSet()
{
	try {
		var url = "/goform/TimeSet?";
		var ai = new AJAXInteraction(url, display);
		var postData = '';
		postData = "Operate=get";
		ai.doPost(postData);
	} catch (error) {
		alert(error);
	}

	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseXML.documentElement;
		set_page_data(g_NetworkParam, xmlDoc);
	}
}


function getEncode()
{
	try {;
		var url = "/goform/EncodeSet?";
		var ai = new AJAXInteraction(url, display);
		var postData = '';
		postData = "Operate=get";
		ai.doPost(postData);
	} catch (error) {
		alert(error);
	}

	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseXML.documentElement;
		set_page_data(g_EncodeParam, xmlDoc);
	}
}

var g_ImageParam = new ImageParam();
function setImage()
{
	try {
		var i, content;
		var new_ImageParam = new ImageParam();
		get_page_data(new_ImageParam);
		var IMGPack = new Pack();
		for (i = 0; i < new_ImageParam.count; i++) {
			if (new_ImageParam.mem[i][1] != g_ImageParam.mem[i][1]) {
				if (new_ImageParam.mem[i][0].substring(2) != "_text") {
					add_to_pack(IMGPack, new_ImageParam.mem[i][0], new_ImageParam.mem[i][1]);
				} else {
					content = '"' + new_ImageParam.mem[i][1] + '"';
					add_to_pack(IMGPack, new_ImageParam.mem[i][0], content);
				}
			}
		}

		if (IMGPack.mem == '') {
			alert("Nothing changed");
			return;
		}

		//showStatus("Setting OSD parameters ....");
		var url = "/goform/ImageSet?";
		var ai = new AJAXInteraction(url, display);
		
		var postData = "Operate=set";
		postData += IMGPack.mem;
		
		ai.doPost(postData);
	} catch (error) {
		alert(error);
	}

	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseText;
		if(xmlDoc == "0"){
			document.getElementById("saveok").innerHTML='保存成功!';
 			setTimeout("clean()",3000);
		}else{
			document.getElementById("saveok").innerHTML='保存失败!';
 			setTimeout("clean()",3000);
		}
	}
	
}
function clean() {
	document.getElementById("saveok").innerHTML='';
}

function getImage()
{
	try {
		var url = "/goform/ImageSet?";
		var ai = new AJAXInteraction(url, display);
		var postData = '';
		postData = "Operate=get";
		ai.doPost(postData);
	} catch (error) {
		alert(error);
	}

	function display(XmlHttpRequest) {
		var xmlDoc=XmlHttpRequest.responseXML.documentElement;
		var val;
		set_page_data(g_ImageParam, xmlDoc);
		for (i = 0; i < g_ImageParam.count-4; i++)
		{
			val = xmlDoc.getElementsByTagName(g_ImageParam.mem[i][0])[0].childNodes[0].nodeValue;
			A_SLIDERS[i].f_setValue(val);
		}
	}
}
