/////////////////////////////////////////////////////////////////////
//
// AJAXInteraction.js
//
// History:
//	2010/02/28 - [Yi Zhu] Created this file
//
// Copyright (C) 2007 - 2010, Ambarella, Inc.
//
// All rights reserved. No Part of this file may be reproduced, stored
// in a retrieval system, or transmitted, in any form, or by any means,
// electronic, mechanical, photocopying, recording, or otherwise,
// without the prior consent of Ambarella, Inc.
//
/////////////////////////////////////////////////////////////////////

function AJAXInteraction(url, callback) {
	var request = init();
	request.onreadystatechange = processRequest;

	// Initialization
	function init() {
		var r = false;
		try { // Firefox-like browsers
			r = new XMLHttpRequest();
		} catch (ie) {
			try { // Microsoft IE
				r = new ActiveXObject("Msxml2.XMLHTTP");
			} catch (other_microsoft) {
				try { // Other browsers and versions of browsers
					r = new ActiveXObject("Microsoft.XMLHTTP");
				} catch (failed) {
					r = false;
				}
			}
		}

		// Error check and processing
		if (!r) {
			alert("You can not use this system.");
		}

		return r;
	}

	// Request processing
	function processRequest() {
		if (request.readyState == 4) {
			if (request.status == 200) {
				if (callback) callback(request);
			}
		}
	}

	function addstamp(url) {
		var surl = url;
		if (surl.search(/\?/) < 0) {
			surl = surl + "?";
		} else {
			surl = surl + "&";
		}
		surl = surl + "stamp=" + Math.random();

		return surl;
	}

	// HTTP GET request
	this.doGet = function() {
		try {
			request.open("GET", addstamp(url), true);
			request.send(null);
		} catch (error) {
			alert(error);
		}
	}

	this.doGetSyn = function() {
		request.open("GET", addstamp(url), false);
		request.send(null);
		if (request.status == 200) {
			if (callback) callback(request);
		}
	}

	// HTTP POST request
	this.doPost = function(body) {
		request.open("POST", addstamp(url), true);
		request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded; charset=utf-8");
		request.send(body);
	}

	// HTTP POST request
	this.doPostSyn = function(body) {
		request.open("POST", addstamp(url), false);
		request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded; charset=utf-8");
		request.send(body);
		if (request.status == 200) {
			if (callback) callback(request);
		}
	}

}


function PlayVideo()
{
	if (window.ActiveXObject) {
		try {
			document.getElementById("AmbaIPCmrWebPlugIn1").Play();
		} catch (e) {
			alert(e);
		}
	}
}

function StopVideo()
{
	if (window.ActiveXObject) {
		try {
			document.getElementById("AmbaIPCmrWebPlugIn1").Stop();
		} catch (e) {
			alert(e);
		}
	}
}

function OnLoadActiveX(hostname, stream_id, recvType, statSize, showStat)
{
	if (window.ActiveXObject) {
		try {
			var activeX = document.getElementById("AmbaIPCmrWebPlugIn1");
			if (activeX.SetRecvType(recvType)) {
				activeX.SetHostname(hostname);
				activeX.SetStreamId(stream_id);
				activeX.SetStatWindowSize(statSize);
				activeX.ShowStat(showStat);
			} else {
				alert("set wrong client type!");
				return;
			}
		} catch (e) {
			alert(e);
			return; 
		}
	}
	PlayVideo(stream_id);
}

function SnapShot()
{
	if (window.ActiveXObject) {
		try {
			$("AmbaIPCmrWebPlugIn1").GetSnapShot();
		} catch (e) {
			alert(e);
		}
	}
}

function SetFormat(format)
{
	if (window.ActiveXObject) {
		try {
			$("AmbaIPCmrWebPlugIn1").SetSnapShotFormat(parseInt(format));
		} catch (e) {
			alert(e);
		}
	}
}

function SetNumber(num)
{
	if (window.ActiveXObject) {
		try {
			$("AmbaIPCmrWebPlugIn1").SetSnapShotNumber(parseInt(num));
		} catch (e) {
			alert(e);
		}
	}
}