<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
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
	
	function Commit() {	
	    document.user.action = "/goform/user?Operate=modifypass";
	    document.user.submit();
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
	<h3>修改密码</h3>
		<form action=/goform/user method="post" name="user">
			<table>
				<tr>
					<td>您要修改密码的用户为:</td><td><% GetCurrentUser(); %></td>
				</tr>
				<tr>
					<td>旧密码:</td>
				<td>
					<INPUT TYPE=password name="oldpassword" size=40  title="旧密码" value="">
				</td>
				</tr>
				<tr>
					<td>新密码:</td>
				<td>
					<input type=password name="password" size=40 title="新密码" value="">
				</td>
				</tr>
				<tr>
					<td>重复新密码:</td>
				<td>
					<input type=password name="passconf" size=40 title="确认新密码" value="">
				</td>
				</tr>
				<tr/><tr/><tr/><tr/>
				<tr>
				    <td></td>
				      <td ALIGN="CENTER"> 
				        <input type="button" STYLE="width:60pt" value="修改" onclick="return Commit()"></td>
				</tr>
			</table>
		</form>
<!--you code end-->
		
	</div>

	</div>
</div>
</body>
</html>