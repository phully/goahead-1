<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<title>Hunda IPcam</title>
<link rel="stylesheet" type="text/css" href="./css/setting.css" />
<script language="JavaScript" src="./js/AJAXInteraction.js"></script>
<script language="JavaScript" src="./js/page.js"></script>
<script language="JavaScript" src="./js/setupLWT.js"></script>

<script>	
	function openSetting(num){
		if (document.getElementById("isOpened" + num).style.display == "block")
 		{
  			document.getElementById("isOpened" + num).style.display = "none";
  			document.getElementById("image" + num).src = "./img/list.gif";
 		}else{
  			document.getElementById("isOpened" + num).style.display = "block";
  			document.getElementById("image" + num).src = "./img/fold.gif";
		}
	}
</script>

</head>

<body>
<div id="formwrapper">
	<div id="redbar"></div>
	<div id="topbar">
		<div id="topleft"></div>
		<div id="topmiddle"></div>
		<div id="topright">	
		<div align='right'>
			<br>
			<span><b>
			<a name="" href="./home.asp">视频预览</a>
			<a name="" href="./network.asp">系统设置</a>
			</b></span></div>
		</div>
	</div>
	
	<div id="iphone4s">
	<!--just a wide red bar no details-->	
	</div>

	<div id="content">
	
<!--sidebar start-->
<div class="sidebar">
<div id="menu"> 

<div class="navhead">网络设置</div>                        
<div class="navcontent">
<ul>
<li class="menusub"><a href="./network.asp">有线网络</a></li>
<!--<li class="menusub"><a href="./wifi.asp">无线网络</a></li>
<li class="menusub"><a href="./pppoe.asp">PPPoE</a></li>
<li class="menusub"><a href="./ddns.asp">动态域名</a></li>-->
</ul>
</div>			
<div class="navhead">视频设置</div>                        
<div class="navcontent">
<ul>
<li class="menusub"><a href="./encode.asp">编码设置</a></li>
<li class="menusub"><a href="./image.asp">图像质量</a></li>
<li class="menusub"><a href="./osd.asp">OSD</a></li>
<li class="menusub"><a href="./privacy.asp">隐私遮蔽</a></li>
</ul>
</div>
<div class="navhead">其它设置</div>
<div class="navcontent">
<ul>
<li class="menusub"><a href="./time.asp">时间设置</a></li>
<li class="menusub"><a href="./alarm.asp">报警设置</a></li>
<li class="menusub"><a href="./user.asp">用户管理</a></li>
<li class="menusub"><a href="./upgrade.asp">维护升级</a></li>
<li class="menusub"><a href="./syslog.asp">系统日志</a></li>
</ul>
</div>	                                  
</div>
</div>
<!-- sidebar end-->
<div id="sideset">
<!--you code start-->
		<br>
			<h3>Note: Stream resolutions should be in the descending order.</h3>
			<form action="/goform/setEncode" method="post" id="setEncodeId">
			<fieldset>
			<legend>码流1</legend>
			<B>编码类型:</B>
			<select name = "type" id = "type" >
				<option value="off">OFF
				<option value="H264" selected>H.264
				<option value="mjpeg">MJPEG</select>
			<B>帧率: </B>
			<select name = "FPS" id = "FPS" >
				<option value = "60">60
				<option value = "30" selected>30
				<option value = "25">25
				<option value = "20">20
				<option value = "15">15
				<option value = "10">10
				<option value = "6">6
				<option value = "5">5
				<option value = "4">4
				<option value = "3">3
				<option value = "2">2
				<option value = "1">1
			</select>
			<B>分辨率: </B>
			<select name = "resolution" id="resolution" >
				<option value = "1080P" selected>1920*1080
				<option value = "720P" >1280*720
			</select>
			<br>
			<div id="img" style="cursor:hand" onclick="openSetting(1)"><image src="./img/list.gif" width="15" height="15" id = "image1"></div>
			<div id = "isOpened1" style="display:none">
			<fieldset><!-- start h264 field -->
			<legend>H.264</legend>
			
			<div>
			<label>I帧间隔(1-100):</label>
			<input type="text" name="IDR" id="IDR" value="" size="20" maxlength="30" />
			<br>
			</div>
		<div>
			<label>GOP模式:</label>
			<select name = "GOP" id = "GOP" >
				<option value = "simple">Simple
				<option value = "advanced">Advanced
			</select>
			<br>
		</div>
		<div>
			<label>比特率控制:</label>
			<select name = "bitratectrl" id="bitratectrl" width="20" >
				<option value = "cbr">CBR
				<option value = "vbr">VBR
				<option value = "cbrKQ">CBR(keep quality)
				<option value = "vbrKQ">VBR(keep quality)
			</select>
			<br>
		</div>
		<div>
			<label>平均比特率:</label>
			<input type="text" name="avgbitrate" id="avgbitrate" value="" size="20" maxlength="30" />
			<br>
		</div>
			</fieldset><!-- end h264 field -->
			<fieldset>
			<legend>MJPEG</legend>
			<div>
			<label>质量(0-100):</label>
			<input type="text" name="quality" id="quality" value="" size="20" maxlength="30" />
			</div>
			</fieldset>
			<label></label>
			&nbsp&nbsp<input type="button" name="submit" value="Apply" onclick = "return setEncode()"/>
			<input type="button" name="reset"  value="Cancel"/>
			
			</div>
			</fieldset>
			<div></div>
			
			</form>
