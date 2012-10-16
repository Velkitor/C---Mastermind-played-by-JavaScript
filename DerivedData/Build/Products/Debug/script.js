Games.Mastermind.start();
var matches = 0, solved = false;
var pos1=0, pos2=0, pos3=0, pos4=0;
//Brute force it!
while( ! solved ){
	pos1++;
	if( pos1 > 3){
		pos1 = 0;
		pos2++
		if( pos2 > 3){
			pos2 = 0;
			pos3++;
			if( pos3 > 3){
				pos3 = 0;
				pos4++;
				if( pos4 > 3){
					pos4 = 0;
				}
			}
		}
	}
	matches = Games.Mastermind.guess(pos1,pos2,pos3,pos4);
	if( matches === 4){
		System.log( "Solving with: " + pos1 + ", " + pos2 +", " +pos3 + ", " + pos4);
		solved = Games.Mastermind.solve(pos1,pos2,pos3,pos4);
		System.log( "JS: Solve returned" + solved);
		if( !solved){
			System.usleep(1000000);
		} else {
			System.log( "SOLVED YAY!");
		}
	}
}
