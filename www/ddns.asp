<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
	<title>DDNS</title>
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
			<a name="" href="./home.asp">VIEW</a>
			<a name="" href="./sysstat.asp">SETTING</a>
			<a name="" href="http://www.hunda.net">Contact us</a>
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
<li class="menusub"><a href="./wifi.asp">无线网络</a></li>
<li class="menusub"><a href="./pppoe.asp">PPPoE</a></li>
<li class="menusub"><a href="./ddns.asp">动态域名</a></li>
</ul>
</div>			
<div class="navhead">视频设置</div>                        
<div class="navcontent">
<ul>
<li class="menusub"><a href="./encode.asp">编码设置</a></li>
<li class="menusub"><a href="./image.asp">图像质量</a></li>
<li class="menusub"><a href="./osd.asp">OSD</a></li>
<li class="menusub"><a href="./privacy.asp">隐私遮蔽</a></li>
<li class="menusub"><a href="./vinvout.asp">输入输出</a></li>
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
			<h3>设置系统的动态域名参数</h3>
			<form action="/goform/setEncode" method="post" id="setEncodeId">
			<fieldset>
			<legend>动态域名</legend>
			<B>DDNS启用:</B>
			<input id="on" type="radio" name="active" checked=""/>On
			<input id="off" type="radio" name="active"/>Off
			<br>
			<B>ISP选择</B>
			<select id="ISP">
				<option selected="" value="dyndns.org">dyndns.org</option>
				<option value="dhs.org">dhs.org</option>
				<option value="easydns.org">easydns.org</option>
			</select>
			<br>
			<B>域  名</B>
			<input id="HostName" type="text" size="20"/>
			<br>
			<B>账  号</B>
			<input id="UserName" type="text" size="20"/>
			<br>
			<B>密  码</B>
			<input id="Password" type="password" size="20"/>
			<br>
			</fieldset>
			<input type="button" value="保存" onclick="setPrivacy("set")"/>
			
			</form>
			<br/>
<!--you code end-->
		
	</div>

	</div>

	<div id="last">
		<div>
			<br>单位地址：上海中山北一路1200号新光三号楼二层<br>电话：021-65440440/65444469/65440782 传真：021-65368814<br>网站：www.hunda.net 邮箱： hunda@hunda.net<br>《中华人民共和国电信与信息服务业务经营许可证》编号：沪ICP备05042258号<br>
		</div>
	</div>
</div>
</body>
</html>