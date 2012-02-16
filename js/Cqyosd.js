

function Judge1()
	{
		document.getElementById("text_judge").value=1;
		setOSD();
	}
	function Judge2()
	{
		document.getElementById("text_judge").value=2;
		setOSD();
	}
	
	function Judge3()
	{
		document.getElementById("text_judge").value=3;
		setOSD();
	}
	
	

	function clean1()                         //Çå³ý
	{
		document.getElementById("s1_text1").value="";
		document.getElementById("s1_text1_width").value="";
		document.getElementById("s1_text1_size").value="";
		document.getElementById("s1_text1_high").value="";
		document.getElementById("s1_text1_startx").value="";
		document.getElementById("s1_text1_starty").value="";
		document.getElementById("s1_text1_outline").value="";
		document.getElementById("s1_text1_color").value="";
		document.getElementById("s1_text1_bold").value="";
		document.getElementById("s1_text1_italic").value="";
		document.getElementById("s1_text1_type").value="";
		document.getElementById("s1_text1_rotate").value="";	
		document.getElementById("text_clean").value="";	
		Judge1();
		
	}
	
	function clean2()
	{
		document.getElementById("s1_text2").value="";
		document.getElementById("s1_text2_width").value="";
		document.getElementById("s1_text2_size").value="";
		document.getElementById("s1_text2_high").value="";
		document.getElementById("s1_text2_startx").value="";
		document.getElementById("s1_text2_starty").value="";
		document.getElementById("s1_text2_outline").value="";
		document.getElementById("s1_text2_color").value="";
		document.getElementById("s1_text2_bold").value="";
		document.getElementById("s1_text2_italic").value="";
		document.getElementById("s1_text2_type").value="";
		document.getElementById("s1_text2_rotate").value="";
		document.getElementById("text_clean").value="";
		Judge2();
	}
	
	function clean3()
	{
		document.getElementById("s1_text3").value="";
		document.getElementById("s1_text3_width").value="";
		document.getElementById("s1_text3_size").value="";
		document.getElementById("s1_text3_high").value="";
		document.getElementById("s1_text3_startx").value="";
		document.getElementById("s1_text3_starty").value="";
		document.getElementById("s1_text3_outline").value="";
		document.getElementById("s1_text3_color").value="";
		document.getElementById("s1_text3_bold").value="";
		document.getElementById("s1_text3_italic").value="";
		document.getElementById("s1_text3_type").value="";
		document.getElementById("s1_text3_rotate").value="";
		document.getElementById("text_clean").value="";
		Judge3();
	}
	
	function init()
		{
			getOSD();
			OnLoadActiveX(location.host, 0, 1, 0, 1);
		}