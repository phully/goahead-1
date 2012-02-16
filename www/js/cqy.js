
var G_zl = [1, 2, 3, 4, 5, 6, 10, 12, 13, 15, 20, 24, 25, 30, 50, 60];

var G = {
	single:{
		s_1:["1080p",30],
		s_2:["1080p",15],
		s_3:["720p",30],
		s_4:["1440*1080p",30],
		s_5:["1600*1200p",30],
		s_6:["2048*1536p",15],
		s_7:["720p",30]		
	},
	dual:{
		s_1:["1080p", 30, "480p", 30],
		s_2:["1080p", 28, "800*600p", 28],
		s_3:["1080p", 24, "720p", 24],
		s_4:["1080p", 15, "1080", 15],
		s_5:["1080p", 15, "720p", 30],
		s_6:["720p", 60, "480p", 30],
		s_7:["720p", 60, "CIF", 60],
		s_8:["720p", 30, "720p", 30],
		s_9:["720p", 30, "CIF", 30],
		s_10:["480p", 30, "480p", 30],
		s_11:["2048*1536p", 15, "576p", 15],
		s_12:["2560*1440p", 15, "480p", 15],
		s_13:["2560*1440p", 15, "720p", 15],
		s_14:["2592*1944p", 15, "576p", 12]
	},
	Triple:
	{
	 s_1:["1080p", 30, "CIF", 30, "CIF", 30],
     s_2:["1080p", 28, "480p", 28, "CIF", 28],
	 s_3:["1080p", 20, "720p", 20, "480p", 20],
	 s_4:["720p", 30, "720p", 30, "480p", 30],
	 s_5:["720p", 25, "720p", 25, "720p", 25] 
	},
   quadplex:{
		s_1:["1080p", 30, "CIF", 30, "CIF", 30, "CIF", 30],
		s_2:["1080p", 20, "720p", 20, "480p", 20, "CIF", 20],
		s_3:["1080p", 25, "480p", 25, "480p", 25, "CIF", 25],	
		s_4:["1080p", 8, "1080p", 8, "1080p", 8, "1080p", 8]
		
	}
};


function check_rate_time() 
	{		
		var exp=/^(([1-9]|([1-9]\d)|(1\d\d)|(2([0-4]\d|5[0-5]))))$/; 
		obj=document.getElementById("frame_rate_time1").value 
		var reg1 = obj.match(exp); 
		obj=document.getElementById("frame_rate_time2").value 
		var reg2 = obj.match(exp); 
		obj=document.getElementById("frame_rate_time3").value 
		var reg3 = obj.match(exp); 
		obj=document.getElementById("frame_rate_time4").value 
		var reg4 = obj.match(exp); 
		if(reg1==null){
			alert("����ĵ�һ��I֡������Ϸ�,(1-255)");
			return false;
		}
		else if(reg2==null)
		{
			alert("����ĵڶ���I֡������Ϸ�,(1-255)");
			return false;
		}
		else if(reg3==null)
		{
			alert("����ĵ����I֡������Ϸ�,(1-255)");
			return false;
		}
		else if(reg4==null)
		{
			alert("����ĵ��ĸ�I֡������Ϸ�,(1-255)");
			return false;
		}
		else{
			//alert("�޸ĳɹ���");
			return true;
		}
 }


function checkmin_rate_time()        //������������ж�֡��
	{		
		var exp=/^(([1-9]|([1-9]\d)|(1\d\d)|(2([0-4]\d|5[0-5]))))$/; 
		obj=document.getElementById("frame_rate_time").value 
		var reg1 = obj.match(exp); 
	  if(reg1==null){
			alert("�����I֡������Ϸ�,(1-255)");
			return false;
		}else{
			//alert("�޸ĳɹ���");
			return true;
		}
	}

function get_option_defalut_arrs (stream_number_value) {
  var arrs;
    switch(stream_number_value)
   {
   case "0":
     arrs = G.single;
     break
   case "1":
     arrs = G.dual;
     break
   case "2":
     arrs = G.Triple;
     break
   case "3":
     arrs = G.quadplex;
     break
   default:
     break
   }
   var j = 0;
   for (var i in arrs)
       if(j == 0)
       return arrs[i];

}

