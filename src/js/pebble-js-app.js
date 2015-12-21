Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready!');
});

Pebble.addEventListener('showConfiguration', function() {
  var url = " ";

	if (Pebble.getActiveWatchInfo) {
	  var info = Pebble.getActiveWatchInfo();
		if(info.platform == "aplite"){
			console.log("APLITE");
			url = "http://ben624.com/SchoolTime/SDK3/Aplite.html";
		}else if(info.platform == "basalt"){
			console.log("BASALT");
			url = "http://ben624.com/SchoolTime/SDK3/Basalt.html";
		}else if(info.platform == "chalk"){
			console.log("CHALK");
			url = "http://ben624.com/SchoolTime/SDK3/Chalk.html";

		}else{
			Pebble.showSimpleNotificationOnPebble("Unknown Watch", "Please contact developer");
		}
} else {
		Pebble.showSimpleNotificationOnPebble("Error", "Please update watch to 3.x");
}
  console.log('Showing configuration page: ' + url);

  Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));
  console.log('Configuration page returned: ' + JSON.stringify(configData));


  var dict = {};
    dict['class_1'] = configData['class_1'];
	dict['class_2'] = configData['class_2'];  
    dict['class_3'] = configData['class_3'];
	dict['class_4'] = configData['class_4'];     
	dict['class_5'] = configData['class_5'];
	dict['class_6'] = configData['class_6']; 
    dict['class_7'] = configData['class_7'];
	dict['class_8'] = configData['class_8'];   
	
	dict['school_day'] = configData['school_day'];   
	dict['clock_style'] = configData['clock_style'];   
	dict['show_bluetooth'] = configData['show_bluetooth'];   
	dict['bluetooth_alarm'] = configData['bluetooth_alarm'];   
	dict['show_battery'] = configData['show_battery'];   
	dict['boot_animation'] = configData['boot_animation'];   

 	dict['background_color'] = parseInt(configData['background_color']); 
 	dict['date_color'] = parseInt(configData['date_color']);   
 	dict['time_color'] = parseInt(configData['time_color']);   
 	dict['period_color'] = parseInt(configData['period_color']);   
 	dict['bluetooth_color'] = parseInt(configData['bluetooth_color']);   
 	dict['battery_color'] = parseInt(configData['battery_color']);   
	dict['lines_color'] = parseInt(configData['lines_color']);   


  Pebble.sendAppMessage(dict, function() {
    console.log('Send successful: ' + JSON.stringify(dict));
  }, function() {
    console.log('Send failed!');
  });
});