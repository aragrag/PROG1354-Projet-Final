function toggleLight() {	
    var body = document.getElementById('body');
    var currentClass = body.className;
    body.className = currentClass == 'dark-mode' ? 'light-mode' : 'light-mode';
  }

  function toggleDark() {
    var body = document.getElementById('body');
    var currentClass = body.className;
    body.className = currentClass == 'light-mode' ? 'dark-mode' : 'dark-mode';
  }

  $('.btn-group > .btn').click(function(){
    $('.btn-group > .btn').removeClass('active');
    $(this).addClass('active');
  });	
setInterval(function() {
    var url = 'data.json';

    $.ajax({
         beforeSend: function(xhr){
            if (xhr.overrideMimeType)
            {
              xhr.overrideMimeType('application/json');
            }
        },
        cache: false,							
        dataType: 'json',
        url: url,
        method:'GET'
    }).done(function(data){
       // json = JSON.stringify(data);
        
        console.log(data)
        var d = data[0];


        var data_temperature = d.temperature;
        // var data_wind = dataReversedArray1.wind;
        var data_humidity = d.humidity;
        // var data_luminosity = dataReversedArray1.luminosity;
        var data_pressure = d.pressure;
        // var data_rain = dataReversedArray1.data_rain;
       
       $('#temperature').html(data_temperature).animate({'opacity': 1}, 900);
       $('.progress-bar.temperature').width(data_temperature+'%');

    //    $('#wind').html(data_wind).animate({'opacity': 1}, 900);
    //    $('.progress-bar.wind').width(data_wind+'%');

       $('#humidity').html(data_humidity).animate({'opacity': 1}, 900);
       $('.progress-bar.humidity').width(data_humidity+'%');

    //    $('#luminosity').html(data_luminosity).animate({'opacity': 1}, 900);
    //    $('.progress-bar.luminosity').width(data_luminosity+'%');

       $('#pressure').html(data_pressure).animate({'opacity': 1}, 900);
       $('.progress-bar.pressure').width(data_pressure+'%');	
       
    //    $('#rain').html(data_rain).animate({'opacity': 1}, 900);
    //    $('.progress-bar.rain').width(data_rain+'%');							   


    }).fail((responseData) => {
            if (responseData.responseCode) {
                console.error(responseData.responseCode);
            }
    });
}, 10000);



// Date & Time

function startTime() {
    var today = new Date();
    var hr = today.getHours();
    var min = today.getMinutes();
    var sec = today.getSeconds();
    ap = (hr < 12) ? "<span>AM</span>" : "<span>PM</span>";
    hr = (hr == 0) ? 12 : hr;
    hr = (hr > 12) ? hr - 12 : hr;
    //Add a zero in front of numbers<10
    hr = checkTime(hr);
    min = checkTime(min);
    sec = checkTime(sec);
    document.getElementById("clock").innerHTML = hr + ":" + min + ":" + sec + " " + ap;
    
    var months = ['Janvier', 'Février', 'Mars', 'Avril', 'Mai', 'Juin', 'Juillet', 'Aout', 'Septembre', 'Octobre', 'Novembre', 'Décembre'];
    var days = ['Dim', 'Lun', 'Mar', 'Mer', 'Jeu', 'Ven', 'Sam'];
    var curWeekDay = days[today.getDay()];
    var curDay = today.getDate();
    var curMonth = months[today.getMonth()];
    var curYear = today.getFullYear();
    var date = curWeekDay+", "+curDay+" "+curMonth+" "+curYear;
    document.getElementById("date").innerHTML = date;
    
    var time = setTimeout(function(){ startTime() }, 500);
}
function checkTime(i) {
    if (i < 10) {
        i = "0" + i;
    }
    return i;
}
startTime();