function set_option_default_value (stream_number_value, argument) {
    var arrs = get_option_defalut_arrs(stream_number_value);
    $("#definition"+argument+" option").remove();
    $("#definition"+argument+"").append("<option value='1'>"+arrs[(argument-1)*2]+"</option>");
    $("#definition"+argument+"").val(1); 
}

function set_option_default_value_judg (stream_number_value, argument) {
  switch(argument)
   {
   case 1:
     set_option_default_value(stream_number_value, 1);
     break
   case 2:
     set_option_default_value(stream_number_value, 1);
     set_option_default_value(stream_number_value, 2);
     break
   case 3:
     set_option_default_value(stream_number_value, 1);
     set_option_default_value(stream_number_value, 2);
     set_option_default_value(stream_number_value, 3);
     break
   case 4:
     set_option_default_value(stream_number_value, 1);
     set_option_default_value(stream_number_value, 2);
     set_option_default_value(stream_number_value, 3);
     set_option_default_value(stream_number_value, 4);
     break
   default:
     break
   }
}




function judge()
	{
		var stream_number_value=document.getElementById("stream_number").value;
		if(stream_number_value==0)
		{
	      set_option_default_value_judg(stream_number_value, 1);
		  $('#stream_judge2').css("display","none");
		  $('#stream_judge3').css("display","none");
		  $('#stream_judge4').css("display","none");
	  }
		if(stream_number_value==1)
		{
	      set_option_default_value_judg(stream_number_value, 2);
		  $('#stream_judge2').css("display","");
		  $('#stream_judge3').css("display","none");
		  $('#stream_judge4').css("display","none");
	  }
	    
	  if(stream_number_value==2)
		{
			set_option_default_value_judg(stream_number_value, 3);
			$('#stream_judge2').css("display","");
		  $('#stream_judge3').css("display","");
		  $('#stream_judge4').css("display","none");
	  }
		
		if(stream_number_value==3)
		{
			set_option_default_value_judg(stream_number_value, 4);
			$('#stream_judge2').css("display","");
		  $('#stream_judge3').css("display","");
		  $('#stream_judge4').css("display","");
	  }
	}
	
function encode_judge1()
{
		var stream_number_value=document.getElementById("encode_style1").value;
		if(stream_number_value==0)
		{
			
			$('#encode1_judge1').css("display","");
			$('#encode1_judge2').css("display","none");
	  }
	  if(stream_number_value==1)
		{
			$('#encode1_judge1').css("display","none");
			$('#encode1_judge2').css("display","");
	  }
}


function encode_judge2()
{
		var stream_number_value=document.getElementById("encode_style2").value;
		if(stream_number_value==0)
		{
			
			$('#encode2_judge1').css("display","");
			$('#encode2_judge2').css("display","none");
	  }
	  if(stream_number_value==1)
		{
			$('#encode2_judge1').css("display","none");
			$('#encode2_judge2').css("display","");
	  }
}

function encode_judge3()
{
		var stream_number_value=document.getElementById("encode_style3").value;
		if(stream_number_value==0)
		{
			
			$('#encode3_judge1').css("display","");
			$('#encode3_judge2').css("display","none");
	  }
	  if(stream_number_value==1)
		{
			$('#encode3_judge1').css("display","none");
			$('#encode3_judge2').css("display","");
	  }
}

function encode_judge4()
{
		var stream_number_value=document.getElementById("encode_style4").value;
		if(stream_number_value==0)
		{
			
			$('#encode4_judge1').css("display","");
			$('#encode4_judge2').css("display","none");
	  }
	  if(stream_number_value==1)
		{
			$('#encode4_judge1').css("display","none");
			$('#encode4_judge2').css("display","");
	  }
}

function checkquality() 
	{		
		var exp= /^(?:0|[1-9][0-9]?|100)$/; 
		obj=document.getElementById("quality").value 
		var reg1 = obj.match(exp); 
		if(reg1==null){
			alert("�����������������(0-100)!");
			return false;
		}
		else{
			//alert("�޸ĳɹ���");
			return true;
		}
	}


