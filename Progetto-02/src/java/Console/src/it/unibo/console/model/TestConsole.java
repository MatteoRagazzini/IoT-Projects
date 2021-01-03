package it.unibo.console.model;

import it.unibo.console.gui.ConsoleFrame;
import it.unibo.console.serial.SerialCommChannel;

public class TestConsole {

	public static void main(String[] args) throws Exception {
		SerialCommChannel channel = new SerialCommChannel("COM4",9600);		
		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		ConsoleFrame cf = new ConsoleFrame(channel);

		cf.printMsg("Waiting Arduino for rebooting and calibrating...");		
		while(!channel.isMsgAvailable() && channel.receiveMsg().charAt(0) != 'C'){
		}
		cf.switchOn();
		cf.printMsg("Ready.");

		while(true) {
			if(channel.isMsgAvailable()) {
				String msg = channel.receiveMsg();
				if(msg.length()>=1) {
					switch(msg.charAt(0)) {
					case 'R': 
						msg = msg.substring(1);
						cf.printMsg(printRMsg(msg));
						if(blink(msg)){
							cf.startBlink();
						}
						break;
					case 'M':
						System.out.println(msg);
						msg=msg.substring(1);
						if(Integer.parseInt(msg) == 2) {
							cf.setAngleRangePanel();
						}else {
							cf.setPotRangePanel();
						}
						break;
					case 'A':
						msg=msg.substring(1);
						if(Integer.parseInt(msg) == 1) {
							cf.startAlarm();
						}else {
							cf.stopAlarm();
						}
						break;

					default:
						cf.printMsg(msg);
						break;
					}	

					Thread.sleep(100);
				}
			}
		}
	}
	public static String[] MsgParam(String msg){
		return msg.split(":");
	}

	public static String printRMsg(String msg) {
		if(MsgParam(msg).length>=2 && Float.parseFloat(MsgParam(msg)[2]) > 0) {
			return "Rilevato in posizione " + MsgParam(msg)[1] + " a distanza: " + MsgParam(msg)[2];
		}else {
			return "Nessun rilevamento";
		}	
	}

	public static boolean blink(String msg) {
		return Float.parseFloat(MsgParam(msg)[2]) > 0.00;
	}


}
