
task intakeTask()
{
	while(true) {
		if( vexRT[Btn5UXmtr2] ) {
			motor[intake] = 127;
	}else if( vexRT[Btn5DXmtr2]){
			motor[intake] = -127;
	}else{
			motor[intake] = 0;
		}
	}


}