<!--you code end-->

<!--you code 2-->
			<form action="/goform/setEncode" method="post" id="setEncodeId">
			<fieldset>
			<legend>码流2</legend>
			<B>编码类型:</B>
			<select name = "type" id = "type" >
				<option value="off">OFF
				<option value="H264" selected>H.264
				<option value="mjpeg">MJPEG</select>
			<B>帧率: </B>
			<select name = "FPS" id = "FPS" >
				<option value = "60">60
				<option value = "30" selected>30
				<option value = "25">25
				<option value = "20">20
				<option value = "15">15
				<option value = "10">10
				<option value = "6">6
				<option value = "5">5
				<option value = "4">4
				<option value = "3">3
				<option value = "2">2
				<option value = "1">1
			</select>
			<B>分辨率: </B>
			<select name = "resolution" id="resolution" >
				<option value = "1080P" selected>1920*1080
				<option value = "720P" >1280*720
			</select>
			<br>
			<div id="img" style="cursor:hand" onclick="openSetting(2)"><image src="./img/list.gif" width="15" height="15" id = "image2"></div>
			<div id = "isOpened2" style="display:none">
			<fieldset><!-- start h264 field -->
			<legend>H.264</legend>
			<div>
			<label>I帧间隔(1-100):</label>
			<input type="text" name="IDR" id="IDR" value="" size="20" maxlength="30" />
			<br>
			</div>
		<div>
			<label>GOP模式:</label>
			<select name = "GOP" id = "GOP" >
				<option value = "simple">Simple
				<option value = "advanced">Advanced
			</select>
			<br>
		</div>
		<div>
			<label>比特率控制:</label>
			<select name = "bitratectrl" id="bitratectrl" width="20" >
				<option value = "cbr">CBR
				<option value = "vbr">VBR
				<option value = "cbrKQ">CBR(keep quality)
				<option value = "vbrKQ">VBR(keep quality)
			</select>
			<br>
		</div>
		<div>
			<label>平均比特率:</label>
			<input type="text" name="avgbitrate" id="avgbitrate" value="" size="20" maxlength="30" />
			<br>
		</div>
			</fieldset><!-- end h264 field -->
			<fieldset>
			<legend>MJPEG</legend>
			<div>
			<label>质量(0-100):</label>
			<input type="text" name="quality" id="quality" value="" size="20" maxlength="30" />
			</div>
			</fieldset>
			<label></label>
			&nbsp&nbsp<input type="button" name="submit" value="Apply" onclick = "return setEncode()"/>
			<input type="button" name="reset"  value="Cancel"/>
			
			</div>
			</fieldset>
			<div></div>
			
			</form>
