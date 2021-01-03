package it.unibo.console.gui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

import it.unibo.console.serial.SerialCommChannel;

public class ControlPanel extends JPanel {
	private static final long serialVersionUID = 1L;
	private final JLabel valueLabel = new JLabel("0");
	private final JButton decBt;
	private final JButton incBt;
	private final JButton sendBt;
	private Range r;
	
	public ControlPanel(SerialCommChannel channel, Range range) {
		super(new GridBagLayout());
		this.r = range;
		this.decBt = getButton("<<", 75, 40);
		this.incBt = getButton(">>", 75, 40);
		this.sendBt = getButton("Send", 160, 40);
		final GridBagConstraints c = new GridBagConstraints();
		c.insets = new Insets(5, 5, 5, 5);
		c.gridy = 0;
		valueLabel.setText(Integer.toString(range.getLowerBound()));
		valueLabel.setPreferredSize(new Dimension(160, 40));
		valueLabel.setFont(new Font(Font.MONOSPACED,Font.BOLD, 24));
		valueLabel.setBackground(Color.WHITE);
		valueLabel.setOpaque(true);
		valueLabel.setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY, 2));
		valueLabel.setHorizontalAlignment(JLabel.CENTER);
		add(valueLabel,c);
		c.gridy++;
		final JPanel p = new JPanel(new GridBagLayout());
		add(p,c);
		c.insets = new Insets(0, 5, 0, 5);
		p.setBackground(Color.WHITE);
		p.add(decBt,c);
		p.add(incBt,c);
		c.insets = new Insets(5, 5, 5, 5); 
		c.gridy++;		
		add(new JPanel(new FlowLayout()).add(sendBt),c);
		
		decBt.addActionListener(e -> {
			Integer value = Integer.parseInt(valueLabel.getText())-r.getDelta();
			value = value > r.getLowerBound() ? value : r.getLowerBound();
			valueLabel.setText(value.toString());
		});
		incBt.addActionListener(e -> {
			Integer value = Integer.parseInt(valueLabel.getText())+ r.getDelta();
			value = value < r.getUpperBound() ? value : r.getUpperBound();
			valueLabel.setText(value.toString());
		});
		
		sendBt.addActionListener(e -> channel.sendMsg(r.getType() + valueLabel.getText()));
		setBackground(Color.WHITE);
		setPreferredSize(new Dimension((int)(getPreferredSize().width*1.5), (int)(getPreferredSize().height*2)));
	}
	
	private JButton getButton(String s, int w, int h){
		
		final JButton but = new JButton(s);
		but.setFont(new Font(Font.MONOSPACED,Font.BOLD, 18));
		but.setPreferredSize(new Dimension(w,h));
		return but;
		
	}
	
	public void setRange(Range r) {
		this.r = r;
		this.valueLabel.setText(Integer.toString(r.getLowerBound()));
	}
	
	public void setEnable(boolean e) {
		this.sendBt.setEnabled(e);
	}
}