function init()
	{
		getEncode();	
	}


function setinfo()
	{
		if(check_rate_time())
		{
		   setEncode();
	  }
	}

function remove_option(minvalue,maxvalue,firstvalue)            //ɾ��option�µ�Ԫ��
{
	for(i=minvalue ; i<=maxvalue; i++)
	{
	  $('#frame_rate1 option:eq('+ firstvalue + ')').remove();
  }
}

function remove_definition2(minvalue,maxvalue,firstvalue)            //��ݵ�һ��ƥ��ڶ��������
{
	for(i=minvalue ; i<=maxvalue; i++)
	{
	  $('#definition2 option:eq('+ firstvalue + ')').remove();         //�ӵ� firstvalue��ʼ remov
  }
}

function remove_option2(minvalue,maxvalue,firstvalue)            //��ݵ�һ��ƥ��ڶ���֡��
{
	for(i=minvalue ; i<=maxvalue; i++)
	{
	  $('#frame_rate2 option:eq('+ firstvalue + ')').remove();
  }
}
	
function remove_definition3(minvalue,maxvalue,firstvalue)            //��ݵ�һ��ƥ�����������
{
	for(i=minvalue ; i<=maxvalue; i++)
	{
	  $('#definition3 option:eq('+ firstvalue + ')').remove();         //�ӵ� firstvalue��ʼ remov
  }
}

function remove_option3(minvalue,maxvalue,firstvalue)            //��ݵ�һ��ƥ����ĸ�֡��
{
	for(i=minvalue ; i<=maxvalue; i++)
	{
	  $('#frame_rate3 option:eq('+ firstvalue + ')').remove();
  }
}

function remove_option4(minvalue,maxvalue,firstvalue)            //��ݵ�һ��ƥ����ĸ�֡��
{
	for(i=minvalue ; i<=maxvalue; i++)
	{
	  $('#frame_rate4 option:eq('+ firstvalue + ')').remove();
  }
}
	
function remove_definition4(minvalue,maxvalue,firstvalue)            //��ݵ�һ��ƥ����ĸ������
{
	for(i=minvalue ; i<=maxvalue; i++)
	{
	  $('#definition4 option:eq('+ firstvalue + ')').remove();         //�ӵ� firstvalue��ʼ remov
  }
}
	
function definition_judge()             //ƥ�������
{
	var stream_number_value=document.getElementById("stream_number").value;
	if(stream_number_value==0)
	{
		select_option_judge1();
	}
	if(stream_number_value==1)
	{
		select_option_judge2();
	}
	if(stream_number_value==2)
	{
		select_option_judge3();
	}
	if(stream_number_value==3)
	{
		select_option_judge4();
	}
	
}	
	
function select_option_judge1()           //һ·�����������ƥ������Ⱥ�֡��
{
	$("#frame_rate1").html(wkl_clone1.html());
	//$("#frame_rate2").html(wkl_clone1.html());
	var definition_value1=document.getElementById("definition1").value;
	if(definition_value1==0)
	{
		remove_option(0,2,14);
		$("#frame_rate1").get(0).selectedIndex=13;
	}
	if(definition_value1==1)
	{
		remove_option(0,2,14);
		$("#frame_rate1").get(0).selectedIndex=13  ;              //�������һ��֡��ΪĬ��
	}
	if(definition_value1==2)
	{
	  remove_option(0,4,21);
	  
	}
	if(definition_value1==3)
	{
	  remove_option(0,0,16);
	  $("#frame_rate1").get(0).selectedIndex=15   ;
	}
	if(definition_value1==4)
	{
	  remove_option(0,4,21);
	}
	if(definition_value1==5 || definition_value1==6  )
	{
	  remove_option(0,6,10);
	  $("#frame_rate1").get(0).selectedIndex=9 ; 
	}
}


Array.prototype.distinct = function() {
    var a = {};
    for (var i = 0; i < this.length; i++) {
        if (typeof a[this[i]] == "undefined")
            a[this[i]] = 1;
    }
    this.length = 0;
    for (var i in a)
        this[this.length] = i;
    return this;
}


