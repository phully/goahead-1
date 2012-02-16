<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
	<title>Alarm Setting</title>
	<link rel="stylesheet" type="text/css" href="./css/setting.css" />
	<script language="JavaScript"  src="./js/AJAXInteraction.js"></script>
	<script type="text/javascript" src="./js/setup.js" ></script>

<script>	
	function openSetting(){
		if (document.getElementById("isOpened").style.display == "block")
 		{
  			document.getElementById("isOpened").style.display = "none";
  			document.getElementById("image1").src = "./img/list.gif";
 		}else{
  			document.getElementById("isOpened").style.display = "block";
  			document.getElementById("image1").src = "./img/fold.gif";
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
	
	<div id="topline">
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
<!--
<li class="menusub"><a href="./wifi.asp">无线网络</a></li>
<li class="menusub"><a href="./pppoe.asp">PPPoE</a></li>
<li class="menusub"><a href="./ddns.asp">动态域名</a></li>
-->
</ul>
</div>			
<div class="navhead">视频设置</div>                        
<div class="navcontent">
<ul>
<li class="menusub"><a href="./encode.asp">编码设置</a></li>
<li class="menusub"><a href="./image.asp">图像质量</a></li>
<li class="menusub"><a href="./osd.asp">OSD</a></li>
<li class="menusub"><a href="./privacy.asp">隐私遮蔽</a></li>
<!--<li class="menusub"><a href="./vinvout.asp">输入输出</a></li>-->
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
			<h3>报警输入设置及报警联动操作</h3>
			<form action="/goform/setEncode" method="post" id="setEncodeId">
			<fieldset>
			<legend>报警输入I</legend>
			<B>报警输入:</B>
			<input id="alarm1_on" type="radio" name="alarm1_active"  />On
			<input id="alarm1_off" type="radio" name="alarm1_active" checked=""/>Off
			<br>
			<input id="alarm1_record" type="checkbox"/>
			<B>视频录像:</B>
			<B>报警前:</B><input id="alarm1_recordstart" type="text" size="3"/><B>秒</B>
			<B>报警后:</B><input id="alarm1_recordstop" type="text" size="3"/><B>秒</B>
			<br>
			<input id="alarm1_capture" type="checkbox"/>
			<B>图像抓拍</B>
			<br>
			<input id="alarm1_osd" type="checkbox"/>
			<B>OSD显示:</B>
			<input id="alarm1_alarmosd" type="text" />
			<br>
			<input id="alarm1_alarmout" type="checkbox"/>
			<B>报警输出</B>
			<br>
			</fieldset>
			
			<fieldset>
			<legend>报警输入II</legend>
			<B>报警输入:</B>
			<input id="alarm2_on" type="radio" name="alarm2_active" />On
			<input id="alarm2_off" type="radio" name="alarm2_active" checked=""/>Off
			<br>
			<input id="alarm2_record" type="checkbox"/>
			<B>视频录像:</B>
			<B>报警前:</B><input id="alarm2_recordstart" type="text" size="3"/><B>秒</B>
			<B>报警后:</B><input id="alarm2_recordstop" type="text" size="3"/><B>秒</B>
			<br>
			<input id="alarm2_capture" type="checkbox"/>
			<B>图像抓拍</B>
			<br>
			<input id="alarm2_osd" type="checkbox"/>
			<B>OSD显示:</B>
			<input id="alarm2_alarmosd" type="text" />
			<br>
			<input id="alarm2_alarmout" type="checkbox"/>
			<B>报警输出</B>
			<br>
			</fieldset>
			</form>
			<br/>
<!--you code end-->
		
	</div>

	</div>
</div>
</body>
</html>