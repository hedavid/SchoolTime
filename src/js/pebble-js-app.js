/*
Copyright (c) 2015 , Ben624

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, 
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. 
THIS APPLICATION CAN BE SHARED ACROSS PEBBLE OWNERS, BUT CAN NOT BE PUBLISHED PUBLICLY ON THE PEBBLE APP STORE. 

Permission to use, copy, or modify, this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.
*/

//Javascript Ready.
Pebble.addEventListener("ready",
    function(e) {


    }
);
//Show configuration page and pass in values.
Pebble.addEventListener("showConfiguration",
  function(e) {
	  var urlString;
    	//urlString= 'http://ben624.com/SchoolTime/V5/classic.html?';	
	      	urlString= 'http://ben624.com/SchoolTime/V5/config.html?';	

	  
	for ( var i = 1 ; i <= 8  ; i++) {
		var nameVar = 'class'+i+'Name';
		var jsnameVar = 'c'+i+'N';
		var nameVal = window.localStorage.getItem(jsnameVar);
        urlString += '&' + nameVar  + '=' + nameVal;
    } 
		urlString += '&sday=' + window.localStorage.getItem('sday');
	  urlString += '&wmode=' + window.localStorage.getItem('wmode');
	  urlString += '&tcolorc=' + window.localStorage.getItem('tcolorc');
	  urlString += '&blue=' + window.localStorage.getItem('blue');
	  urlString += '&bluea=' + window.localStorage.getItem('bluea');
	  urlString += '&bat=' + window.localStorage.getItem('bat');
	  urlString += '&dcolor=' + window.localStorage.getItem('dcolor');
	  urlString += '&lcolor=' + window.localStorage.getItem('lcolor');
	  urlString += '&tcolor=' + window.localStorage.getItem('tcolor');
	  urlString += '&batcolor=' + window.localStorage.getItem('batcolor');
	  urlString += '&bluecolor=' + window.localStorage.getItem('bluecolor');
	  urlString += '&backcolor=' + window.localStorage.getItem('backcolor');
	  urlString += '&periodcolor=' + window.localStorage.getItem('periodcolor');
	  urlString += '&breakmode=' + window.localStorage.getItem('breakmode');

     
	console.log("URL OPENING IS...")
    console.log(urlString);
	Pebble.openURL(urlString);
    return urlString;
  }
);


//Save entered values
Pebble.addEventListener("webviewclosed",
  function(e) {
	 if(e.response.length <= 2){
		 console.log("Cancel Button Pressed");
	 }else{
	  var options = JSON.parse(decodeURIComponent(e.response));
	  console.log("RESPONSE CLOSED VIEW");
	  console.log(e.response);	
	window.localStorage.setItem('c1N', encodeURIComponent(options.c1N));
    window.localStorage.setItem('c2N', encodeURIComponent(options.c2N));
    window.localStorage.setItem('c3N', encodeURIComponent(options.c3N));
	window.localStorage.setItem('c4N', encodeURIComponent(options.c4N));
    window.localStorage.setItem('c5N', encodeURIComponent(options.c5N));
    window.localStorage.setItem('c6N', encodeURIComponent(options.c6N));
    window.localStorage.setItem('c7N', encodeURIComponent(options.c7N));
	window.localStorage.setItem('c8N', encodeURIComponent(options.c8N));
	window.localStorage.setItem('sday', encodeURIComponent(options.sday));
	window.localStorage.setItem('wmode', encodeURIComponent(options.wmode));
	window.localStorage.setItem('tcolorc', encodeURIComponent(options.tcolorc));
	window.localStorage.setItem('blue', encodeURIComponent(options.blue));
	window.localStorage.setItem('bluea', encodeURIComponent(options.bluea));
	window.localStorage.setItem('bat', encodeURIComponent(options.bat));
		 
	window.localStorage.setItem('dcolor', encodeURIComponent(options.dcolor));
	window.localStorage.setItem('lcolor', encodeURIComponent(options.lcolor));
	window.localStorage.setItem('tcolor', encodeURIComponent(options.tcolor));
	window.localStorage.setItem('batcolor', encodeURIComponent(options.batcolor));
	window.localStorage.setItem('bluecolor', encodeURIComponent(options.bluecolor));
	window.localStorage.setItem('backcolor', encodeURIComponent(options.backcolor));
	window.localStorage.setItem('periodcolor', encodeURIComponent(options.periodcolor));
	window.localStorage.setItem('breakmode', encodeURIComponent(options.breakmode));

  
	 Pebble.sendAppMessage(options);
	 }
  });