function get_G_arrs (argument) {
  var nu=document.getElementById("stream_number").value;	
  switch(nu)
   {
   case "0":
     return G.single;
     break
   case "1":
     return G.dual;
     break
   case "2":
     return G.Triple;
     break
   case "3":
     return G.quadplex;
     break
   }

}

function select_value_arrs_a (argument) {
  var arrs = new Array();
  
  if(argument == 1)
      return arrs;
      
  for(var i = 1 ; i < argument; i++)
  {
  	arrs.push($('#definition'+i+'').find("option:selected").text());
  	arrs.push($('#frame_rate'+i+'').find("option:selected").text());
  }
  
  return arrs;
}

function zl_filter (select_arrs, g_arrs_a,argument) {//返回帧率过滤后结果 没有结果返回0
	//select_arrs前面几路已选的设置
	//g_arrs_a当前待匹配数组
	//argument 第几路  
	
	var arrs;
	for(var i = 0; i < (argument - 1); i++)
	{
		if(select_arrs[i*2] != g_arrs_a[i*2])
		   return 0;   
	}
	
	for(var i = 0; i < (argument - 1); i++)
	{
		if(select_arrs[i*2 + 1] > g_arrs_a[i*2 + 1])
		   return 0;   
	}
	return g_arrs_a[(argument - 1) * 2];                                        
}

function get_final_arrs (select_arrs, argument) { //返回最终可选项数组
	 //arrs 去重后的可选项   
	 //select_arrs前面几路已选的设置 
	 //argument 设置的第几路
	 
	/*******分辨率过滤***********/
	var arrs = new Array();
	var g_arrs = get_G_arrs();
	for(var i in g_arrs)
	{  	   		
	   var zl_arrs = zl_filter(select_arrs, g_arrs[i],argument);
	   if(zl_arrs != 0)
	   {
	   	  arrs.push(zl_arrs);
	   }
	}
	
  return arrs;
}
function delete_baseon_befor_choice (arrs, argument) {    //arrs 去重后的可选项 
	var select_arrs =  select_value_arrs_a(argument);  //前面几路已选的设置
	if(select_arrs.length == 0)
       return arrs;
  
    return get_final_arrs(select_arrs, argument);
    
}


function get_option_arrs (select_arrs, argument) {
  var arrs = new Array();
  for(var i in select_arrs) {
  	   arrs.push(select_arrs[i][(argument - 1)*2]);
	}
		
	arrs.distinct();  //数组去重
	arrs = delete_baseon_befor_choice(arrs, argument);
    return arrs;
}


function before_change (argument) {	
			
	var select_arrs = get_G_arrs();	
	
	var arrs = get_option_arrs(select_arrs, argument);

    $('#definition'+ argument + ' option').remove();

	for(var i = 0; i < arrs.length; i++) {
		$("#definition"+ argument + "").append("<option value='" + i + "'>" + arrs[i] + "</option>");		
	};
  
}

function zl_delete_g_arrs (g_arrs_a, argument) { //判断当前数组 编码部分是否与已选值匹配  ,匹配返回1, 否则0
	//argument 第几路的编码

  var select_arrs = select_value_arrs_a(argument);  //前面几路已选的设置 
  
  
  for(var i = 0; i < (argument - 1); i++)
	{
		if(select_arrs[i*2] != g_arrs_a[i*2])
		   return 0;   
	}
	 
	for(var i = 0; i < (argument - 1); i++)
	{
		if(select_arrs[i*2 + 1] > g_arrs_a[i*2 + 1])
		   return 0;   
	}
	
	return 1;        
}

function zl_delete_now_arrs (arrs, argument) {	
   var me = $('#definition'+argument+'').find("option:selected").text();
   if (me == arrs[(argument - 1)*2])
   	  return 1;
   else
   	  return 0;

}

function compare(a,b)   
    {   
        return b-a;   
    }

function zl_final_arrs (arrs, argument) {   //返回正确的选项最大值
	//arrs 最终可选项
	//argument  第几路的编码设置
	var val_arrs = new Array();
	
	for(var i in arrs)
	{
		val_arrs.push(arrs[i][argument * 2 - 1]);
	}
  
    val_arrs.sort(compare);
    return val_arrs[0];
  
}

