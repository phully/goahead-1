<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<title>Hunda IPcam</title>
<link rel="stylesheet" type="text/css" href="./css/setting.css" />
<script language="JavaScript" src="./js/AJAXInteraction.js"></script>
<script language="JavaScript" src="./js/page.js"></script>

<script language="javascript"> 
	function checkIP() 
	{		
		var exp=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/; 
		obj=document.getElementById("Addr").value 
		var reg1 = obj.match(exp); 
		obj=document.getElementById("Mask").value
		var reg2 = obj.match(exp); 
		obj=document.getElementById("Gate").value
		var reg3 = obj.match(exp);
		if(reg1==null){
			alert("IP地址输入不合法！");
			return false;
		}else if(reg2==null){
			alert("子网掩码输入不合法！");
			return false;
		}else if(reg3==null){
			alert("默认网关输入不合法！");
			return false;
		}else{
			alert("修改成功！");
			return true;
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
		
		<!--start-->
<form action="/goform/NetworkSet" method="post">
	
<fieldset>
<legend>网络设置</legend>
<br>
<div>
<label>网络地址:</label>
<input type="text" name="Address" id="Addr" size="20" maxlength="16" value = "<%MakeDispAddr();%>" />
<br/>
</div>
<div>
<label>子网掩码:</label>
<input type="text" name="Submask" id="Mask" size="20" maxlength="16" value = "<%MakeDispMask();%>"/>
<br/>
</div>
<div>
<label>默认网关:</label>
<input type="text" name="Gateway" id="Gate" size="20" maxlength="16" value = "<%MakeDispGate();%>"/>
<br/>
</div>
<div>
<label></label>
<input name="setIP" type="submit" value="确定"  onclick="return checkIP()"/>
<input name="reset" type="reset"  value="重置" />
</div>
</fieldset>
</form>
		<!--end-->
		
	</div>

	</div>
</div>
</body>
</html>