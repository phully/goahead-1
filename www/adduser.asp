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

	function Add() {
	    var bRet;
	
	    bRet = checkinfo();
	    if (false == bRet) {
	        return false;
	    }
	
	    document.user.action = "/goform/user?Operate=add";
	    document.user.submit();
	}
	
	function checkinfo() {
	    if (document.user.user.value == "") {
	        alert("请填写用户名称!");
	        return false;
	    }
	    else if (document.user.group.value == "") {
	        alert("请选择所属用户组！");
	        return false;
	    }
	    else {
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
		
<!--you code start-->
		<form action=/goform/user method="post" name="user">
			<h3>用户管理</h3>
	    <table width="90%" border="1" cellpadding="0" cellspacing="0" bgcolor="#ECFAFF" class="table-2-index">
	      <tr>
	        <td  colspan="2"  align="center" class="biao" >创建新用户</td>
	      </tr>
	       <tr align="center" class="toprow">
	       <td align="right" class="lefttd" width="44%">用户名称</td>
	       <td align="left" class="righttd"><input type="text" name="user" maxlength=20 /></td>
	       </tr>
	       <tr>
	       <td align="right" class="lefttd" width="44%">所属用户组</td>
	       <td align="left" class="righttd">
	       <% MakeGroupList(); %>
	       </td>
	       </tr>
	       <tr>
	       <td align="right" class="lefttd" width="44%">密码</td>
	       <td align="left" class="righttd"><input type="password" name="password" maxlength=20 /></td>
	       </tr>
	       <tr>
	       <td align="right" class="lefttd" width="44%">确认密码</td>
	       <td align="left" class="righttd"><input type="password" name="passconf" maxlength=20 /></td>
	       </tr>
	
	      <tr>
	      <td align="center" height="40" colspan="2" class="lefttd">
	      <input type="button" class="aniu" value="增加" onclick="return Add()"/>&nbsp;&nbsp;
	      <input type="reset"" class="aniu" value="重置"/>
	      </td>
	      </tr>
	    </table>
		<form/>
<!--you code end-->
		
	</div>

	</div>

</div>
</body>
</html>