<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
<title>Hunda IPcam</title>
<link rel="stylesheet" type="text/css" href="./css/setting.css" />
<script language="JavaScript"  src="./js/AJAXInteraction.js"></script>
<script type="text/javascript" src="./js/setup.js" ></script>
<script type="text/javascript" src="./js/Cqyosd.js" ></script>
<script type="text/javascript" src="./js/jquery-1.2.2.pack.js" ></script>

<style>

.sidebtn {
	background: url(./img/list.gif) no-repeat top left;
	height: 16px;
	margin: 0 auto;
	position: relative;
	top: 0px;
}

.sidebtn.on {
	background: url(./img/fold.gif) no-repeat top left;
	height: 16px;
	margin: 0 auto;
	position: relative;
	top: 0px;
}


</style>

<script>		
$(document).ready(function () {
	  $('.sidebtn').click(function () {
	  	if ($(this).hasClass("on")) {
  			$(this).removeClass("on");
 			}else{
  			$(this).addClass("on");
			}
			
	  	$(this).next("div").slideToggle();
    });
});
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
		
<!--you code start-->
		<br>
			<h3>设置视频叠加OSD的参数</h3>
			<OBJECT CLASSID="CLSID:3BCDAA6A-7306-42FF-B8CF-BE5D3534C1E4" codebase="./ambaWeb.cab#version=1,0,0,32" 
		   WIDTH=480 HEIGHT=310 align="absmiddle"ID="AmbaIPCmrWebPlugIn1">
		   <PARAM NAME="_Version" VALUE="65536">
		   <PARAM NAME="_ExtentX" VALUE="19045">
		   <PARAM NAME="_ExtentY" VALUE="11478">
		   <PARAM NAME="_StockProps" VALUE="0">
