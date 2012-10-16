(function() {
  var i, _i;
  
	var right = true;
	var i = 0, r = 100.0 ,g = 100.0 , b = 100.0; 
	
  while(true) {
		var pos = System.boxPosition;
		var screenSize = System.screenSize;
		// var new_x = pos[0];
		// if( right )
		// 	right = (new_x <= (screenSize[0] -128));
		// else if( !right )
		// 	right = (new_x <= 0);
		// if( right ){
		// 	new_x += 1;
		// } else {
		// 	new_x -= 1;
		// }
		var x = Math.cos((i/200)%360) + 1.0;
		x *= (screenSize[0] -128)/2
		var y = Math.sin((i/200)%360) + 1.0;
		y *= (screenSize[1] -128)/2;
		System.positionBox(x, y);
		if( i % 7 === 0)
			r++;
		r = r % 255.0;
		if( r < 100.0 )
		 r = 100.0;
		if( i % 11 === 0)
			g++;
		g = g % 255.0;
		if( g < 100.0 )
		 g = 100.0;
		if( i % 13 === 0)
			b++;
		b = b % 255.0;
		if( b < 100.0 )
		 b = 100.0;
		System.setBoxColor(r /255.0, g /255.0,  b /255.0 );
		System.usleep(2000);
		i++;
  }

}).call(this);
