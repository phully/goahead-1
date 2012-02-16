<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=gb2312"  />
<title>Hunda IPcam</title>
<link rel="stylesheet" type="text/css" href="./css/setting.css" />
<script language="JavaScript" src="./js/AJAXInteraction.js"></script>
<script language="JavaScript" src="./js/page.js"></script>
<script type="text/javascript" src="./js/setup.js"></script>
<script type="text/javascript" src="./js/jquery-1.2.2.pack.js" ></script>
<script type="text/javascript" src="./js/cqy.js"></script>


<script>	
var wkl_clone1;
var wkl_clone2;
var wkl_clone3;
var wkl_clone4;

var wkl_definition2
var wkl_definition3
var wkl_definition4

$(document).ready(function()
{   
	
	 wkl_clone1 = $("#frame_rate1").clone(); 
	 wkl_clone2 = $("#frame_rate2").clone(); 
	 wkl_clone3 = $("#frame_rate3").clone(); 
	 wkl_clone4 = $("#frame_rate4").clone(); 
	 wkl_definition2 = $("#definition2").clone();  
	 wkl_definition3 = $("#definition3").clone();  
	 wkl_definition4 = $("#definition4").clone();  
})   
		
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
<li class="menusub"><a href="./encode1.asp">编码设置1</a></li>
<li class="menusub"><a href="./encode2.asp">编码设置2</a></li>
<li class="menusub"><a href="./encode3.asp">编码设置3</a></li>
<li class="menusub"><a href="./encode4.asp">编码设置4</a></li>
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
			<h3>编码设置</h3>
			<form action="/goform/setEncode" method="post" id="setEncodeId">		
			<fieldset><!-- start h264 field -->
			<legend>基本设置 </legend>	  
	    <div>
	    	<table>
	    	<tr>
				 <td><span>码流数:</span></td>
				 <td>
					<select name = "stream_number" id="stream_number" style="width:100" onchange="judge()">
						<option value = "0" selected="">1</option>
						<option value = "1">2</option>
						<option value = "2">3</option>
						<option value = "3">4</option>		
					</select>
				</td>		
		   </tr>
		   <tr>
				<td><span>模拟视频输出&nbsp;&nbsp;&nbsp;:</span></td>
				<td>
				  <select name = "video_output" id="video_output" style="width:100" >
					  <option value = "0" selected="">关闭</option>
					  <option value = "1">打开</option>		
				</select>	
			  </td>
			  <td><span>&nbsp;&nbsp;&nbsp;制式:</span></td>
				<td>
				  <select name = "video_mode" id="video_mode" style="width:100" >
					  <option value = "0" selected="">PAL</option>
					  <option value = "1">NTSC </option>		
				</select>	
			  </td>	
			  <td><span>&nbsp;&nbsp;&nbsp;显示比例:</span></td>
				<td>
				  <select name = "proportion" id="proportion" style="width:100" >
					  <option value = "0" selected="">16:9</option>
					  <option value = "1">4:3 </option>		
				</select>	
			  </td>			
			</tr>			
		 </table>			
		</div>
		</fieldset>
		
	  <fieldset>
	  	<legend>1 </legend>	  
	  	<div>
	  		<table>
	  			<tr>
	  				<td><span>编码类型&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;:</span></td>
	  				<td>
							<select name = "encode_style1" id="encode_style1" style="width:100" onchange="encode_judge1()">
								<option value = "0" selected="">H.264</option>
								<option value = "1">MJPEG</option>	
							</select>
						</td>	
						<td><span>电子PTZ:</span></td>
						<td>
               <input id="PTZ1" type="checkbox" checked />
            </td>	
	  			</tr>
	  			<tr>
	  				<td><span>帧率:</span></td>
					<td>
						<select name = "frame_rate1" id="frame_rate1" style="width:100" onchange="select_option1_judge()" onfocus="zl_before_change(1)" >
							<option value = "0" >1</option>
							<option value = "1">2</option>
							<option value = "2">3</option>
							<option value = "3">4</option>
							<option value = "4">5</option>
							<option value = "5">6</option>
							<option value = "6">10</option>
							<option value = "7">12</option>
							<option value = "8">13</option>
							<option value = "9">15</option>
							<option value = "10">20</option>
							<option value = "11">24</option>
							<option value = "12">25</option>
							<option value = "13">30</option>
							<option value = "14">50</option>
							<option value = "15">60</option>
							<option value = "16">120</option>
						</select>				  
				  </td>
					 <td><span>&nbsp;&nbsp;清晰度:</span></td>
					 <td>
						<select name = "definition1" id="definition1" style="width:100" onchange="definition_judge()" onfocus="before_change(1)" >
						<!--
							<option value = "0" selected="">CIF</option>
							<option value = "1">480</option>
							<option value = "2">576</option>
							<option value = "3">720</option>
							<option value = "4">UXGA</option>
							<option value = "5">1080</option>
							<option value = "6">2048x1536</option>
							<option value = "7">QXGA</option>
							-->
					  </select>	
					</td>	
					<td><span>旋转方向:</span></td>
					<td>
					  <select name = "rotate1" id="rotate1" style="width:100" >
					  	<option value = "0" selected="">不旋转</option>
							<option value = "1">向右旋转90度</option>
							<option value = "2">向左旋转90度</option>
							<option value = "3">旋转180度</option>
							<option value = "4">垂直翻转</option>
							<option value = "5">水平翻转</option>
					 </select>
				  </td>				  
	  			</tr>
	  		</table>
	  	</div>
	  	<div id="encode1_judge1" name="encode1_judge1"  style="display:">
	  	<fieldset>
				<legend>H.264 </legend>	  		    
		    	<table>	
		    	 <tr>		
		    	 	<td><span>I帧间隔&nbsp;&nbsp;&nbsp;&nbsp;:</span></td>
					  <td>
					  	<input type="text" name = "frame_rate_time1" id="frame_rate_time1" size="15">					  
				  </td>	
				</tr>
				<tr>
				  <td><span>码率控制:</span></td>
				  <td>
				  <select name = "code_rate_contral" id="code_rate_contral" style="width:100" >
						<option value = "0" selected="">IAV_CBR</option>
						<option value = "1">IAV_VBR</option>
						<option value = "2">IAV_CBR_QUALITY_KEEPING</option>
						<option value = "3">IAV_VBR_QUALITY_KEEPING</option>
						<option value = "4">IAV_CBR2</option>
						<option value = "5">IAV_VBR2</option>	
				  </select>	
				 </td>
				 <td><span>CBR平均码率</span></td>
				 <td>
				 	<select name="CBR_code_contral1" id="CBR_code_contral1" style="width:100">
				 		<option value = "0" selected="">256</option>
						<option value = "1">512</option>
						<option value = "2">1024</option>
						<option value = "3">2048</option>
						<option value = "4">4096</option>
						<option value = "4">6144</option>
						<option value = "5">8192</option>
						<option value = "6">10240</option>
						<option value = "7">14336</option>	
				 </td>		  		  				  
				 </tr>	
				 <tr>
				 	<td><span>VBR最小码率</span></td>
				 <td>
				 	<select name="VBR_min_contral1" id="VBR_min_contral1" style="width:100">
				 		<option value = "0" selected="">256</option>
						<option value = "1">512</option>
						<option value = "2">1024</option>
						<option value = "3">2048</option>
						<option value = "4">4096</option>
						<option value = "4">6144</option>
						<option value = "5">8192</option>
						<option value = "6">10240</option>
						<option value = "7">14336</option>
				 </td>
				 <td><span>VBR最大码率</span></td>
				 <td>
				 	<select name="VBR_max_contral1" id="VBR_max_contral1" style="width:100">
				 		<option value = "0" selected="">256</option>
						<option value = "1">512</option>
						<option value = "2">1024</option>
						<option value = "3">2048</option>
						<option value = "4">4096</option>
						<option value = "4">6144</option>
						<option value = "5">8192</option>	
						<option value = "6">10240</option>
						<option value = "7">14336</option>
				 </td>		  			  		  
				 </tr>		
			 </table>					
		 </fieldset>
		 </div>
		 <div id="encode1_judge2" name="encode1_judge2"  style="display:none">
		 <fieldset>
		 	<legend>MJPEG</legend>
		 		<table>
		 			<tr>
		 				<td><span>质量&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span></td>
		 				<td>
		 					<input type="text" name="encode_quality1" id="encode_quality1" value="" size="13"  />
		 				</td>
		 			</tr>
		 		</table>		 	
		 </fieldset>
		 </div>
		</fieldset><!-- end h264 field -->
    
    <div id="stream_judge2" name="stream_judge2"  style="display:none">
    <fieldset>
    	<legend>2 </legend>	  
	  	<div>
	  		<table>
	  			<tr>
	  				<td><span>编码类型&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;:</span></td>
	  				<td>
							<select name = "encode_style2" id="encode_style2" style="width:100" onchange="encode_judge2()">
								<option value = "0" selected="">H.264</option>
								<option value = "1">MJPEG</option>	
							</select>
						</td>	
						<td><span>电子PTZ:</span></td>
						<td>
               <input id="PTZ2" type="checkbox" />
            </td>	
						<tr>
	  				<td><span>帧率:</span></td>
					<td>
					  <select name = "frame_rate2" id="frame_rate2" style="width:100" onchange="" onfocus="zl_before_change(2)">
							<option value = "0" selected="">1</option>
							<option value = "1">2</option>
							<option value = "2">3</option>
							<option value = "3">4</option>
							<option value = "4">5</option>
							<option value = "5">6</option>
							<option value = "6">10</option>
							<option value = "7">12</option>
							<option value = "8">13</option>
							<option value = "9">15</option>
							<option value = "10">20</option>
							<option value = "11">24</option>
							<option value = "12">25</option>
							<option value = "13">30</option>
							<option value = "14">50</option>
							<option value = "15">60</option>
							<option value = "16">120</option>
						</select>				  	
				  </td>
					 <td><span>&nbsp;&nbsp;清晰度:</span></td>
					 <td>
						<select name = "definition2" id="definition2" style="width:100" onchange="definition2_judge()" onfocus="before_change(2)" >
						<!--
							<option value = "0" selected="">CIF</option>
							<option value = "1">480</option>
							<option value = "2">576</option>
							<option value = "3">720</option>
							<option value = "4">UXGA</option>
							<option value = "5">1080</option>
							<option value = "6">2048x1536</option>
							<option value = "7">QXGA</option>
							-->
					  </select>	
					</td>	
					<td><span>旋转方向:</span></td>
					<td>
					  <select name = "rotate2" id="rotate2" style="width:100" >
							<option value = "0" selected="">不旋转</option>
							<option value = "1">向右旋转90度</option>
							<option value = "2">向左旋转90度</option>
							<option value = "3">旋转180度</option>
							<option value = "4">垂直翻转</option>
							<option value = "5">水平翻转</option>
					 </select>
				  </td>				
	  			</tr>
	  		</table>
	  	</div>
	  	<div id="encode2_judge1" name="encode2_judge1"  style="display:">
	    <fieldset>    	
				<legend>H.264 </legend>	  	    
		    	<table>
		    	<tr>
					 <td><span>I帧间隔&nbsp;&nbsp;&nbsp;&nbsp;:</span></td>
					  <td>
					    <input type="text" name = "frame_rate_time2" id="frame_rate_time2" size="15">	
				  </td>	
				</tr>
				<tr>
				  <td><span>码率控制:</span></td>
				  <td>
				  <select name = "code_rate_contra2" id="code_rate_contra2" style="width:100" >
						<option value = "0" selected="">IAV_CBR</option>
						<option value = "1">IAV_VBR</option>
						<option value = "2">IAV_CBR_QUALITY_KEEPING</option>
						<option value = "3">IAV_VBR_QUALITY_KEEPING</option>
						<option value = "4">IAV_CBR2</option>
						<option value = "5">IAV_VBR2</option>	
				  </select>	
				 </td>
				 <td><span>CBR平均码率</span></td>
				 <td>
				 	<select name="CBR_code_contral2" id="CBR_code_contral2" style="width:100">
				 		<option value = "0" selected="">256</option>
						<option value = "1">512</option>
						<option value = "2">1024</option>
						<option value = "3">2048</option>
						<option value = "4">4096</option>
						<option value = "4">6144</option>
						<option value = "5">8192</option>	
						<option value = "6">10240</option>
						<option value = "7">14336</option>
				 </td>		  		  				  
				 </tr>	
				 <tr>
				 	<td><span>VBR最小码率</span></td>
				 <td>
				 	<select name="VBR_min_contral2" id="VBR_min_contral2" style="width:100">
				 		<option value = "0" selected="">256</option>
						<option value = "1">512</option>
						<option value = "2">1024</option>
						<option value = "3">2048</option>
						<option value = "4">4096</option>
						<option value = "4">6144</option>
						<option value = "5">8192</option>	
						<option value = "6">10240</option>
						<option value = "7">14336</option>
				 </td>
				 <td><span>BVR最大码率</span></td>
				 <td>
				 	<select name="VBR_max_contral2" id="VBR_max_contral2" style="width:100">
				 		<option value = "0" selected="">256</option>
						<option value = "1">512</option>
						<option value = "2">1024</option>
						<option value = "3">2048</option>
						<option value = "4">4096</option>
						<option value = "4">6144</option>
						<option value = "5">8192</option>	
						<option value = "6">10240</option>
						<option value = "7">14336</option>
				 </td>		  			  		  
				 </tr>		
				 </tr>			
			 </table>			
			</fieldset><!-- end h264 field -->
		</div>		
		<div id="encode2_judge2" name="encode2_judge2"  style="display:none">
		 <fieldset>
		 	<legend>MJPEG</legend>
		 		<table>
		 			<tr>
		 				<td><span>质量&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span></td>
		 				<td>
		 					<input type="text" name="encode_quality2" id="encode_quality2" value="" size="13"  />
		 				</td>
		 			</tr>
		 		</table>		 	
		 </fieldset>
		 </div>
		</fieldset>
		</div>	
		
	 <div id="stream_judge3" name="stream_judge3"  style="display:none">
    <fieldset>
    	<legend>3 </legend>	  
	  	<div>
	  		<table>
	  			<tr>
	  				<td><span>编码类型&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;:</span></td>
	  				<td>
							<select name = "encode_style3" id="encode_style3" style="width:100" onchange="encode_judge3()">
								<option value = "0" selected="">H.264</option>
								<option value = "1">MJPEG</option>	
							</select>
						</td>	
						<td><span>电子PTZ:</span></td>
						<td>
               <input id="PTZ3" type="checkbox" />
            </td>	
						<tr>
	  				<td><span>帧率:</span></td>
					<td>
					  <select name = "frame_rate3" id="frame_rate3" style="width:100" onchange="" onfocus="zl_before_change(4)">
							<option value = "0" selected="">1</option>
							<option value = "1">2</option>
							<option value = "2">3</option>
							<option value = "3">4</option>
							<option value = "4">5</option>
							<option value = "5">6</option>
							<option value = "6">10</option>
							<option value = "7">12</option>
							<option value = "8">13</option>
							<option value = "9">15</option>
							<option value = "10">20</option>
							<option value = "11">24</option>
							<option value = "12">25</option>
							<option value = "13">30</option>
							<option value = "14">50</option>
							<option value = "15">60</option>
							<option value = "16">120</option>
						</select>				  		
				  </td>
					 <td><span>&nbsp;&nbsp;清晰度:</span></td>
					 <td>
						<select name = "definition3" id="definition3" style="width:100" onchange="" onfocus="before_change(3)" >
							<option value = "0" selected="">CIF</option>
							<option value = "1">480</option>
							<option value = "2">576</option>
							<option value = "3">720</option>
							<option value = "4">UXGA</option>
							<option value = "5">1080</option>
							<option value = "6">2048x1536</option>
							<option value = "7">QXGA</option>
					  </select>	
					</td>	
					<td><span>旋转方向:</span></td>
					<td>
					  <select name = "rotate3" id="rotate3" style="width:100" >
							<option value = "0" selected="">不旋转</option>
							<option value = "1">向右旋转90度</option>
							<option value = "2">向左旋转90度</option>
							<option value = "3">旋转180度</option>
							<option value = "4">垂直翻转</option>
							<option value = "5">水平翻转</option>
					 </select>
				  </td>				
	  			</tr>
	  		</table>
	  	</div>
	  	<div id="encode3_judge1" name="encode3_judge1"  style="display:">
	    <fieldset>    	
				<legend>H.264 </legend>	  	    
		    	<table>
		    	<tr>
					 <td><span>I帧间隔&nbsp;&nbsp;&nbsp;&nbsp;:</span></td>
					  <td>
					    <input type="text" name = "frame_rate_time3" id="frame_rate_time3" size="15">	
				  </td>	
				</tr>
				<tr>
				  <td><span>码率控制:</span></td>
				  <td>
				  <select name = "code_rate_contra3" id="code_rate_contra3" style="width:100" >
						<option value = "0" selected="">IAV_CBR</option>
						<option value = "1">IAV_VBR</option>
						<option value = "2">IAV_CBR_QUALITY_KEEPING</option>
						<option value = "3">IAV_VBR_QUALITY_KEEPING</option>
						<option value = "4">IAV_CBR2</option>
						<option value = "5">IAV_VBR2</option>	
				  </select>	
				 </td>
				 <td><span>CBR平均码率</span></td>
				 <td>
				 	<select name="CBR_code_contral3" id="CBR_code_contral3" style="width:100">
				 		<option value = "0" selected="">256</option>
						<option value = "1">512</option>
						<option value = "2">1024</option>
						<option value = "3">2048</option>
						<option value = "4">4096</option>
						<option value = "4">6144</option>
						<option value = "5">8192</option>
						<option value = "6">10240</option>
						<option value = "7">14336</option>	
				 </td>		  		  				  
				 </tr>	
				 <tr>
				 	<td><span>VBR最小码率</span></td>
				 <td>
				 	<select name="VBR_min_contral3" id="VBR_min_contral3" style="width:100">
				 		<option value = "0" selected="">256</option>
						<option value = "1">512</option>
						<option value = "2">1024</option>
						<option value = "3">2048</option>
						<option value = "4">4096</option>
						<option value = "4">6144</option>
						<option value = "5">8192</option>	
						<option value = "6">10240</option>
						<option value = "7">14336</option>
				 </td>
				 <td><span>VBR最大码率</span></td>
				 <td>
				 	<select name="VBR_max_contral3" id="VBR_max_contral3" style="width:100">
				 		<option value = "0" selected="">256</option>
						<option value = "1">512</option>
						<option value = "2">1024</option>
						<option value = "3">2048</option>
						<option value = "4">4096</option>
						<option value = "4">6144</option>
						<option value = "5">8192</option>	
						<option value = "6">10240</option>
						<option value = "7">14336</option>
				 </td>		  			  		  
				 </tr>		
				 </tr>			
			 </table>			
			</fieldset><!-- end h264 field -->
		</div>		
		<div id="encode3_judge2" name="encode3_judge2"  style="display:none">
		 <fieldset>
		 	<legend>MJPEG</legend>
		 		<table>
		 			<tr>
		 				<td><span>质量&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span></td>
		 				<td>
		 					<input type="text" name="encode_quality3" id="encode_quality3" value="" size="13"  />
		 				</td>
		 			</tr>
		 		</table>		 	
		 </fieldset>
		 </div>
		</fieldset>
		</div>	
		
		 <div id="stream_judge4" name="stream_judge4"  style="display:none">
    <fieldset>
    	<legend>4 </legend>	  
	  	<div>
	  		<table>
	  			<tr>
	  				<td><span>编码类型&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;:</span></td>
	  				<td>
							<select name = "encode_style4" id="encode_style4" style="width:100" onchange="encode_judge4()">
								<option value = "0" selected="">H.264</option>
								<option value = "1">MJPEG</option>	
							</select>
						</td>	
						<td><span>电子PTZ:</span></td>
						<td>
               <input id="PTZ4" type="checkbox" />
            </td>	 
						<tr>
	  				<td><span>帧率:</span></td>
					<td>
					  <select name = "frame_rate4" id="frame_rate4" style="width:100" onchange="" onfocus="zl_before_change(4)">
							<option value = "0" selected="">1</option>
							<option value = "1">2</option>
							<option value = "2">3</option>
							<option value = "3">4</option>
							<option value = "4">5</option>
							<option value = "5">6</option>
							<option value = "6">10</option>
							<option value = "7">12</option>
							<option value = "8">13</option>
							<option value = "9">15</option>
							<option value = "10">20</option>
							<option value = "11">24</option>
							<option value = "12">25</option>
							<option value = "13">30</option>
							<option value = "14">50</option>
							<option value = "15">60</option>
							<option value = "16">120</option>
						</select>				  		
				  </td>
					 <td><span>&nbsp;&nbsp;清晰度:</span></td>
					 <td>
						<select name = "definition4" id="definition4" style="width:100" onchange="" onfocus="before_change(4)" >
							<option value = "0" selected="">CIF</option>
							<option value = "1">480</option>
							<option value = "2">576</option>
							<option value = "3">720</option>
							<option value = "4">UXGA</option>
							<option value = "5">1080</option>
							<option value = "6">2048x1536</option>
							<option value = "7">QXGA</option>
					  </select>	
					</td>	
					<td><span>旋转方向:</span></td>
					<td>
					  <select name = "rotate4" id="rotate4" style="width:100" >
							<option value = "0" selected="">不旋转</option>
							<option value = "1">向右旋转90度</option>
							<option value = "2">向左旋转90度</option>
							<option value = "3">旋转180度</option>
							<option value = "4">垂直翻转</option>
							<option value = "5">水平翻转</option>
					 </select>
				  </td>				
	  			</tr>
	  		</table>
	  	</div>
	  	
	  	<div id="encode4_judge1" name="encode4_judge1"  style="display:">
	    <fieldset>    	
				<legend>H.264 </legend>	  	    
		    	<table>
		    	<tr>
					 <td><span>I帧间隔&nbsp;&nbsp;&nbsp;&nbsp;:</span></td>
					  <td>
					    <input type="text" name = "frame_rate_time4" id="frame_rate_time4" size="15">	
				  </td>	
				</tr>
				<tr>
				  <td><span>码率控制:</span></td>
				  <td>
				  <select name = "code_rate_contra4" id="code_rate_contra4" style="width:100" >
						<option value = "0" selected="">IAV_CBR</option>
						<option value = "1">IAV_VBR</option>
						<option value = "2">IAV_CBR_QUALITY_KEEPING</option>
						<option value = "3">IAV_VBR_QUALITY_KEEPING</option>
						<option value = "4">IAV_CBR2</option>
						<option value = "5">IAV_VBR2</option>	
				  </select>	
				 </td>
				 <td><span>CBR平均码率</span></td>
				 <td>
				 	<select name="CBR_code_contral4" id="CBR_code_contral4" style="width:100">
				 		<option value = "0" selected="">256</option>
						<option value = "1">512</option>
						<option value = "2">1024</option>
						<option value = "3">2048</option>
						<option value = "4">4096</option>
						<option value = "4">6144</option>
						<option value = "5">8192</option>	
						<option value = "6">10240</option>
						<option value = "7">14336</option>
				 </td>		  		  				  
				 </tr>	
				 <tr>
				 	<td><span>VBR最小码率</span></td>
				 <td>
				 	<select name="VBR_min_contral4" id="VBR_min_contral4" style="width:100">
				 		<option value = "0" selected="">256</option>
						<option value = "1">512</option>
						<option value = "2">1024</option>
						<option value = "3">2048</option>
						<option value = "4">4096</option>
						<option value = "4">6144</option>
						<option value = "5">8192</option>	
						<option value = "6">10240</option>
						<option value = "7">14336</option>
				 </td>
				 <td><span>VBR最大码率</span></td>
				 <td>
				 	<select name="VBR_max_contral4" id="VBR_max_contral4" style="width:100">
				 		<option value = "0" selected="">256</option>
						<option value = "1">512</option>
						<option value = "2">1024</option>
						<option value = "3">2048</option>
						<option value = "4">4096</option>
						<option value = "4">6144</option>
						<option value = "5">8192</option>	
						<option value = "6">10240</option>
						<option value = "7">14336</option>
				 </td>		  			  		  
				 </tr>		
				 </tr>			
			 </table>			
			</fieldset><!-- end h264 field -->
		</div>	
			
		<div id="encode4_judge2" name="encode4_judge2"  style="display:none">
		 <fieldset>
		 	<legend>MJPEG</legend>
		 		<table>
		 			<tr>
		 				<td><span>质量&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span></td>
		 				<td>
		 					<input type="text" name="encode_quality4" id="encode_quality4" value="" size="13"  />
		 				</td>
		 			</tr>
		 		</table>		 	
		 </fieldset>
		 </div>
		</fieldset>
		</div>
		<input type="button" name="reset"  value="保存" onclick="setinfo()"/>	
			</div>
			</form>
<!--4 end--  setinfo>
</div>
</div>
</div>
</body>
</html>
