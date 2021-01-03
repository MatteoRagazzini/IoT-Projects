package it.unibo.console.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Toolkit;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;

import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import it.unibo.console.serial.SerialCommChannel;

import javax.swing.JLabel;

public class ConsoleFrame extends JFrame {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private final JPanel scanPanel = new JPanel();
	private final JLabel scanLabel = new JLabel("prova");
	private final JPanel buttonPanel = new JPanel();
	private final JPanel ledPanel = new JPanel();
	private final JButton singleModeBt;
	private final JButton autoModeBt;
	private final JButton manualModeBt;
	private ControlPanel commandPanel;
	private final JPanel backPanel = new JPanel();
	private final JLabel LD = new JLabel();
	private final JLabel LA = new JLabel();
	private Agent agentLD;
	private Agent agentLA;
	private final SerialCommChannel channel;
	

	public ConsoleFrame(SerialCommChannel channel) {
		final int width = (int) (Toolkit.getDefaultToolkit().getScreenSize().getWidth()*0.5);
		final int height = (int)(Toolkit.getDefaultToolkit().getScreenSize().getHeight()*0.5);
		setSize(width, height);
		setResizable(false);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.getContentPane().add(backPanel);
		final BorderLayout b = new BorderLayout();
		b.setVgap(40);
		this.channel = channel;
		this.commandPanel = new ControlPanel(channel, new Range(12, 180, 0, "S"));
		this.backPanel.setLayout(b);
		this.backPanel.setBorder(BorderFactory.createLineBorder(Color.WHITE,20));
		this.backPanel.setBackground(Color.WHITE);
		this.backPanel.add(scanPanel, BorderLayout.NORTH);
		this.backPanel.add(buttonPanel, BorderLayout.SOUTH);
		this.backPanel.add(commandPanel, BorderLayout.WEST);
		this.backPanel.add(ledPanel, BorderLayout.CENTER);
		
		this.ledPanel.setBackground(Color.WHITE);
		final FlowLayout f = new FlowLayout();
		this.ledPanel.setLayout(f);
		f.setHgap(120);
		this.ledPanel.add(LD);
		this.ledPanel.add(LA);
		
		try {
			agentLD = new Agent(LD,"g", 125, false);
			new Thread(agentLD).start();
			
			agentLA = new Agent(LA,"r", 125, true);
			new Thread(agentLA).start();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
        
		
		this.scanPanel.setPreferredSize(new Dimension(width, (int)(height*0.3)));
		this.scanLabel.setPreferredSize(new Dimension(820, 150));
		this.scanPanel.add(scanLabel);
		this.scanLabel.setBackground(Color.WHITE);
		this.scanPanel.setBackground(Color.WHITE);
		this.scanLabel.setFont(new Font(Font.MONOSPACED,Font.BOLD, 24));
		this.scanLabel.setHorizontalAlignment(JLabel.CENTER);
		this.scanLabel.setOpaque(true);
		this.scanLabel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));
		this.buttonPanel.setLayout(new GridBagLayout());
		final GridBagConstraints c = new GridBagConstraints();
		c.insets = new Insets(0, 30, 0, 30);
		this.singleModeBt = getButton("SINGLE");
		this.autoModeBt = getButton("AUTO");
		this.manualModeBt = getButton("MANUAL");
		this.singleModeBt.setPreferredSize(new Dimension(230,50));
		this.manualModeBt.setPreferredSize(new Dimension(230,50));
		this.autoModeBt.setPreferredSize(new Dimension(230,50));
		this.buttonPanel.setBackground(Color.WHITE);
		this.buttonPanel.add(singleModeBt,c);
		this.buttonPanel.add(autoModeBt, c);
		this.buttonPanel.add(manualModeBt,c);

