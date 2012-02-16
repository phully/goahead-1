<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<title>Hunda IPcam</title>
<link rel="stylesheet" type="text/css" href="./css/setting.css" />
<script language="JavaScript" src="./js/AJAXInteraction.js"></script>
<script language="JavaScript" src="./js/slider.js"></script>
<script language="Javascript" src="./js/setup.js"></script>
<script type ="text/javascript" language ="javascript" >
function checkIP()
{
	var Sys1;
	Sys1=document.getElementsByName("n_NTPradiotime");
	if(Sys1[0].checked == true)
	{
		//alert("修改成功！");
		setTimeSet();
		return 0;
	}
	
	var exp=/^(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$/; 
	obj=document.getElementById("NTPaddress").value;
	var reg1 = obj.match(exp); 
	if(reg1==null){
			alert("NTP地址输入不合法！");
			return false;
	}else{
			//alert("修改成功！");
			setTimeSet();
			return true;
		}
}

function settimes() 
{
    var time = new Date();
    hours    = time.getHours();
    mins     = time.getMinutes();
    secs     = time.getSeconds();
    years    = time.getFullYear();
    mons     = (time.getMonth() + 1);
    days     = time.getDate();
    
    mons     = (mons < 10 ? '0' : '') + mons;
    days     = (days < 10 ? '0' : '') + days;
    
    hours    = (hours < 10 ? '0' : '') + hours;
    mins     = (mins < 10 ? '0' : '') + mins;
    secs     = (secs < 10 ? '0' : '') + secs;

    document.getElementById("ClientTime").value = years + "-" + mons + "-" + days + " " + hours + ":" + mins + ":" + secs;
    getSysTime();         //显示系统时间
    setTimeout('settimes()', 999);   //刷新
}
</script>

<script>
function init()
		{    
			settimes();    //页面得到本机时间SSSS
			
		}
</script>

</head>

<body onload="init()">
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
<fieldset>
<legend>当前时间</legend>
<div>
<label>系统时间:</label>
<input type="text" id="SystemTime" name="SystemTime" readonly size="20" />
<br/>
</div>
</fieldset>

<fieldset>
<legend>时间设置</legend>
<br>
<div>
<label>同步方式:</label>
<input type=radio name="n_NTPradiotime"  value="1" checked >本机</input>	
<br/>
</div>
<div>
<label>本机时间:</label>
<input type="text" id="ClientTime" readonly name="ClientTime" size="20" />
<br/>
</div>
<div>
<label></label>
<input type=radio name="n_NTPradiotime" id="NTPradiotime" value="0" checked >NTP同步</input>	
<br/>
</div>
<div>
<label>NTP服务地址:</label>
<input type="text" name="NTPaddress" id="NTPaddress"  size="20" />
<br/>
</div>
<div>
<label></label>
<input type="button" value="应用" onclick="return checkIP()" />
</div>
</fieldset>
		<!--end-->
		
	</div>

	</div>
</div>
</body>
</html>