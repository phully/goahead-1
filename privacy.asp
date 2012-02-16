<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<title>Hunda IPcam</title>
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

<body onload="OnLoadActiveX(location.host, 0, 1, 0, 1)">
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
			<h3>设置视频源编码的隐私遮蔽</h3>
			<OBJECT CLASSID="CLSID:3BCDAA6A-7306-42FF-B8CF-BE5D3534C1E4" codebase="./activeX/ambaWeb.cab#version=1,0,0,32" WIDTH=480 HEIGHT=310 align="absmiddle" id="AmbaIPCmrWebPlugIn1">
										<PARAM NAME="_Version" VALUE="65536">
										<PARAM NAME="_ExtentX" VALUE="19045">
										<PARAM NAME="_ExtentY" VALUE="11478">
										<PARAM NAME="_StockProps" VALUE="0">
			</OBJECT>
			<fieldset>
			<legend>颜色</legend>
			<B>Y:</B>
			<input id="ColorY" type="text"/>
			<br>
			<B>U: </B>
			<input id="ColorU" type="text"/>
			<br>
			<B>V: </B>
			<input id="ColorV" type="text"/>
			<br>
			</fieldset>
			<fieldset width="50%">
			<legend>显示区域</legend>
			<table>
				<tr>
					<td align="right">X:</td>
					<td align="left"><input id="PosX" type="text" size="6"/></td>
					<td align="right">Y:</td>
					<td align="left"><input id="PosY" type="text" size="6"/></td>
				</tr>
				<tr>
					<td align="right">宽度:</td>
					<td align="left"><input id="Width" type="text" size="6"/></td>
					<td align="right">高度:</td>
					<td align="left"><input id="Height" type="text" size="6"/></td>
				</tr>
			</table>
			</fieldset>
			<input type="button" value="设置" onclick="setPrivacy('set')"/>
			<input type="button" value="去除" onclick="setPrivacy('del')"/>
			<input type="button" value="清空" onclick="setPrivacy('clear')"/>
			
			<br/>
<!--you code end-->
		
	</div>

	</div>
</div>
</body>
</html>