function zl_get_option_arrs (argument) {  //返回正确的选项数组
	//argument  第几路的编码设置
  var arrs = get_G_arrs();
  
  /*******依赖前面选择去除不匹配项********/
  for(var i in arrs)
  {
  	if(zl_delete_g_arrs(arrs[i] , argument) == 0)
  	   delete arrs[i];
  }
  
  /********根据当前项去除不匹配**********/
  for(var i in arrs)
  {
  	if(zl_delete_now_arrs(arrs[i] , argument) == 0)
  	   delete arrs[i];
  }
  
  return zl_final_arrs(arrs, argument);

}

function zl_judg (argument) {
   var arrs = G_zl;
   for(var i = arrs.length - 1; 0 <= i ; i--)
   {
   	  if(argument < arrs[i])
   	      arrs.pop();
   }
   return arrs;
}

function zl_before_change (argument) {
  
    var arrs = zl_get_option_arrs (argument);
    
    var final_arrs = zl_judg(arrs);
    
    
    $('#frame_rate'+ argument + ' option').remove();
    
	for(var i = 0; i < final_arrs.length; i++) {
		$("#frame_rate"+ argument + "").append("<option value='" + i + "'>" + final_arrs[i] + "</option>");		
	};
}


function select_option_judge2()
{
	
		
	$("#frame_rate2").html(wkl_clone2.html());                  //���صڶ���֡��
	$("#definition2").html(wkl_definition2.html());             //���¼��صڶ��������
	select_option_judge1();
	var definition_value1=document.getElementById("definition1").value;
	var definition_value2=document.getElementById("definition2").value;
	if(definition_value1==0)
	{
		remove_definition2(0,5,1);
		remove_option2(0,4,21);
	}
	if(definition_value1==1)
	{
		remove_definition2(0,0,0);
		remove_definition2(0,5,1);
		$("#frame_rate2").get(0).selectedIndex=13
	}
	if(definition_value1==2)
	{
		remove_definition2(0,1,5);
		remove_definition2(0,0,2);
		remove_option2(0,4,21);
	}
	if(definition_value1==3)
	{
		remove_definition2(0,0,2);
		remove_definition2(0,3,3);
		remove_option2(0,2,14);
		$("#frame_rate2").get(0).selectedIndex=13  ;  
	}
	if(definition_value1==5)
	{
		remove_definition2(0,0,0);
		remove_definition2(0,5,1);
     
    $("#frame_rate1").html(wkl_clone1.html());                    //���¼��ص�һ��֡��
    remove_option(0,2,14);
    remove_option2(0,2,14);
		$("#frame_rate1").get(0).selectedIndex=13
		$("#frame_rate2").get(0).selectedIndex=13
	}
	if(definition_value1==6)
	{
		remove_definition2(0,1,0);
		remove_definition2(0,4,1);
		remove_option2(0,4,21);
	}
	if(definition_value1==7)
	{
		remove_definition2(0,1,0);		
		remove_definition2(0,6,1);
		remove_option2(0,4,21);
		
	}
}


function select_option_judge3()
{
	select_option_judge2();
	//$("#frame_rate3").html(wkl_clone2.html());                  //���ص����֡��
	$("#definition3").html(wkl_definition3.html());             //���¼��ص���������
	var definition_value1=document.getElementById("definition1").value;
	if(definition_value1==1)
	{
		remove_definition3(0,0,0);
		remove_definition3(0,5,1);		
	}
	if(definition_value1==3)
	{
		remove_definition2(0,1,0);		
		remove_definition3(0,0,0);
		remove_definition3(0,0,1);
		remove_definition3(0,3,2);
	}
	if(definition_value1==5)
	{
		remove_definition3(0,0,2);
		remove_definition3(0,0,3);
		remove_definition3(0,1,4);
	}
	if(definition_value1==6)
	{
		$("#definition2").html(wkl_definition2.html()); 
		remove_definition2(0,0,0); 
		remove_definition2(0,5,1); 
		remove_definition3(0,6,1); 
	}
}