<!--you code 2 end-->
<!-- 3 -- start-->
			<form action="/goform/setEncode" method="post" id="setEncodeId">
			<fieldset>
			<legend>码流3</legend>
			<B>编码类型:</B>
			<select name = "type" id = "type" >
				<option value="off">OFF
				<option value="H264" selected>H.264
				<option value="mjpeg">MJPEG</select>
			<B>帧率: </B>
			<select name = "FPS" id = "FPS" >
				<option value = "60">60
				<option value = "30" selected>30
				<option value = "25">25
				<option value = "20">20
				<option value = "15">15
				<option value = "10">10
				<option value = "6">6
				<option value = "5">5
				<option value = "4">4
				<option value = "3">3
				<option value = "2">2
				<option value = "1">1
			</select>
			<B>分辨率: </B>
			<select name = "resolution" id="resolution" >
				<option value = "1080P" selected>1920*1080
				<option value = "720P" >1280*720
			</select>
			<br>
			<div id="img" style="cursor:hand" onclick="openSetting(3)"><image src="./img/list.gif" width="15" height="15" id = "image3"></div>
			<div id = "isOpened3" style="display:none">
			<fieldset><!-- start h264 field -->
			<legend>H.264</legend>
			<div>
			<label>I帧间隔(1-100):</label>
			<input type="text" name="IDR" id="IDR" value="" size="20" maxlength="30" />
			<br>
			</div>
		<div>
			<label>GOP模式:</label>
			<select name = "GOP" id = "GOP" >
				<option value = "simple">Simple
				<option value = "advanced">Advanced
			</select>
			<br>
		</div>
		<div>
			<label>比特率控制:</label>
			<select name = "bitratectrl" id="bitratectrl" width="20" >
				<option value = "cbr">CBR
				<option value = "vbr">VBR
				<option value = "cbrKQ">CBR(keep quality)
				<option value = "vbrKQ">VBR(keep quality)
			</select>
			<br>
		</div>
		<div>
			<label>平均比特率:</label>
			<input type="text" name="avgbitrate" id="avgbitrate" value="" size="20" maxlength="30" />
			<br>
		</div>
			</fieldset><!-- end h264 field -->
			<fieldset>
			<legend>MJPEG</legend>
			<div>
			<label>质量(0-100):</label>
			<input type="text" name="quality" id="quality" value="" size="20" maxlength="30" />
			</div>
			</fieldset>
			<label></label>
			&nbsp&nbsp<input type="button" name="submit" value="Apply" onclick = "return setEncode()"/>
			<input type="button" name="reset"  value="Cancel"/>
			
			</div>
			</fieldset>
			<div></div>
			
			</form>
<!-- 3 end-->
<!--4-->
			<form action="/goform/setEncode" method="post" id="setEncodeId">
			<fieldset>
			<legend>码流4</legend>
			<B>编码类型:</B>
			<select name = "type" id = "type" >
				<option value="off">OFF
				<option value="H264" selected>H.264
				<option value="mjpeg">MJPEG</select>
			<B>帧率: </B>
			<select name = "FPS" id = "FPS" >
				<option value = "60">60
				<option value = "30" selected>30
				<option value = "25">25
				<option value = "20">20
				<option value = "15">15
				<option value = "10">10
				<option value = "6">6
				<option value = "5">5
				<option value = "4">4
				<option value = "3">3
				<option value = "2">2
				<option value = "1">1
			</select>
			<B>分辨率: </B>
			<select name = "resolution" id="resolution" >
				<option value = "1080P" selected>1920*1080
				<option value = "720P" >1280*720
			</select>
			<br>
			
			<div id="img" style="cursor:hand" onclick="openSetting(4)"><image src="./img/list.gif" width="15" height="15" id = "image4"></div>
			<div id = "isOpened4" style="display:none">
			<fieldset><!-- start h264 field -->
			<legend>H.264</legend>
			<div>
			<label>I帧间隔(1-100):</label>
			<input type="text" name="IDR" id="IDR" value="" size="20" maxlength="30" />
			<br>
			</div>
		<div>
			<label>GOP模式:</label>
			<select name = "GOP" id = "GOP" >
				<option value = "simple">Simple
				<option value = "advanced">Advanced
			</select>
			<br>
		</div>
		<div>
			<label>比特率控制:</label>
			<select name = "bitratectrl" id="bitratectrl" width="20" >
				<option value = "cbr">CBR
				<option value = "vbr">VBR
				<option value = "cbrKQ">CBR(keep quality)
				<option value = "vbrKQ">VBR(keep quality)
			</select>
			<br>
		</div>
		<div>
			<label>平均比特率:</label>
			<input type="text" name="avgbitrate" id="avgbitrate" value="" size="20" maxlength="30" />
			<br>
		</div>
			</fieldset><!-- end h264 field -->
			<fieldset>
			<legend>MJPEG</legend>
			<div>
			<label>质量(0-100):</label>
			<input type="text" name="quality" id="quality" value="" size="20" maxlength="30" />
			</div>
			</fieldset>
			<label></label>
			&nbsp&nbsp<input type="button" name="submit" value="Apply" onclick = "return setEncode()"/>
			<input type="button" name="reset"  value="Cancel"/>
			
			</div>
			</fieldset>
			<div></div>
			
			</form>
<!--4 end-->
</div>
</div>
</div>
</body>
</html>