</OBJECT>
			<fieldset>
			<legend>区域 1</legend>
  			<p class="sidebtn"></p>
				<div id="isOpened" style="display:none">
				<table>
						<tr>
							<td align="center"><span>叠加字符:</span></td>
							<td colspan="3"  align="left"><input id="s1_text1" type="text" size="45"  /></td>					
							<td align="center"><span>&nbsp;&nbsp;&nbsp;字体大小:</span></td>
							<td align="left"><input id="s1_text1_size" type="text" size="9"/></td>		
						</tr>
						<tr>
							<td align="center"><span>区域宽度:</span></td>
							<td align="left"><input id="s1_text1_width" type="text" size="20"/></td>	
							<td align="center"><span>&nbsp;&nbsp;&nbsp;&nbsp;区域高度:</span></td>
							<td align="left"><input id="s1_text1_high" type="text" size="9"/></td>	
							<td><span>&nbsp;&nbsp;&nbsp;粗&nbsp;&nbsp;&nbsp;&nbsp;体:</span></td>
						<td>
								<select id="s1_text1_bold" style="width:67">
									<option value="0" selected="">0</option>
									<option value="1">1</option>
									<option value="2">2</option>
									<option value="3">3</option>
									<option value="4">4</option>
									<option value="5">5</option>
									<option value="6">6</option>
								</select>
							</td>
						</tr>
						<tr>
						<td><span>显示位置:</span></td>
						<td align="center">
							<span>X</span>
							<input id="s1_text1_startx" type="text" size="6"/>
							<span>Y</span>
							<input id="s1_text1_starty" type="text" size="6"/>
						</td>	
						<td><span>&nbsp;&nbsp;&nbsp;&nbsp;旋转方向:</span></td>
							<td>
								<select id="s1_text1_rotate" style="width:67">
									<option value="0" selected="">0</option>
									<option value="90">90</option>
									<option value="180">180</option>
									<option value="270">270</option>
								</select>
							</td>	
						<td><span>&nbsp;&nbsp;&nbsp;斜&nbsp;&nbsp;&nbsp;&nbsp;体:</span></td>
						<td>
								<select id="s1_text1_italic" style="width:67">
									<option value="0" selected="">0</option>
									<option value="1">1</option>
									<option value="2">2</option>
									<option value="3">3</option>
									<option value="4">4</option>
									<option value="5">5</option>
									<option value="6">6</option>
								</select>
							</td>	
					</tr>
					<tr>	
						<td><span>显示方式:</span></td>
							<td>
								<select id="s1_text1_type">
									<option value="0" selected="">字符</option>
									<option value="1">时间</option>
								</select>
							</td>			
						<td><span>&nbsp;&nbsp;&nbsp;&nbsp;颜&nbsp;&nbsp;&nbsp;色:</span></td>
						<td>
							<select id="s1_text1_color" style="width:67">
								<option selected="" value="0">Black</option>
								<option value="1">Red</option>
								<option value="2">Blue</option>
								<option value="3">Green</option>
								<option value="4">Yellow</option>
								<option value="5">Magenta</option>
								<option value="6">Cyan</option>
								<option value="7">White</option>
							</select>
						</td>
						<td><span>&nbsp;&nbsp;&nbsp;边框宽度:</span></td>
							<td>
								<select id="s1_text1_outline" style="width:67">
									<option value="0" selected="">0</option>
									<option value="1">1</option>
									<option value="2">2</option>
									<option value="3">3</option>
								</select>
							</td>		
					</tr>
					<tr>	
					</tr>
				</table>
				<input type="button" id="stream1" value="保存" onclick = "Judge1()"/>
				<input type="button" id="clean" value="清除" onclick = "clean1()"/>
				</div>
			</fieldset>
			
			<br>
			<fieldset>
			<legend>区域 2</legend>
  			<p class="sidebtn"></p>
				<div id="isOpened" style="display:none">
				<table>
						<tr>
							<td align="center"><span>叠加字符:</span></td>
							<td colspan="3" align="left"><input id="s1_text2" type="text" size="45"/></td>							
							<td align="center"><span>&nbsp;&nbsp;&nbsp;字体大小:</span></td>
							<td align="left"><input id="s1_text2_size" type="text" size="9"/></td>
							<td><div style="display:none">
								<input id="text_judge" type="text" size="1"></div>
							</td>	
							<td><div style="display:none">
								<input id="text_clean" type="text" size="1" value="1"></div>
							</td>									
						</tr>
						<tr>
							<td align="center"><span>区域宽度:</span></td>
							<td align="left"><input id="s1_text2_width" type="text"/></td>	
							<td align="center"><span>&nbsp;&nbsp;&nbsp;&nbsp;区域高度:</span></td>
							<td align="left"><input id="s1_text2_high" type="text" size="9"/></td>	
							<td><span>&nbsp;&nbsp;&nbsp;粗&nbsp;&nbsp;&nbsp;&nbsp;体:</span></td>
						<td>
								<select id="s1_text2_bold" style="width:67">
									<option value="0" selected="">0</option>
									<option value="1">1</option>
									<option value="2">2</option>
									<option value="3">3</option>
									<option value="4">4</option>
									<option value="5">5</option>
									<option value="6">6</option>
								</select>
							</td>
						</tr>
						<tr>
						<td><span>显示位置:</span></td>
						<td align="center">
							<span>X</span>
							<input id="s1_text2_startx" type="text" size="6"/>
							<span>Y</span>
							<input id="s1_text2_starty" type="text" size="6"/>
						</td>	
						<td><span>&nbsp;&nbsp;&nbsp;&nbsp;旋转方向:</span></td>
							<td>
								<select id="s1_text2_rotate" style="width:67">
									<option value="0" selected="">0</option>
									<option value="90">90</option>
									<option value="180">180</option>
									<option value="270">270</option>
								</select>
							</td>		
						
						<td><span>&nbsp;&nbsp;&nbsp;斜&nbsp;&nbsp;&nbsp;体:</span></td>
						<td>
								<select id="s1_text2_italic" style="width:67">
									<option value="0" selected="">0</option>
									<option value="1">1</option>
									<option value="2">2</option>
									<option value="3">3</option>
									<option value="4">4</option>
									<option value="5">5</option>
									<option value="6">6</option>
								</select>
							</td>	
					</tr>
					<tr>	
						<td><span>显示方式:</span></td>
							<td>
								<select id="s1_text2_type">
									<option value="0" selected="">字符</option>
									<option value="1">时间</option>
								</select>
							</td>				
						<td><span>&nbsp;&nbsp;&nbsp;&nbsp;颜&nbsp;&nbsp;&nbsp;色:</span></td>
						<td>
							<select id="s1_text2_color" style="width:67">
								<option selected="" value="0">Black</option>
								<option value="1">Red</option>
								<option value="2">Blue</option>
								<option value="3">Green</option>
								<option value="4">Yellow</option>
								<option value="5">Magenta</option>
								<option value="6">Cyan</option>
								<option value="7">White</option>
							</select>
						</td>
						<td><span>&nbsp;&nbsp;&nbsp;边框宽度:</span></td>
							<td>
								<select id="s1_text2_outline" style="width:67">
									<option value="0" selected="">0</option>
									<option value="1">1</option>
									<option value="2">2</option>
									<option value="3">3</option>
								</select>
							</td>							
					</tr>
					<tr>	
					</tr>
				</table>
				<input type="button" id="stream1" value="保存" onclick = "Judge2()"/>
				<input type="button" id="clean" value="清除" onclick = "clean2()"/>
				</div>
			</fieldset>
			
			
			<br>
			<fieldset>
			<legend>区域 3</legend>
  			<p class="sidebtn"></p>
				<div id="isOpened" style="display:none">
				<table>
						<tr>
							<td align="center"><span>叠加字符:</span></td>
							<td colspan="3" align="left"><input id="s1_text3" type="text" size="45"/></td>
							<td align="center"><span>&nbsp;&nbsp;&nbsp;字体大小:</span></td>
							<td align="left"><input id="s1_text3_size" type="text" size="9"/></td>
								
						</tr>
						<tr>
							<td align="center"><span>区域宽度:</span></td>
							<td align="left"><input id="s1_text3_width" type="text"/></td>		
							<td align="center"><span>&nbsp;&nbsp;&nbsp;&nbsp;区域高度:</span></td>
							<td align="left"><input id="s1_text3_high" type="text" size="9"/></td>	
							<td><span>&nbsp;&nbsp;&nbsp;粗&nbsp;&nbsp;&nbsp;&nbsp;体:</span></td>
					  	<td>
								<select id="s1_text3_bold" style="width:67">
									<option value="0" selected="">0</option>
									<option value="1">1</option>
									<option value="2">2</option>
									<option value="3">3</option>
									<option value="4">4</option>
									<option value="5">5</option>
									<option value="6">6</option>
								</select>
							</td>
						</tr>
						<tr>
						<td><span>显示位置:</span></td>
						<td align="center">
							<span>X</span>
							<input id="s1_text3_startx" type="text" size="6"/>
							<span>Y</span>
							<input id="s1_text3_starty" type="text" size="6"/>
						</td>	
						<td><span>&nbsp;&nbsp;&nbsp;&nbsp;旋转方向:</span></td>
							<td>
								<select id="s1_text3_rotate" style="width:67">
									<option value="0" selected="">0</option>
									<option value="90">90</option>
									<option value="180">180</option>
									<option value="270">270</option>
								</select>
							</td>								
						<td><span>&nbsp;&nbsp;&nbsp;斜&nbsp;&nbsp;&nbsp;&nbsp;体:</span></td>
						<td>
								<select id="s1_text3_italic"   style="width:67">
									<option value="0" selected="">0</option>
									<option value="1">1</option>
									<option value="2">2</option>
									<option value="3">3</option>
									<option value="4">4</option>
									<option value="5">5</option>
									<option value="6">6</option>
								</select>
							</td>	
					</tr>
					<tr>	
						<td><span>显示方式:</span></td>
							<td>
								<select id="s1_text3_type">
									<option value="0" selected="">字符</option>
									<option value="1">时间</option>
								</select>
							</td>			
						<td><span>&nbsp;&nbsp;&nbsp;&nbsp;颜&nbsp;&nbsp;&nbsp;色:</span></td>
						<td>
							<select id="s1_text3_color" style="width:67">
								<option selected="" value="0">Black</option>
								<option value="1">Red</option>
								<option value="2">Blue</option>
								<option value="3">Green</option>
								<option value="4">Yellow</option>
								<option value="5">Magenta</option>
								<option value="6">Cyan</option>
								<option value="7">White</option>
							</select>
						</td>
						<td><span>&nbsp;&nbsp;&nbsp;边框宽度:</span></td>
							<td>
								<select id="s1_text3_outline" style="width:67">
									<option value="0" selected="">0</option>
									<option value="1">1</option>
									<option value="2">2</option>
									<option value="3">3</option>
								</select>
							</td>								
					</tr>
					<tr>	
					</tr>
				</table>
				<input type="button" id="stream1" value="保存" onclick = "Judge3()"/>
				<input type="button" id="clean" value="清除" onclick = "clean3()"/>
				</div>
			</fieldset>
<!--you code end-->
		
	</div>

	</div>
</div>
</body>
</html>