function select_option_judge4()
{
	select_option_judge3();
	$("#definition4").html(wkl_definition4.html());           //���¼��ص��ĸ������
	var definition_value1=document.getElementById("definition1").value;    
	if(definition_value1==5)
	{
		$("#definition3").html(wkl_definition3.html());
		remove_definition3(0,2,2); 
		remove_definition3(0,1,3);
		remove_definition4(0,3,1);
		remove_definition4(0,1,2);
	}
	if(definition_value1==3)
	{
		$("#definition3").html(wkl_definition3.html()); 
		remove_definition3(0,0,2); 
		remove_definition3(0,3,3); 
		remove_definition4(0,0,2); 
		remove_definition4(0,3,3); 
	}
	if(definition_value1==1)
	{
		remove_definition4(0,0,0); 
		remove_definition4(0,6,1); 
	}
	if(definition_value1==6)
	{
		$("#definition2").html(wkl_definition2.html()); 
		$("#definition3").html(wkl_definition3.html()); 
		remove_definition2(0,2,0);
		remove_definition2(0,3,1);
		remove_definition3(0,2,0);
		remove_definition3(0,3,1);
		remove_definition4(0,1,0);
		remove_definition4(0,4,1);
	}
}


function select_option1_judge()                     //��һ��֡�����ж����������Ⱥ������֡��
{
	var frame_rate_value1=document.getElementById("frame_rate1").value;
	var definition_value1=document.getElementById("definition1").value;
	var stream_number_value=document.getElementById("stream_number").value;
	if(stream_number_value==1)
	{
		if(definition_value1==5)
		{
			
			if(frame_rate_value1==11)
			{
			  $("#definition2").html(wkl_definition2.html());
			  $("#frame_rate2").html(wkl_clone2.html());   
				remove_definition2(0,2,0);
				remove_definition2(0,3,1);
				remove_option2(0,4,12);
				$("#frame_rate2").get(0).selectedIndex=11  ;              //�������һ��֡��ΪĬ��
			}
		  
		  if(frame_rate_value1==13)
			{
				$("#definition2").html(wkl_definition2.html());
			  $("#frame_rate2").html(wkl_clone2.html());   
				remove_definition2(0,0,0);
				remove_definition2(0,5,1);
				remove_option2(0,2,14);
				$("#frame_rate2").get(0).selectedIndex=13  ;  
			}
			if(frame_rate_value1==9)
			{
				$("#definition2").html(wkl_definition2.html());
			  $("#frame_rate2").html(wkl_clone2.html());   
				remove_definition2(0,2,0);
				remove_definition2(0,0,1);
				remove_definition2(0,1,2);
				remove_option2(0,6,10);
				$("#frame_rate2").get(0).selectedIndex=9  ;  
			}
		}
		if(definition_value1==3)
		{
			if(frame_rate_value1==13)
			{
				$("#definition2").html(wkl_definition2.html());
				$("#frame_rate2").html(wkl_clone2.html());   
				remove_definition2(0,1,1);
				remove_definition2(0,4,2);
				remove_option2(0,2,14);
				$("#frame_rate2").get(0).selectedIndex=13  ;  
			}
		}
	}
}



function definition2_judge()                        //�ڶ�����������ж������֡��
{
	var stream_number_value=document.getElementById("stream_number").value;
	var definition_value1=document.getElementById("definition1").value; 
	var definition_value2=document.getElementById("definition2").value;
	var frame_rate_value1=document.getElementById("frame_rate1").value; 
	if(stream_number_value==2)
	{
		if(definition_value1==5)
		{
			
			if(definition_value2==3)
			{
				$("#frame_rate2").html(wkl_clone2.html());   
				remove_option2(0,2,14);
				$("#frame_rate2").get(0).selectedIndex=13  ;  
			}
			if(definition_value2==5)
			{
				$("#frame_rate2").html(wkl_clone2.html());   
				remove_option2(0,6,10);
				$("#frame_rate2").get(0).selectedIndex=9  ;  
			}
		}
	
	}
}