		final ActionListener a = e->{
			this.commandPanel.setRange(new Range(1, 5, 1, "P"));
			this.stopAlarm();
			int m = ((JButton)e.getSource()).getText().substring(0, 1).equals("S") ? 0:1;
			this.channel.sendMsg("M"+ m);
			
			};
		this.singleModeBt.addActionListener(a);
		this.autoModeBt.addActionListener(a);
		this.manualModeBt.addActionListener(e->{
			this.stopAlarm();
			this.commandPanel.setRange(new Range(12, 180, 0, "S"));
			this.channel.sendMsg("M"+ 2);
			});
	
		setVisible(true);
		switchOff();
		
	}
	
	public void setPotRangePanel() {
		this.commandPanel.setRange(new Range(1, 5, 1, "P"));
		this.scanLabel.setText("");
	}
	
	public void setAngleRangePanel() {
		this.commandPanel.setRange(new Range(12, 180, 0, "S"));
		this.scanLabel.setText("");
	}
	
	public void startBlink() {
		agentLD.startBlink();
	}
	
	public void startAlarm() {
		agentLA.startBlink();
		this.scanLabel.setBorder(BorderFactory.createLineBorder(Color.RED, 4));
	}
	
	public void stopAlarm() {
		agentLA.stopBlink();
		agentLA.switchOff();
		this.scanLabel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));
	}
	
	public void printMsg(String msg) {
		this.scanLabel.setText(msg);
	}
	
	private JButton getButton(String text) {
		final JButton but = new JButton(text);
		but.setFont(new Font(Font.MONOSPACED,Font.BOLD, 24));
		return but;
	}
	
	public void switchOn() {
		this.autoModeBt.setEnabled(true);
		this.singleModeBt.setEnabled(true);
		this.manualModeBt.setEnabled(true);
		this.commandPanel.setEnable(true);
	}
	public void switchOff() {
		this.autoModeBt.setEnabled(false);
		this.singleModeBt.setEnabled(false);
		this.manualModeBt.setEnabled(false);
		this.commandPanel.setEnable(false);
	}
	
	
	
	private enum LedState {
		ON, OFF;
	}
	 private class Agent implements Runnable {
	        /*
	         * stop is volatile to ensure ordered access
	         */
	        private volatile boolean stop = true;
	        private Image ON;
	        private Image OFF;
	        private LedState state = LedState.OFF;
	        private final JLabel led;
	        private final int period;
	        private final boolean isContinuous;
	        
	        public Agent(JLabel led, String color, int period, boolean c) throws IOException {
					ON = ImageIO.read(ClassLoader.getSystemResource(color + "LedOn1.png"));
					ON = ON.getScaledInstance(120, 144, Image.SCALE_SMOOTH);
					OFF = ImageIO.read(ClassLoader.getSystemResource(color + "LedOff1.png"));
					OFF = OFF.getScaledInstance(120, 144, Image.SCALE_SMOOTH);
					this.led = led;
					led.setIcon(new ImageIcon(OFF));
					this.period = period;
					this.isContinuous = c;
			}

	        public void run() {
	            while (true) {
	            	if(!stop) {
		                try {
		                    SwingUtilities.invokeAndWait(new Runnable() {
		                        public void run() {
		                        	switch(state) {
		                            case OFF: 
		                            	switchOn();
		                            	break;
		                            case ON:
		                            	switchOff();
		                            	stop = !isContinuous;
		                            	break;
		                        	}

		                        	
		                        }
		                    });
		                    Thread.sleep(period);
		                } catch (InvocationTargetException | InterruptedException ex) {
		                    ex.printStackTrace();
		                }
		            
	            	}
	            }
	        }

	        public void stopBlink() {
	            this.stop = true;
	        }
	        
	        public void startBlink() {
	        	this.stop = false;
	        }
	        
	        public void switchOn() {
	        	led.setIcon(new ImageIcon(ON));
            	state = LedState.ON;
	        }
	        
	        public void switchOff() {
	        	led.setIcon(new ImageIcon(OFF));
             	state = LedState.OFF;
	        }
	    }
}
