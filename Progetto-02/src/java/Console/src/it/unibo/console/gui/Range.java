package it.unibo.console.gui;

public class Range {
	
	private final int delta;
	private final int upperBound;
	private final int lowerBound;
	private final String type;
	
	public Range(int delta, int upperBound, int lowerBound, String type) {
		this.delta = delta;
		this.upperBound = upperBound;
		this.lowerBound = lowerBound;
		this.type = type;
	}

	public int getDelta() {
		return delta;
	}

	public int getUpperBound() {
		return upperBound;
	}

	public int getLowerBound() {
		return lowerBound;
	}
	
	public String getType() {
		return type;
	}
	
}
